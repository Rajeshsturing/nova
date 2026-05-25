/*
	NAVO Enteprise 2001
	Expression Evaluator

*/

#ifndef _EXPRESSEVAL_H_
#define _EXPRESSEVAL_H_

//-------------------------------------------------------
//	tokeny rozpoznawane przez nas
//-------------------------------------------------------

enum eExpTokens
{
	et_none,			//brak
	et_error,			//b³¹d
	et_value,			//wartoœæ np. 230,23
	et_symbol,			//referencja do zmiennej

	et_op_add,			//	+
	et_op_sub,			//	-
	et_op_mul,			//	*
	et_op_div,			//	/
	
	et_lop_eq,			// =
	et_lop_gt,			// >
	et_lop_ge,			// >=
	et_lop_lt,			// <
	et_lop_le,			// <=
	et_lop_ne,			// <>
	
	et_or,				// ||
	et_and,				// &&
	et_not,				// !

	et_left_bra,		// (
	et_right_bra,		// )

	et_unary_neg,		// unary minus
};

//-------------------------------------------------------
//	CToken - rozpoznany token
//-------------------------------------------------------

class CToken
{
public:
	CToken(eExpTokens eExpToken = et_none) :
		m_eType(eExpToken)
	{
	}
	
	CToken(const CToken & roToken) :
		m_eType(roToken.m_eType),
		m_oValueSOV(roToken.m_oValueSOV)
	{
	}
	virtual void operator = (const CToken & roToken)
	{
		m_eType = roToken.m_eType;
		m_oValueSOV = roToken.m_oValueSOV;
	}
	void SetType(eExpTokens eType)
	{
		m_eType = eType;
	}
	eExpTokens GetType() const
	{
		return m_eType;
	}
	void SetValue(const CSmartOleVariant & roSOV)
	{
		m_oValueSOV = roSOV;
	}
	const CSmartOleVariant & GetValue() const
	{
		return m_oValueSOV;
	}
#ifdef _DEBUG
	CString Dump() const
	{
		switch(m_eType)
		{
		case et_none:			//brak
			return "<brak/>";
		case et_error:			//b³¹d
			return "<blad/>";
		case et_value:			//wartoœæ np. 230:23
			return "<value>" + Variant2String(GetValue()) + "</value>";
		case et_symbol:			//referencja do zmiennej
			return "<symbol>" + Variant2String(GetValue()) + "</symbol>";
		case et_op_add:			//	+
			return "<plus/>";
		case et_op_sub:			//	-
			return "<minus/>";
		case et_op_mul:			//	*
			return "<multi/>";
		case et_op_div:			//	/
			return "<div/>";
		case et_lop_eq:			// =
			return "<equal/>";
		case et_lop_gt:			// >
			return "<greater/>";
		case et_lop_ge:			// >=
			return "<gr_eq/>";
		case et_lop_lt:			// <
			return "<less/>";
		case et_lop_le:			// <=
			return "<less_eq/>";
		case et_lop_ne:			// <>
			return "<not_eq/>";
		case et_or:				// ||
			return "<or/>";
		case et_and:				// &&
			return "<and/>";
		case et_not:				// !
			return "<not/>";
		case et_left_bra:		// (
			return "<leftbra/>";
		case et_right_bra:		// )
			return "<rightbra/>";
		case et_unary_neg:
			return "<unary_minus/>"; //
		default:
			ASSERT(false);
		}
	}
#endif
private:
	CSmartOleVariant m_oValueSOV;
	eExpTokens m_eType;
};

//-------------------------------------------------------
//		CTokenizer - analizator lexycalny
//-------------------------------------------------------

