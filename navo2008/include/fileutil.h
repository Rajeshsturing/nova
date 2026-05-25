/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	File System related Utility

	CStreamHolder
	CFileRemover
	CBufferToFile
*/

#ifndef _FILEUTIL_H_
#define _FILEUTIL_H_

bool CheckEnvVariablePath(LPCTSTR pcVarName = NULL);	//check path described in Enviroment Variable

//kopiuje strumieñ do strumienia, "generic" implementation of IStream::CopyTo
HRESULT IStream_CopyTo(IStream * pSrcIStream,IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
			ULARGE_INTEGER * pulBytesRead = NULL, ULARGE_INTEGER * pulBytesWritten = NULL);

inline bool CheckTmpVariable()							//check path described in TEMP
{
	return CheckEnvVariablePath();
}

CString GenerateUniqueFileName(LPCTSTR pcPrefix, LPCTSTR pcExtension);
void CleanNavoTemporaryFiles();

//IStream na pliku
class CFileStream: public CCmdTargetInterface
{
public:
	static SCP <IStream> Get(LPCTSTR pcFileName, bool bCoded, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes = 0)
	{
		return NewSCP(new CFileStream(pcFileName, bCoded, dwDesiredAccess, dwShareMode, dwCreationDisposition, dwFlagsAndAttributes))->GetStream();
	};

	CFileStream(LPCTSTR pcFileName, bool bCoded, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes = 0):
		m_hFile(INVALID_HANDLE_VALUE),
		m_oStreamNameString(pcFileName),
		m_bCoded(bCoded),
		m_grfMode(STGM_DIRECT),
		m_nSeekPtr(0)
	{
		_CreateFile(dwDesiredAccess, dwShareMode, dwCreationDisposition, dwFlagsAndAttributes);
		EnableAutomation();

		if (dwDesiredAccess | GENERIC_READ)
		{
			m_grfMode |= STGM_READ;
		};
		if (dwDesiredAccess | GENERIC_WRITE)
		{
			m_grfMode |= STGM_WRITE;
		};
		if (!(dwShareMode & FILE_SHARE_READ))
		{
			m_grfMode |= STGM_SHARE_DENY_READ;
		};
		if (!(dwShareMode & FILE_SHARE_WRITE))
		{
			m_grfMode |= STGM_SHARE_DENY_WRITE;
		};
//		TRACE1("CFileStream ctor 1: [%s]\n",pcFileName);
	};
	CFileStream(LPCTSTR pcFileName, HANDLE hFile,long nSeekPtr,DWORD grfMode,bool bCoded) :
		m_oStreamNameString(pcFileName),
		m_hFile(hFile),
		m_nSeekPtr(nSeekPtr),
		m_bCoded(bCoded),
		m_grfMode(grfMode)
	{
		EnableAutomation();
//		TRACE1("CFileStream ctor 2: [%s]\n",pcFileName);
	}
	~CFileStream()
	{
		::CloseHandle(m_hFile);
//		TRACE1("CFileStream dtor: [%s]\n",m_oStreamNameString);
	};
	HANDLE GetHandle()
	{
		return m_hFile;
	};
	SCP <IStream> GetStream()
	{
		SCP <IStream> iStreamSCP;
		iStreamSCP.QueryInterface(GetUnknown());
		return iStreamSCP;
	};

protected:
	//{{AFX_DISPATCH(CFileStream)
	afx_msg VARIANT GetValueAUTO();
	afx_msg void SetValueAUTO(const VARIANT FAR& newValue);

