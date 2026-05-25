/*
	NAVO Enterprise 2008
	
	CADOCommand - ADO command helper
*/

#ifndef _ADO_COMMAND_H_
#define _ADO_COMMAND_H_

class CADOCommand
{
public:
	CADOCommand(ADODB::_ConnectionPtr & roConnectionPtr);
	~CADOCommand();
	
	ADODB::_RecordsetPtr ExecDirect(LPCTSTR lpCmdString,bool bNoResults);
	ADODB::_RecordsetPtr ExecProc(LPCTSTR lpCmdString,bool bNoResults,VARIANT * pActualParam = NULL);
	ADODB::_RecordsetPtr ExecProc(bool bNoResults,VARIANT * pActualParam = NULL);
	
	void Prepare(LPCTSTR lpCmdString);

	long AddInParam(long nType,LPVOID pData);
	long AddOutParam(long nType);
	void AddReturnValueParam(long nType);
	
	const CSmartOleVariant & GetOutParam(long nInx)
	{
		return m_oOutParamArray[nInx];
	}
	long GetRecordsAffected() const
	{
		ASSERT(m_varRecordsAffected.vt == VT_I4);
		return m_varRecordsAffected.lVal;
	}
	const CSmartOleVariant & GetReturnValue() const
	{
		return m_oReturnValueSOV;
	}
	void set_timeout(long nSeconds);
	void set_cmdtxt(LPCTSTR lpCmdString);
	ADODB::_Command * get_command_ptr();
private:
	VARIANT m_varRecordsAffected;
	ADODB::_CommandPtr m_poCommandPtr;
	CArray<CSmartOleVariant,CSmartOleVariant&> m_oOutParamArray;
	bool			 m_bReturnValueExpected;
	CSmartOleVariant m_oReturnValueSOV;
};

//////////////////////////------------------------------------------
//
//		CADOCommand
//		Implementacja
//
//////////////////////////------------------------------------------
inline CADOCommand::CADOCommand(ADODB::_ConnectionPtr & roConnectionPtr) :
	m_bReturnValueExpected(false)
{
	m_varRecordsAffected.vt = VT_I4;
	m_varRecordsAffected.lVal = 0;
	m_poCommandPtr.CreateInstance("ADODB.Command");
	m_poCommandPtr->ActiveConnection = roConnectionPtr;
	m_poCommandPtr->CommandTimeout = 60 * 60;
}

inline CADOCommand::~CADOCommand()
{
}

inline ADODB::_RecordsetPtr CADOCommand::ExecDirect(LPCTSTR lpCmdString,bool bNoResults)
{
	ASSERT((bool)m_poCommandPtr);
	m_poCommandPtr->CommandText = _bstr_t(lpCmdString);
	m_poCommandPtr->CommandTimeout = 60 * 60;
	return m_poCommandPtr->Execute(&m_varRecordsAffected,NULL,ADODB::adCmdText|
		((bNoResults) ? ADODB::adExecuteNoRecords : 0 ));
}

inline void CADOCommand::Prepare(LPCTSTR lpCmdString)
{
	ASSERT((bool)m_poCommandPtr);
	m_poCommandPtr->CommandText = _bstr_t(lpCmdString);
	m_poCommandPtr->PutPrepared(true);
}

inline long CADOCommand::AddInParam(long nType,LPVOID pData)
{
	ASSERT((bool)m_poCommandPtr);
	CSmartOleVariant oSOV;
	long nSize = Binary2VariantHelper(nType,oSOV,(LPBYTE)pData);
	
	ADODB::DataTypeEnum eDataType;
	switch(nType)
	{
	case SQLT_SMALL:
		eDataType = ADODB::adSmallInt;
	break;
	case SQLT_INT:
	case SQLT_TIME:
		eDataType = ADODB::adInteger;
	break;
	case SQLT_DATE:
		eDataType = ADODB::adDBTimeStamp;
	break;
	case SQLT_IMAGE:
		eDataType = ADODB::adLongVarBinary;
	break;
	case SQLT_MONEY:
	case SQLT_QUANTITY:
		eDataType = ADODB::adCurrency;
	break;
	default:
		if(nType >= SQLT_CHAR0 && nType < SQLT_SMALL)
		{
			eDataType = ADODB::adChar;
		}
		else
		{
			ThrowNavoException(ERCO_OBJSERV_ADDPARAM_INVALID_TYPE,IDPAGE_NOTAVAILABLE);
		}
	}
	ASSERT(nSize != -1);
	ASSERT(oSOV.Type() != VT_EMPTY);

	ADODB::_ParameterPtr poParameterPtr = m_poCommandPtr->CreateParameter(
		_bstr_t(Long2String(1+m_poCommandPtr->Parameters->GetCount())),
		eDataType,ADODB::adParamInput,nSize,_variant_t(oSOV.GetVariantRef()));
	HRESULT hr = m_poCommandPtr->Parameters->Append(poParameterPtr);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_OBJSERV_ADDPARAM_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
	}

	return nSize;
}