class CTokenizer
{
public:
	CTokenizer(LPCTSTR lpInputString) :
		m_lpInputString(lpInputString)
	{
		ASSERT(m_lpInputString);
	}
	bool GetToken(CToken & roToken)
	{
		TCHAR cChar = *m_lpInputString++;
		while(IsSpace(cChar))
		{
			cChar = *m_lpInputString++;
		}
		switch(cChar)
		{
		case '\0':
			roToken.SetType(et_none);
			m_lpInputString--;
			return false;
		case '+':
			roToken.SetType(et_op_add);
			return true;
		case '-':
			roToken.SetType(et_op_sub);
			return true;
		case '*':
			roToken.SetType(et_op_mul);
			return true;
		case '/':
			roToken.SetType(et_op_div);
			return true;
		case '=':
			roToken.SetType(et_lop_eq);
			return true;
		case '>':
			if(*m_lpInputString == '=')
			{
				m_lpInputString++;
				roToken.SetType(et_lop_ge);
				return true;
			}
			else
			{
				roToken.SetType(et_lop_gt);
				return true;
			}
		case '<':
			if(*m_lpInputString == '=')
			{
				m_lpInputString++;
				roToken.SetType(et_lop_le);
				return true;
			}
			else if(*m_lpInputString == '>')
			{
				m_lpInputString++;
				roToken.SetType(et_lop_ne);
				return true;
			}
			else
			{
				roToken.SetType(et_lop_lt);
				return true;
			}
		case '|':
			if(*m_lpInputString == '|')
			{
				m_lpInputString++;
				roToken.SetType(et_or);
				return true;
			}
			roToken.SetType(et_error);
			return true;
		case '&':
			if(*m_lpInputString == '&')
			{
				m_lpInputString++;
				roToken.SetType(et_and);
				return true;
			}
			roToken.SetType(et_error);
			return true;
		case '!':
			if(*m_lpInputString == '=')
			{
				m_lpInputString++;
				roToken.SetType(et_lop_ne);
				return true;
			}
			else
			{
				roToken.SetType(et_not);
				return true;
			}
		case '(':
			roToken.SetType(et_left_bra);
			return true;
		case ')':
			roToken.SetType(et_right_bra);
			return true;
		case '"':
		{
			long nLen = _tcscspn(m_lpInputString,_T("\""));
			roToken.SetType(et_value);
			roToken.SetValue(CSmartOleVariant(CString(m_lpInputString,nLen)));
			m_lpInputString += nLen + 1;
			return true;
		}
		default:
			if(IsAlpha(cChar))
			{
				long nLen = 0;
				while(IsAlphaNum(*(m_lpInputString+nLen)))
				{
					nLen++;
				}
				roToken.SetType(et_symbol);
				roToken.SetValue(CSmartOleVariant(CString(m_lpInputString-1,1+nLen)));
				m_lpInputString += nLen;
				return true;
			}
			else if(IsDigit(cChar))	//number
			{
				LPTSTR lpEndChar;
				long nIntPart = _tcstol(m_lpInputString-1,&lpEndChar,10);
				if(*lpEndChar == '.')	//exists fractiona part
				{
					double dValue = _tcstod(m_lpInputString-1,&lpEndChar);
					m_lpInputString = lpEndChar;
					roToken.SetType(et_value);
					CSmartOleVariant oSOV(dValue);
					oSOV.ChangeType(VT_CY);
					roToken.SetValue(oSOV);
					return true;
				}
				else
				{
					m_lpInputString = lpEndChar;
					roToken.SetType(et_value);
					roToken.SetValue(CSmartOleVariant(nIntPart,VT_I4));
					return true;
				}
			}
			roToken.SetType(et_error);
			return true;
		}
	}
private:
	LPCTSTR m_lpInputString;

};

//-------------------------------------------------------
//		CComputer - computes expression from stack
//-------------------------------------------------------
class CComputeException
{
public :
	CComputeException(LPCTSTR lpMsg) :
	   m_oErrorMsgString(lpMsg)
	{
	}
	LPCTSTR GetMsg() const
	{
		return m_oErrorMsgString;
	}
private:
	CString m_oErrorMsgString;
};