	//}}AFX_DISPATCH
	BEGIN_INTERFACE_PART(Stream, IStream)
		HRESULT STDMETHODCALLTYPE Read(void *pData, unsigned long lLength, unsigned long *plBytesRead)
		{
			METHOD_PROLOGUE(CFileStream, Stream)
			ALL_TRY
			{
				//zerujemy
				if (plBytesRead)
				{
					*plBytesRead = 0;
				};
				DWORD lDataRead = 0;
				if(!::ReadFile(pThis->m_hFile,pData,lLength,&lDataRead,NULL))
				{
					return S_FALSE;
				}
				if (plBytesRead)
				{
					*plBytesRead = lDataRead;
				};
				if (pThis->m_bCoded)
				{
					DecodeBuffer(pData, lDataRead);
				};
				pThis->m_nSeekPtr += lDataRead;
			}
			ALL_CATCH(CNavoException &)
			{
				return DISP_E_EXCEPTION;
			};
			return S_OK;
		}
		HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER liOffset, unsigned long lOrigin,
			ULARGE_INTEGER * pliNewPointer)
		{
			METHOD_PROLOGUE(CFileStream, Stream)
			ALL_TRY
			{
				long lNewOffset = ::SetFilePointer(pThis->m_hFile,lohyper(liOffset.QuadPart),NULL,lOrigin);

				if(lNewOffset == -1)
				{
					return S_FALSE;
				}
				if (pliNewPointer)
				{
					pliNewPointer->QuadPart = lNewOffset;
				};
				pThis->m_nSeekPtr = lNewOffset;
			}
			ALL_CATCH(CNavoException &)
			{
				return DISP_E_EXCEPTION;
			};
			return S_OK;
		};
		HRESULT STDMETHODCALLTYPE Write(const void *pData, unsigned long lLength, unsigned long *plBytesWritten)
		{
			METHOD_PROLOGUE(CFileStream, Stream)
			ALL_TRY
			{
				if (plBytesWritten)
				{
					*plBytesWritten = 0;
				};
				CArray <char, char> oBuffer;
				if (pThis->m_bCoded)
				{
					oBuffer.SetSize(lLength);
					memcpy(oBuffer.GetData(), pData, lLength);
					EncodeBuffer(oBuffer.GetData(), lLength);
					pData = oBuffer.GetData();
				};
				DWORD lBytesWritten = 0;
				if(!::WriteFile(pThis->m_hFile,pData,lLength,&lBytesWritten,NULL))
				{
					return S_FALSE;
				}
				if (plBytesWritten)
				{
					*plBytesWritten = lBytesWritten;
				};
				pThis->m_nSeekPtr += lBytesWritten;
			}
			ALL_CATCH(CNavoException &)
			{
				return DISP_E_EXCEPTION;
			};
			return S_OK;
		}
		HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER ulSize)
		{
			METHOD_PROLOGUE(CFileStream, Stream)
			LARGE_INTEGER lOffset;
			lOffset.QuadPart = __int64(ulSize.QuadPart); 
			HRESULT hr = Seek(lOffset, STREAM_SEEK_SET,NULL);
			if(hr != S_OK)
			{
				return hr;
			}
			if(::SetEndOfFile(pThis->m_hFile))
			{
				return S_OK;
			}
			else
			{
				DWORD dwLastError = ::GetLastError();
				if(dwLastError == ERROR_DISK_FULL)
				{
					return STG_E_MEDIUMFULL;
				}
				else
				{
					return E_FAIL;
				}
			}
		};
		HRESULT STDMETHODCALLTYPE CopyTo(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
			ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten)
		{
			METHOD_PROLOGUE(CFileStream, Stream)
		
			return IStream_CopyTo(this,pDestIStream,ulToCopy,pulBytesRead,pulBytesWritten);
		}

		HRESULT STDMETHODCALLTYPE Commit(unsigned long)
		{
			ASSERT(false);
			return E_FAIL;
		};
		HRESULT STDMETHODCALLTYPE Revert()
		{
			ASSERT(false);
			return E_FAIL;
		};
		HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
		{
			ASSERT(false);
			return E_FAIL;
		};
		HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long)
		{
			ASSERT(false);
			return E_FAIL;
		};
		HRESULT STDMETHODCALLTYPE Stat(STATSTG * pStatStg, unsigned long lFlags);
		HRESULT STDMETHODCALLTYPE Clone(IStream ** ppIStream)
		{
			METHOD_PROLOGUE(CFileStream, Stream)

			*ppIStream = NULL;
			HANDLE hFile;
			if(!duplicate_os_handle(pThis->m_hFile,hFile))
			{
				return E_FAIL;
			}
			*ppIStream = NewSCP(new CFileStream(pThis->m_oStreamNameString,
				hFile,pThis->m_nSeekPtr,pThis->m_grfMode,pThis->m_bCoded))->GetStream().Detach();
			return S_OK;
		};
	END_INTERFACE_PART(Stream)
	DECLARE_INTERFACE_MAP();
	DECLARE_DISPATCH_MAP()

	void _CreateFile(DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes);

	CString m_oStreamNameString;
	long  m_nSeekPtr;
	HANDLE m_hFile;
	DWORD m_grfMode;
	bool m_bCoded;
};