inline void CADOCommand::AddReturnValueParam(long nType)
{
	ASSERT((bool)m_poCommandPtr);
	ADODB::DataTypeEnum eDataType;
	long nSize = 0;
	switch(nType)
	{
	case SQLT_SMALL:
		eDataType = ADODB::adSmallInt;
	break;
	case SQLT_INT:
	case SQLT_TIME:
		eDataType = ADODB::adInteger;
	break;
	case SQLT_DATE:
		eDataType = ADODB::adDate;
	break;
	case SQLT_IMAGE:
		eDataType = ADODB::adLongVarBinary;
	break;
	case SQLT_MONEY:
	case SQLT_QUANTITY:
		eDataType = ADODB::adCurrency;
	break;
	default:
		if(nType >= SQLT_CHAR0 && nType < SQLT_SMALL)
		{
			eDataType = ADODB::adChar;
			nSize = (nType < SQLT_VARCHAR0) ? CHARLEN(nType) : VARCHARLEN(nType);
		}
		else
		{
			ThrowNavoException(ERCO_OBJSERV_ADDPARAM_INVALID_TYPE,IDPAGE_NOTAVAILABLE);
		}
	}
	ADODB::_ParameterPtr poParameterPtr = m_poCommandPtr->CreateParameter(
		_bstr_t("RETURN_VALUE"),eDataType,ADODB::adParamReturnValue,nSize);
	HRESULT hr = m_poCommandPtr->Parameters->Append(poParameterPtr);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_OBJSERV_ADDPARAM_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
	}
	m_bReturnValueExpected = true;
}

inline long CADOCommand::AddOutParam(long nType)
{
	ASSERT((bool)m_poCommandPtr);
	ADODB::DataTypeEnum eDataType;
	long nSize = 0;
	switch(nType)
	{
	case SQLT_SMALL:
		eDataType = ADODB::adSmallInt;
	break;
	case SQLT_INT:
	case SQLT_TIME:
		eDataType = ADODB::adInteger;
	break;
	case SQLT_DATE:
		eDataType = ADODB::adDate;
	break;
	case SQLT_IMAGE:
		eDataType = ADODB::adLongVarBinary;
	break;
	case SQLT_MONEY:
	case SQLT_QUANTITY:
		eDataType = ADODB::adCurrency;
	break;
	default:
		if(nType >= SQLT_CHAR0 && nType < SQLT_SMALL)
		{
			eDataType = ADODB::adChar;
			nSize = (nType < SQLT_VARCHAR0) ? CHARLEN(nType) : VARCHARLEN(nType);
		}
		else
		{
			ThrowNavoException(ERCO_OBJSERV_ADDPARAM_INVALID_TYPE,IDPAGE_NOTAVAILABLE);
		}
	}
	ADODB::_ParameterPtr poParameterPtr = m_poCommandPtr->CreateParameter(
		_bstr_t(Long2String(1+m_poCommandPtr->Parameters->GetCount())),
		eDataType,ADODB::adParamOutput,nSize);
	HRESULT hr = m_poCommandPtr->Parameters->Append(poParameterPtr);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_OBJSERV_ADDPARAM_FAILED,IDPAGE_NOTAVAILABLE,SCODE_To_String(hr));
	}
	return m_oOutParamArray.Add(CSmartOleVariant());
}

inline ADODB::_RecordsetPtr CADOCommand::ExecProc(bool bNoResults,VARIANT * pActualParam)
{
	m_poCommandPtr->CommandTimeout = 60 * 60;
	ADODB::_RecordsetPtr poRecordsetPtr = m_poCommandPtr->Execute(&m_varRecordsAffected,pActualParam,ADODB::adCmdStoredProc |
		((bNoResults) ? ADODB::adExecuteNoRecords : 0 ));
	
	if(m_oOutParamArray.GetSize() || m_bReturnValueExpected)
	{
		if(poRecordsetPtr != NULL)	//close recordset if any and not closed
		{
			if(poRecordsetPtr->State != ADODB::adStateClosed)
			{
				poRecordsetPtr->Close();
			}
			poRecordsetPtr = NULL;
		}

		long paramiter = 0;
		if(m_bReturnValueExpected)
		{
			ADODB::_ParameterPtr poParamPtr = m_poCommandPtr->Parameters->Item[ paramiter ];
			ASSERT(poParamPtr->Direction == ADODB::adParamReturnValue);
			m_oReturnValueSOV = poParamPtr->Value;
			paramiter++;
		}
		for(long iter=0; iter <= m_oOutParamArray.GetUpperBound();iter++)
		{
			bool bBreak = false;
			do
			{
				ADODB::_ParameterPtr poParamPtr = m_poCommandPtr->Parameters->Item[ paramiter ];
				paramiter++;
				if(poParamPtr->Direction == ADODB::adParamOutput)
				{
					m_oOutParamArray[iter] = poParamPtr->Value;
					bBreak = true;
				}
			}
			while(!bBreak);
		}
	}
	return poRecordsetPtr;
}

inline ADODB::_RecordsetPtr CADOCommand::ExecProc(LPCTSTR lpCmdString,bool bNoResults,VARIANT * pActualParam)
{
	ASSERT((bool)m_poCommandPtr);
	m_poCommandPtr->CommandText = _bstr_t(lpCmdString);
	return ExecProc(bNoResults,pActualParam);
}

inline void CADOCommand::set_timeout(long nSeconds)
{
	//m_poCommandPtr->CommandTimeout = 0;
}

inline void CADOCommand::set_cmdtxt(LPCTSTR lpCmdString)
{
	ASSERT((bool)m_poCommandPtr);
	m_poCommandPtr->CommandText = _bstr_t(lpCmdString);
}

inline ADODB::_Command * CADOCommand::get_command_ptr()
{
	ASSERT((bool)m_poCommandPtr);
	return m_poCommandPtr.GetInterfacePtr();
}

#else
	#error __FILE__ already included
#endif