static void _math_values(eExpTokens eOperation,
						 const CSmartOleVariant & roOp1SOV,
						const CSmartOleVariant & roOp2SOV,
						CSmartOleVariant & roResultSOV)
{
	if(roOp1SOV.Type() == VT_I4 && roOp2SOV.Type() == VT_I4)
	{
		roResultSOV.ChangeType(VT_I4);
		long N1 = roOp2SOV.GetLong();
		long N2 = roOp1SOV.GetLong();
		long Res;
		switch(eOperation)
		{
			case et_op_add:
				Res = N1 + N2;
			break;
			case et_op_sub:
				Res = N1 - N2;
			break;
			case et_op_mul:
				Res = N1 * N2;
			break;
			case et_op_div:
				if(N2 == 0)
				{
					throw CComputeException("divide by zero (" + Variant2String(roOp1SOV) +
						"," + Variant2String(roOp1SOV) + ")");
				}
				Res = N1 / N2;
			break;
			default:
				ASSERT(false);
		}
		roResultSOV.SetLong(Res);
		return;
	}
	else if(roOp1SOV.Type() == VT_BSTR && roOp2SOV.Type() == VT_BSTR)
	{
		if(eOperation == et_op_add)		//stringi umiemy tylko dodawaæ
		{
			roResultSOV.ChangeType(VT_BSTR);
			CString oString(roOp2SOV.GetBStr());
			oString += CString(roOp1SOV.GetBStr());
			roResultSOV.SetBStr(oString.AllocSysString());
			return;
		}
	}
	throw CComputeException("math - bad operands (" + Variant2String(roOp1SOV) + "," +
		Variant2String(roOp2SOV) + ")");
}

static void _compar_values(eExpTokens eOperation,
						 const CSmartOleVariant & roOp1SOV,
						const CSmartOleVariant & roOp2SOV,
						CSmartOleVariant & roResultSOV)
{
	roResultSOV.ChangeType(VT_BOOL);
	bool bRes;
	if(roOp1SOV.Type() == VT_I4 && roOp2SOV.Type() == VT_I4)
	{
		long N1 = roOp2SOV.GetLong();
		long N2 = roOp1SOV.GetLong();
		switch(eOperation)
		{
			case et_lop_eq:			// =
				bRes = (N1 == N2);
			break;
			case et_lop_gt:			// >
				bRes = (N1 > N2);
			break;
			case et_lop_ge:			// >=
				bRes = (N1 >= N2);
			break;
			case et_lop_lt:			// <
				bRes = (N1 < N2);
			break;
			case et_lop_le:			// <=
				bRes = (N1 <= N2);
			break;
			case et_lop_ne:			// <>
				bRes = (N1 != N2);
			break;
			default:
				ASSERT(false);
		}
		roResultSOV.SetBool(bRes);
		return;
	}
	else if(roOp1SOV.Type() == VT_BSTR && roOp2SOV.Type() == VT_BSTR)
	{
		CString oString1 = roOp2SOV.GetBStr();
		CString oString2 = roOp1SOV.GetBStr();
		switch(eOperation)
		{
			case et_lop_eq:			// =
				bRes = (oString1 == oString2);
			break;
			case et_lop_gt:			// >
				bRes = (oString1 > oString2);
			break;
			case et_lop_ge:			// >=
				bRes = (oString1 >= oString2);
			break;
			case et_lop_lt:			// <
				bRes = (oString1 < oString2);
			break;
			case et_lop_le:			// <=
				bRes = (oString1 <= oString2);
			break;
			case et_lop_ne:			// <>
				bRes = (oString1 != oString2);
			break;
			default:
				ASSERT(false);
		}
		roResultSOV.SetBool(bRes);
		return;
	}
	else if(roOp1SOV.Type() == VT_BOOL && roOp2SOV.Type() == VT_BOOL)
	{
		bool b1 = roOp2SOV.GetBool();
		bool b2 = roOp1SOV.GetBool();
		switch(eOperation)
		{
			case et_lop_eq:			// =
				bRes = (b1 == b2);
			break;
			case et_lop_gt:			// >
				bRes = (b1 > b2);
			break;
			case et_lop_ge:			// >=
				bRes = (b1 >= b2);
			break;
			case et_lop_lt:			// <
				bRes = (b1 < b2);
			break;
			case et_lop_le:			// <=
				bRes = (b1 <= b2);
			break;
			case et_lop_ne:			// <>
				bRes = (b1 != b2);
			break;
			default:
				ASSERT(false);
		}
		roResultSOV.SetBool(bRes);
		return;
	}
	throw CComputeException("compar - bad operands (" + Variant2String(roOp1SOV) + "," +
		Variant2String(roOp2SOV) + ")");
}