//-------CStreamHolder-----------------------
//
// obudowa na IStream. Nie ma zadnej funkcjonalnosci - rzuca tylko wyjatki
// gdy metody IStream sie nie powodza.
//
// UWAGA! Nie jest to klasyczny holder
//---------------------------------------------

class CStreamHolder
{
public:
	CStreamHolder()
	{
	}
	CStreamHolder(SCP <IStream> & iStreamSCP):
		m_oTSCP(iStreamSCP)
	{
	};
	~CStreamHolder()
	{
	};
	SCP <IStream> & GetStream()
	{
		return m_oTSCP;
	};
	void SetStream(SCP<IStream> & rpIStreamSP)
	{
		m_oTSCP = rpIStreamSP;
	}
	
	unsigned long Read(void * pData, unsigned long lLength);

	unsigned long SeekToBegin()
	{
		return Seek(0, STREAM_SEEK_SET);
	}
	unsigned long SeekToEnd()
	{
		return Seek(0, STREAM_SEEK_END);
	}
	unsigned long Seek(long liOffset, unsigned long lOrigin)
	{
		ASSERT(m_oTSCP.PointsObject());
		ULARGE_INTEGER oNewPos;
		LARGE_INTEGER oOffset;
		oOffset.QuadPart = liOffset;
		HRESULT hr = m_oTSCP->Seek(oOffset, lOrigin, &oNewPos);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_UNABLE_TO_SEEK_IN_STREAM, IDPAGE_NOTAVAILABLE, 
				SCODE_To_String(hr));
		};
		return (unsigned long)oNewPos.QuadPart;
	};
	void Stat(STATSTG & pStatStg, CBStr * pBStr = NULL)
	{
		long lFlags;
		if (pBStr)
		{
			lFlags = STATFLAG_DEFAULT;
		}
		else
		{
			lFlags = STATFLAG_NONAME;
		};
		HRESULT hr = m_oTSCP->Stat(&pStatStg, lFlags);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_UNABLE_TO_GET_STREAM_INFO, 
				IDPAGE_NOTAVAILABLE, SCODE_To_String(hr));
		};
		if (pBStr)
		{
			pBStr->Attach(pStatStg.pwcsName, CBStr::COALLOC);
		};
	};
	void WritePascalString(LPCTSTR pString)
	{
		long nStrLen = 0;
		if(pString)
		{
			nStrLen = sizeof(TCHAR) * _tcslen(pString);
			Write(&nStrLen,sizeof(long));
			Write(reinterpret_cast<const void*>(pString),nStrLen);
		}
		else
		{
			Write(&nStrLen,sizeof(long));
		}
	}
	void WriteString(LPCTSTR pString)
	{
		Write(reinterpret_cast<const void*>(pString),
			sizeof(TCHAR) * _tcslen(pString));
	}
	CString ReadPascalString()
	{
		long nStrLen;
		CString oString;

		Read(&nStrLen,sizeof(long));
		if(nStrLen != 0)
		{
			Read(oString.GetBuffer(nStrLen),nStrLen);
#ifdef _NAVODOTNET
			oString.ReleaseBuffer(nStrLen);
#else
			oString.ReleaseBuffer();
#endif
		}
		return oString;
	}
	void Write(const void * pData, unsigned long lLength)
	{
		unsigned long lBytesWritten;
		Write(pData, lLength, &lBytesWritten);
		if (lBytesWritten != lLength)
		{
			ThrowNavoException2(ERCO_UNABLE_TO_WRITE_ALL_TO_STREAM, IDPAGE_NOTAVAILABLE,
				lBytesWritten,lLength);
		};
	};
	void Write(const void * pData, unsigned long lLength, unsigned long * plBytesWritten)
	{
		ASSERT(m_oTSCP.PointsObject());
		HRESULT hr = m_oTSCP->Write(pData, lLength, plBytesWritten);
		if (hr != S_OK)
		{
			ThrowNavoException1(ERCO_UNABLE_TO_WRITE_TO_STREAM, IDPAGE_NOTAVAILABLE,
				SCODE_To_String(hr));
		};
	};
	bool IsStream() const
	{
		return m_oTSCP.PointsObject();
	}