static bool Variant2Bool(const CSmartOleVariant & roSOV)
{
	if(roSOV.Type() == VT_I4)
	{
		return (roSOV.GetLong() != 0);
	}
	else if(roSOV.Type() == VT_BSTR)
	{
		return (!CString(roSOV.GetBStr()).IsEmpty());
	}
	else if(roSOV.Type() == VT_BOOL)
	{
		return roSOV.GetBool();
	}
	throw CComputeException("bool - bad operand: " + Variant2String(roSOV));
}

static void _logical_values(eExpTokens eOperation,
						 const CSmartOleVariant & roOp1SOV,
						const CSmartOleVariant & roOp2SOV,
						CSmartOleVariant & roResultSOV)
{
	roResultSOV.ChangeType(VT_BOOL);
	bool bRes;
	bool bFirst = Variant2Bool(roOp1SOV);
	bool bSecond = Variant2Bool(roOp2SOV);
	switch(eOperation)
	{
	case et_or:
		bRes = bFirst || bSecond;
	break;
	case et_and:
		bRes = bFirst && bSecond;
	break;
	default:
		ASSERT(false);
	}
	roResultSOV.SetBool(bRes);
}

static void _unary_values(eExpTokens eOperation,
						 const CSmartOleVariant & roOpSOV,
						CSmartOleVariant & roResultSOV)
{
	if(eOperation == et_not)
	{
		roResultSOV.ChangeType(VT_BOOL);
		roResultSOV.SetBool(!Variant2Bool(roOpSOV));
		return;
	}
	else if(eOperation == et_unary_neg)
	{
		if(roOpSOV.Type() == VT_I4)
		{
			roResultSOV.ChangeType(VT_I4);
			roResultSOV.SetLong(-roOpSOV.GetLong());
			return;
		}
	}
	ASSERT(false);
}

class CComputer
{
public:
	CComputer()
	{
	}
	const CString & GetLastErrorString()
	{
		return m_oLastErrorString;
	}
	