private:
	SCP <IStream> m_oTSCP;
};


//------------- CStreamSeekPtrHolder ------------------
//
//holder na zmianê seek pointera w streamie
//
//---------------------------------------------

class CStreamSeekPtrHolder
{
public:
	CStreamSeekPtrHolder(IStream * pIStream) :
		m_pIStream( pIStream )
	{
		LARGE_INTEGER liZero;
		liZero.QuadPart=0;
		VERIFY(pIStream->Seek(liZero,STREAM_SEEK_CUR,(ULARGE_INTEGER*)&m_liSizeOld) == S_OK);
	}
	~CStreamSeekPtrHolder()
	{
		if(m_pIStream)
		{
			VERIFY(m_pIStream->Seek(m_liSizeOld,STREAM_SEEK_SET,NULL) == S_OK);
		}
	}
	void OK()
	{
		m_pIStream = NULL;
	}
private:
	LARGE_INTEGER m_liSizeOld;
	IStream * m_pIStream;
};


//------------- CFileRemover ------------------
//
//holder na usuwanie plików
//
//---------------------------------------------


class CFileRemover: public CInterface__
{
public:
	CFileRemover():
		m_bRemove(true)
	{
	};
	CFileRemover(const TCHAR * pcFileName):
		m_bRemove(true),
		m_oFileName(pcFileName)
	{
	};
	~CFileRemover()
	{
		if (m_bRemove)
		{
			TryToRemove();
		};
	};
	void DontRemove()
	{
		m_bRemove = false;
	};
	void SetFileName(CString & roFileName)
	{
		m_oFileName = roFileName;
	};
	const CString & GetFileName() const
	{
		return m_oFileName;
	};

protected:
	void TryToRemove();

	CString m_oFileName;

private:
	bool m_bRemove;
};

//------------- CBufferToFile ------------------
//
//
//---------------------------------------------

class CBufferToFile : public CInterface__
{
public:
	CBufferToFile() :
		m_lBufferSize(8192),
		m_lPosition(0),
		m_lBufferLength(0),
		m_bEndOfFile(false)
	{
		//for template operations
	}
	CBufferToFile(SCP <IStream> & riStreamSCP, long lBufferSize = 8192):
		m_iStreamSCP(riStreamSCP),
		m_lBufferSize(lBufferSize),
		m_lPosition(0),
		m_lBufferLength(0),
		m_bEndOfFile(false)
	{
		m_acBuffer.SetSize(m_lBufferSize);
		ReadBlock();
	};
	~CBufferToFile()
	{
	};
	char GetChar()
	{
		register char cResult = '\0';
		if (!IsEndOfFile())
		{
			if (m_lPosition < m_lBufferLength)
			{
				cResult = m_acBuffer[m_lPosition++];
			};
			if (m_lPosition == m_lBufferSize)
			{
				ReadBlock();
			};
		};
		return cResult;
	};
	void MoveBack();
	bool IsEndOfFile() const
	{
		return m_lPosition == m_lBufferLength && m_bEndOfFile;
	};
	bool IsNotEndOfFile() const
	{
		return m_lPosition < m_lBufferLength || !m_bEndOfFile;
	};
	long GetCurrentPosition()
	{
		return Seek(0) + m_lPosition - m_lBufferLength;
	};
	long ReadLine(CArray <TCHAR, TCHAR &> & raSource, bool bWithCR);
	
	virtual void operator = (const CBufferToFile & roBufferToFile)
	{
			m_acBuffer.RemoveAll();
			m_acBuffer.Append(roBufferToFile.m_acBuffer);
			m_lBufferSize	= roBufferToFile.m_lBufferSize;
			m_lBufferLength	= roBufferToFile.m_lBufferLength;
			m_lPosition		= roBufferToFile.m_lPosition;
			m_bEndOfFile	= roBufferToFile.m_bEndOfFile;
			m_iStreamSCP	= (const_cast<CBufferToFile &>(roBufferToFile)).m_iStreamSCP;
			(const_cast<CBufferToFile &>(roBufferToFile)).m_iStreamSCP = 0;
	}
	void ReadBlock()
	{
		ReadBlockFromInput();
		m_lPosition = 0;
		if (m_lBufferLength < m_lBufferSize)
		{
			m_bEndOfFile = true;
		};
	};
private:
	enum EOffsetBase
	{
		BEGIN,
		CURRENT,
	};
	SCP <IStream> & GetStream()
	{
		ASSERT(m_iStreamSCP.PointsObject());
		return m_iStreamSCP;
	};
	void ReadBlockFromInput()
	{
		ASSERT(m_iStreamSCP.PointsObject());
		CStreamHolder oSH(GetStream());
		m_lBufferLength = oSH.Read(m_acBuffer.GetData(), m_lBufferSize);
	};
	long Seek(long lSeek, EOffsetBase eBase = CURRENT);

	CArray <char, char &> m_acBuffer;
	long m_lBufferSize, m_lBufferLength, m_lPosition;
	bool m_bEndOfFile;
	SCP <IStream> m_iStreamSCP;
};

class CStreamLineReader
{
public:
	CStreamLineReader(SCP<IStream> poInputStreamSP) :
		m_poInputStreamSP(poInputStreamSP),
		m_oBuffer2File(poInputStreamSP)
	{
		m_oLineArray.SetSize(8192);
	}
	virtual bool _get_line(CString & roString)
	{
		long nLength = m_oBuffer2File.ReadLine(m_oLineArray,false);
		if(nLength == -1)
		{
			return false;
		}
		roString = m_oLastLineString = CString(m_oLineArray.GetData(),nLength);
		return true;
	}
	const CString & _get_last_line_again() const
	{
		return m_oLastLineString;
	}
protected:
	CString		 m_oLastLineString;
	SCP<IStream> m_poInputStreamSP;
	CBufferToFile m_oBuffer2File;
	CArray <TCHAR, TCHAR &> m_oLineArray;
};


class CStreamBuffer
{
public:
	CStreamBuffer(SCP<IStream> poStreamSP);
	TCHAR _get_char();
	void  _unget_char();
private:
	TCHAR m_cCharQueue[16];
	long  m_nQueueStartPos;
	long  m_nQueueEndPos;

	CBufferToFile m_oBuffer2Stream;
};

//otwórz strumieñ z pliku
inline SCP <IStream> OpenFileStream(LPCTSTR pcFileName, bool bCoded, 
	DWORD dwDesiredAccess, DWORD dwShareMode, 
	DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes = 0)
{
	return CFileStream::Get(pcFileName, bCoded, dwDesiredAccess, dwShareMode, dwCreationDisposition, dwFlagsAndAttributes);
};

//----------------------------------------------------------------------------------
//UPRASZCZACZE
//----------------------------------------------------------------------------------

inline SCP<IStream> OpenFileStream_Read(LPCTSTR pcFileName,bool bCoded = false)
{
	return OpenFileStream(pcFileName,bCoded,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_DELETE,OPEN_EXISTING);
}

inline SCP<IStream> CreateFileStream_Write(LPCTSTR pcFileName, bool bCoded = false)
{
	return OpenFileStream(pcFileName,bCoded,GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_DELETE,CREATE_ALWAYS);
}

inline SCP<IStream> CreateTempFileStream()
{
	CString oFileNameString = GenerateUniqueFileName(_T("NV"),_T("TMP"));
	return OpenFileStream(oFileNameString,true,GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_DELETE,CREATE_ALWAYS,FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_TEMPORARY);
}