	bool Compute(CEnhancedStack<CToken> & roTokenStack,CSmartOleVariant & roSOV)
	{
		try
		{
			//TRACE0("======================\n");
			POSITION pos = roTokenStack.GetBottomPosition();
			while(pos)
			{
				CToken & roToken = roTokenStack.MoveUp(pos);
				//TRACE1("%s\n",roToken.Dump());
				switch(roToken.GetType())
				{
				case et_value:
					m_oSOVStack.Push(const_cast<CSmartOleVariant &>(roToken.GetValue()));
				break;
				case et_op_add:
				case et_op_sub:
				case et_op_mul:
				case et_op_div:
				{
					CSmartOleVariant oOp1SOV = m_oSOVStack.Pop();
					CSmartOleVariant oOp2SOV = m_oSOVStack.Pop();
					CSmartOleVariant oResultSOV;
					_math_values(roToken.GetType(),oOp1SOV,oOp2SOV,oResultSOV);
					m_oSOVStack.Push(oResultSOV);
				}
				break;
				case et_lop_eq:			// =
				case et_lop_gt:			// >
				case et_lop_ge:			// >=
				case et_lop_lt:			// <
				case et_lop_le:			// <=
				case et_lop_ne:			// <>
				{
					CSmartOleVariant oOp1SOV = m_oSOVStack.Pop();
					CSmartOleVariant oOp2SOV = m_oSOVStack.Pop();
					CSmartOleVariant oResultSOV;
					_compar_values(roToken.GetType(),oOp1SOV,oOp2SOV,oResultSOV);
					m_oSOVStack.Push(oResultSOV);
				}
				break;
				case et_or:
				case et_and:
				{
					CSmartOleVariant oOp1SOV = m_oSOVStack.Pop();
					CSmartOleVariant oOp2SOV = m_oSOVStack.Pop();
					CSmartOleVariant oResultSOV;
					_logical_values(roToken.GetType(),oOp1SOV,oOp2SOV,oResultSOV);
					m_oSOVStack.Push(oResultSOV);
				}
				break;
				case et_not:
				case et_unary_neg:
				{
					CSmartOleVariant oOpSOV = m_oSOVStack.Pop();
					CSmartOleVariant oResultSOV;
					_unary_values(roToken.GetType(),oOpSOV,oResultSOV);
					m_oSOVStack.Push(oResultSOV);
				}
				break;
				default:
					ASSERT(false);
					return false;
				}
			}
			if(m_oSOVStack.GetCount() != 1)
			{
				return false;
			}
			roSOV = m_oSOVStack.Pop();
			return true;
		}
		catch(const CComputeException & roComputeException)
		{
			m_oLastErrorString = roComputeException.GetMsg();
			return false;
		}
	}
private:
	CEnhancedStack<CSmartOleVariant> m_oSOVStack;
	CString m_oLastErrorString;
};

//-------------------------------------------------------
//		CEvaluator - creates token tree (hard-coded) and result stack
//-------------------------------------------------------

class CParseException
{
public :
	CParseException(LPCTSTR lpMsg) :
	   m_oErrorMsgString(lpMsg)
	{
	}
	LPCTSTR GetMsg() const
	{
		return m_oErrorMsgString;
	}
private:
	CString m_oErrorMsgString;
};