//----------------------------------------------------------------------------------

//otwórz strumieñ z URL
SCP <IStream> OpenURLStream(const TCHAR * pszURL);

//otwórz strumieñ na sockecie
SCP<IStream> OpenSocketStream(LPCTSTR lpServer,long nPort,bool bWaitingRead);

//otwórz strumieñ na RAMie
SCP <IStream> CreateStreamInMemory(HGLOBAL hGlobal = NULL);

//ustaw (zmieñ rozszerzenie pliku o podanej nazwie)
CString SetFileNameExtension(CString oFileNameString, LPCTSTR pcFileExtension);

long GetDirectoryDiskUsage(CString oDirectoryString);

//Tworzenie katalogu (rzuca wyj¹tek)
void NavoCreateDirectory(const TCHAR *pcDirName);

//Tworzenie i usuwanie drzewa katalogów
void NavoCreateDirectoryTree(CString oPathNameString);
bool NavoRemoveDirectoryTree(CString oDirectoryString, bool bThrowIfFailed = false, bool bOnlyDirectoryTree = false);

//usuwa plik jeœli siê da, mo¿e zmieniæ atrybuty (RO)
bool NavoDeleteFile(LPCTSTR lpFileName);

//zwraca pe³n¹ nazwê pliku (lower case)
CString NavoGetFullPathName(LPCTSTR pcFileName);

//zwraca d³ugoœæ strumienia
long GetStreamSize(IStream * pStream);
__int64 get_stream_size64(IStream * pStream);

//zapisuje strumieñ w pliku. Przesuwa seek ptr !
void SaveStreamToFile(SCP <IStream> & iStreamSCP, LPCTSTR pcFileName, bool bEncode, ULONGLONG unLength = MAXLONGLONG);

interface INotificationSink;

HRESULT SaveStreamToFile(SCP <IStream> & iStreamSCP, CFile * pDestinationFile,
		INotificationSink * poNotificationSink = NULL,long nLength = MAXLONG);

HRESULT ReadStreamFromFile(CFile * pSourceFile,SCP <IStream> & iStreamSCP, 
		INotificationSink * poNotificationSink = NULL,long nLength = MAXLONG);

void normalize_name_4_path(LPCTSTR lpAnyName,CString & roNormalizedPathString);

//---------------------------------
//INLINES
//---------------------------------
inline void EnsureEndingBackslash(CString & roString)
{
	if(roString.IsEmpty())
	{
		roString = '\\';
	}
	else
	{
		if(roString[roString.GetLength() - 1] != '\\')
		{
			roString += '\\';
		}
	}
}

inline CString SetFileNameExtension(CString oFileNameString, LPCTSTR pcFileExtension)
{
	long lIndex = oFileNameString.ReverseFind('.');
	if (lIndex != -1)
	{
		if (oFileNameString.ReverseFind('\\') > lIndex || oFileNameString.ReverseFind('/') > lIndex)
		{
			lIndex = -1;
		};
	};
	if (lIndex == -1)
	{
		lIndex = oFileNameString.GetLength();
	};
	return CString(oFileNameString, lIndex) + '.' + pcFileExtension;
};

inline SCP <IStream> CreateStreamInMemory(HGLOBAL hGlobal)
{
	SCP <IStream> iStreamSCP;
	HRESULT hr = ::CreateStreamOnHGlobal(hGlobal, hGlobal == NULL, &iStreamSCP.GetRawPointer()); 
	if (S_OK != hr)
	{
		ThrowNavoException1(ERCO_CREATESTREAMONHGLOBAL_FAILED, IDPAGE_NOTAVAILABLE,
			SCODE_To_String(hr));
	};
	return iStreamSCP;
};

inline CString NavoGetCurrentDir()
{
	CString oStr;
	if (!::GetCurrentDirectory(_MAX_PATH + 1, oStr.GetBuffer(_MAX_PATH)))
	{
		DWORD dwErrorCode = ::GetLastError();
		ThrowNavoException1(ERCO_UNABLETOGETCURRENTDIRECTORY, IDPAGE_NOTAVAILABLE, 
			GetLastError_To_String(dwErrorCode));
	};
	oStr.ReleaseBuffer();
	return oStr;
};

inline void NavoSetCurrentDir(LPCTSTR pcNewDir)
{
	if (!::SetCurrentDirectory(pcNewDir))
	{
		DWORD dwErrorCode = ::GetLastError();
		ThrowNavoException2(ERCO_UNABLETOSETCURRENTDIRECTORY, IDPAGE_NOTAVAILABLE, 
			pcNewDir, GetLastError_To_String(dwErrorCode));
	};
};

class CDirectoryChangeHolder
{
public:
	CDirectoryChangeHolder(LPCTSTR pcNewDir):
		m_oOldDirString(NavoGetCurrentDir())
	{
		NavoSetCurrentDir(pcNewDir);
	};
	~CDirectoryChangeHolder()
	{
		try
		{
			NavoSetCurrentDir(m_oOldDirString);
		}
		catch(...)
		{
			ASSERT(false);
		};
	};

private:
	CString m_oOldDirString;
};

inline CString ShortFileNameFromLongName(LPCTSTR lpLongName)
{
	CString oString;
	if(!::GetShortPathName(lpLongName,oString.GetBuffer(_MAX_PATH),_MAX_PATH))
	{
		oString.SetAt(0,'\0');
	}
	oString.ReleaseBuffer();
	return oString;
}


inline SCP<IStream> OpenFileStream_Read_On_SOV(const CSmartOleVariant & roSOV)
{
	switch(roSOV.Type())
	{
	case VT_BSTR:
	{
		CString oURLString(roSOV.GetBStr());
		if(0 == _tcsnicmp(oURLString,_T("url:"),4))			//4=="url:"
		{
			return OpenURLStream(LPCTSTR(oURLString)+4);
		}
		else
		{
			return OpenFileStream_Read(oURLString);
		}
	}
	break;
	case VT_UNKNOWN:
	{
		return roSOV.GetStream();
	}
	break;
	case VT_DISPATCH:
	{
		SCP<IStream> poIStreamSP;
		poIStreamSP.QueryInterface(roSOV.GetDispatch());
		return poIStreamSP;
	}
	break;
	case (VT_DISPATCH | VT_BYREF):
	{
		LPDISPATCH pDispatch = *(roSOV.GetVariantRef().ppdispVal);
	
		SCP<IStream> poIStreamSP;
		poIStreamSP.QueryInterface(pDispatch);
		return poIStreamSP;
	}
	break;
	case (VT_ARRAY | VT_UI1) :
	{
		SCP <IStream> poStreamSP = CreateStreamInMemory();
		COleSafeArray oSafeArray;
		oSafeArray.Attach(const_cast<CSmartOleVariant&>(roSOV).GetVariantRef());
		DWORD dwElementCount = oSafeArray.GetOneDimSize();
		CSafeArrayAccessHolder<TCHAR> oSAAH(oSafeArray);
		CStreamHolder oSH(poStreamSP);
		oSH.Write(oSAAH.GetData(),dwElementCount);
		oSH.SeekToBegin();
		return poStreamSP;
	}
	break;
	case (VT_VARIANT | VT_BYREF):		//takie coœ dostajemy z VBScript
	{
		VARIANT * pVariant = roSOV.GetVariantRef().pvarVal;
		ASSERT(pVariant);
		//ten _cast to po to by nie robiæ niepotrzenie obiektu SOV
		return OpenFileStream_Read_On_SOV(reinterpret_cast<const CSmartOleVariant&>(*pVariant));	//Uwaga! wywo³uje siebie ale ju¿ bez byRef
	}
	default:
		ASSERT(false);
	}
	return SCP<IStream>();
}