class CEvaluator
{
public:
	CEvaluator(LPCTSTR lpExpression,CSymbolicNameResolver * poSNR) :
		m_oTokenizer(lpExpression),
		m_poSNR(poSNR),
		m_bParseOnly(false)
	{
	}
	const CString & GetLastErrorString()
	{
		return m_oLastErrorString;
	}
	void SetParseOnlyMode()
	{
		m_bParseOnly = true;
	}
	bool Evaluate(CSmartOleVariant & roSOV)
	{
		if(!m_oTokenizer.GetToken(m_oLastToken))
		{
			return false;
		}
		try
		{
			__ParseExpression();
		}
		catch(const CParseException & roParseException)
		{
			m_oLastErrorString = roParseException.GetMsg();
			return false;
		}
		if(m_bParseOnly)
		{
			return true;
		}
		CComputer oComputer;
		if(!oComputer.Compute(m_oProgramTokenStack,roSOV))
		{
			m_oLastErrorString = oComputer.GetLastErrorString();
			return false;
		}
		return true;
	}
private:
	void __ParseExpression()
	{
		__ParseOrOperand();
		CToken oToken = LastToken();
		while(oToken.GetType() == et_or)
		{
			NextToken();
			__ParseOrOperand();
			Push(oToken);
			oToken = LastToken();
		}
	}
	void __ParseOrOperand()
	{
		__ParseAndOperand();
		CToken oToken = LastToken();
		while(oToken.GetType() == et_and)
		{
			NextToken();
			__ParseAndOperand();
			Push(oToken);
			oToken = LastToken();
		}
	}
	bool IsComparisionOperator(eExpTokens eExpToken) const
	{
		return (eExpToken == et_lop_eq) || (eExpToken == et_lop_gt) || 
			   (eExpToken == et_lop_ge) || (eExpToken == et_lop_lt) ||
			   (eExpToken == et_lop_le) || (eExpToken == et_lop_ne);
	}
	void __ParseAndOperand()
	{
		__ParseComparisionOperand();
		CToken oToken = LastToken();
		while(IsComparisionOperator(oToken.GetType()))
		{
			NextToken();
			__ParseComparisionOperand();
			Push(oToken);
			oToken = LastToken();
		}
	}
	bool IsAddtiveOperator(eExpTokens eExpToken) const
	{
		return (eExpToken == et_op_add) || (eExpToken == et_op_sub);
	}
	void __ParseComparisionOperand()
	{
		__ParseAdditiveOperand();
		CToken oToken = LastToken();
		while(IsAddtiveOperator(oToken.GetType()))
		{
			NextToken();
			__ParseAdditiveOperand();
			Push(oToken);
			oToken = LastToken();
		}
	}
	bool IsMultiplicativeOperator(eExpTokens eExpToken) const
	{
		return (eExpToken == et_op_mul) || (eExpToken == et_op_div);
	}
	void __ParseAdditiveOperand()
	{
		__ParseMultiplicationOperand();
		CToken oToken = LastToken();
		while(IsMultiplicativeOperator(oToken.GetType()))
		{
			NextToken();
			__ParseMultiplicationOperand();
			Push(oToken);
			oToken = LastToken();
		}
	}
	void __ParseMultiplicationOperand()
	{
		CToken oToken = LastToken();
		while(oToken.GetType() == et_op_add)	//unary +		- just skip
		{
			NextToken();
			oToken = LastToken();
		}
		if(oToken.GetType() == et_not || oToken.GetType() == et_op_sub)
		{
			NextToken();
			__ParseMultiplicationOperand();
			
			if(oToken.GetType() == et_op_sub)		//to direrrentiate operations (substraction and unary minus)
			{
				oToken.SetType(et_unary_neg);
			}
			Push(oToken);
		}
		else
		{
			__ParseItem();
		}
	}
	void __ParseItem()
	{
		CToken oToken = LastToken();
		switch(oToken.GetType())
		{
		case et_symbol:
		{
			CSmartOleVariant oSOV;
			if(!GetSymbolValue(CString(oToken.GetValue().GetBStr()),oSOV))
			{
				if(!m_bParseOnly)
				{
					throw CParseException("undefined symbol: " + CString(oToken.GetValue().GetBStr()));
				}
			}
			//resolve var value
			oToken.SetValue(oSOV);
			oToken.SetType(et_value);
			//no break;
		}
		case et_value:
			{
				Push(oToken);
				NextToken();
				return;
			}
		case et_left_bra:
			{
				NextToken();
				__ParseExpression();
				if(LastToken().GetType() == et_right_bra)
				{
					NextToken();
					return;
				}
			}
		}
		throw CParseException(_T("expected value"));
	}
	
	void NextToken()
	{
		if(!m_oTokenizer.GetToken(m_oLastToken))
		{
			m_oLastToken.SetType(et_none);
		}
		if(m_oLastToken.GetType() == et_error)
		{
			throw CParseException(_T("syntax error"));
		}
	}
	const CToken & LastToken() const
	{
		return m_oLastToken;
	}

	bool GetSymbolValue(LPCTSTR lpSymbol,CSmartOleVariant & roValueSOV)
	{
		if(m_poSNR)
		{
			return m_poSNR->GetSymbolValue(lpSymbol,roValueSOV);
		}
		else
		{
			return false;
		}
	}
	void Push(CToken & roToken)
	{
		m_oProgramTokenStack.Push(roToken);
	}

	CToken m_oLastToken;
	CTokenizer m_oTokenizer;
	CEnhancedStack<CToken> m_oProgramTokenStack;		//evaluation "program" code
	CSymbolicNameResolver * m_poSNR;
	bool					m_bParseOnly;
	CString					m_oLastErrorString;
};

#else
	#error __FILE__ already included
#endif