inline SCP<IStream> CreateFileStream_Write_On_SOV(const CSmartOleVariant & roSOV,
	SCP<CFileRemover> & rpoFileRemoverSP)
{
	switch(roSOV.Type())
	{
	case VT_BSTR:
	{
		CString oPackageNameString = CString(roSOV.GetBStr());
		rpoFileRemoverSP = NewSCP(new CFileRemover(oPackageNameString));
		return CreateFileStream_Write(oPackageNameString);
	}
	break;
	case VT_UNKNOWN:
	{
		return roSOV.GetStream();
	}
	break;
	case VT_DISPATCH:
	{
		SCP<IStream> poIStreamSP;
		poIStreamSP.QueryInterface(roSOV.GetDispatch());
		return poIStreamSP;
	}
	break;
	case (VT_DISPATCH | VT_BYREF):
	{
		LPDISPATCH pDispatch = roSOV.GetVariantRef().pdispVal;

		SCP<IStream> poIStreamSP;
		poIStreamSP.QueryInterface(pDispatch);
		return poIStreamSP;
	}
	break;
	case (VT_VARIANT | VT_BYREF):		//takie coœ dostajemy z VBScript
	{
		VARIANT * pVariant = roSOV.GetVariantRef().pvarVal;
		ASSERT(pVariant);
		//ten _cast to po to by nie robiæ niepotrzenie obiektu SOV
		return CreateFileStream_Write_On_SOV(reinterpret_cast<const CSmartOleVariant&>(*pVariant),rpoFileRemoverSP);
	}
	break;
	case VT_EMPTY:
		return SCP<IStream>();
	break;
	default:
		ASSERT(false);
	}
	return SCP<IStream>();
}

//returns pointer to compressed stream (pull mode read). Entry stream : any binary
SCP <IStream> CompressStream(SCP <IStream> & rpoInputStreamSP);

//returns pointer to uncompressed stream (pull mode read). Entry stream : compressed with CompressStream
SCP <IStream> UncompressStream(SCP <IStream> & rpoInputStreamSP);

//returns pointer to base64 encoded stream (pull mode read). Entry stream : any binary
SCP <IStream> Base64EncodeStream(SCP <IStream> & rpoInputStreamSP);

//returns pointer to base64 decoded stream (pull mode read). Entry stream: base 64 encoded
SCP <IStream> Base64DecodeStream(SCP <IStream> & rpoInputStreamSP);

//---------------------------------------------------------------------
inline void normalize_name_4_path(LPCTSTR lpAnyName,CString & roNormalizedPathString)
{
	TCHAR cBuffer[ _MAX_PATH ];
	_tcsncpy(cBuffer,lpAnyName,_MAX_PATH-1);
	cBuffer[_MAX_PATH-1] = '\0';
	LPTSTR pcPtr = cBuffer;

	while(*pcPtr)
	{
		if(!IsAlphaNum(*pcPtr))
		{
			*pcPtr = '_';
		}
		pcPtr++;
	}
	roNormalizedPathString = cBuffer;
}


//-------------------------- stream buffer ---------------------

inline CStreamBuffer::CStreamBuffer(SCP<IStream> poStreamSP) :
	m_nQueueStartPos(0),
	m_nQueueEndPos(0),
	m_oBuffer2Stream(poStreamSP)
{
}

inline TCHAR CStreamBuffer::_get_char()
{
	if(m_nQueueStartPos == m_nQueueEndPos)	//empty
	{
		m_cCharQueue[ m_nQueueEndPos++ ] = m_oBuffer2Stream.GetChar();
		if(m_nQueueEndPos == sizeof(m_cCharQueue) / sizeof(TCHAR))
		{
			m_nQueueEndPos = 0;
		}
	}
	TCHAR cChar = m_cCharQueue[ m_nQueueStartPos++ ];
	if(m_nQueueStartPos == sizeof(m_cCharQueue) / sizeof(TCHAR))
	{
		m_nQueueStartPos = 0;
	}
	return cChar;
}

inline void CStreamBuffer::_unget_char()
{
	if(m_nQueueStartPos == 0)
	{
		m_nQueueStartPos = sizeof(m_cCharQueue) / sizeof(TCHAR);
	}
	--m_nQueueStartPos; 
}

#else
	#error __FILE__ already included
#endif
