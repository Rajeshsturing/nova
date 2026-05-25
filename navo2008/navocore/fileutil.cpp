/*
NAVO Sp. z o.o. (2001)

NAVO Enterprise

File System related Utility
*/

#include "StdAfx.h"
#include "..\navopx\navopx.h"

#ifndef _MINI_CORE_
#include "..\include\interfaceutil.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR * _g_pchNAVO2001Temporary		= _T("TempFiles");

#ifndef _MINI_CORE_

CWinVersion _g_FileStream_WinWersion;

BEGIN_INTERFACE_MAP(CFileStream, CCmdTargetInterface)
	INTERFACE_PART(CFileStream, IID_IStream, Stream)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CFileStream, Stream)  

	HRESULT STDMETHODCALLTYPE CFileStream::XStream::Stat(STATSTG * pStatStg, unsigned long lFlags)
{
	METHOD_PROLOGUE(CFileStream, Stream)
		ALL_TRY
	{
		if (!pStatStg)
		{
			return E_FAIL;
		};
		::ZeroMemory(pStatStg, sizeof(STATSTG));
		CBStr oFileNameBStr (pThis->m_oStreamNameString, CBStr::COALLOC);
		if (::GetClassFile(oFileNameBStr, &pStatStg->clsid) != S_OK)
		{
			pStatStg->clsid = CLSID_NULL;
		};
		if (!::GetFileTime((HANDLE)pThis->m_hFile, &pStatStg->ctime, &pStatStg->atime, &pStatStg->mtime))
		{
			return E_FAIL;
		};
		pStatStg->cbSize.QuadPart = (DWORDLONG)::GetFileSize((HANDLE)pThis->m_hFile, NULL);
		if (pStatStg->cbSize.QuadPart == (DWORDLONG)-1L)
		{
			return E_FAIL;
		};
		pStatStg->type = STGTY_STREAM;
		pStatStg->grfMode = pThis->m_grfMode;
		pStatStg->grfLocksSupported = 0;
		if (lFlags == STATFLAG_DEFAULT)
		{
			pStatStg->pwcsName = oFileNameBStr.Detach();
		};
		return  S_OK;
	}
	ALL_CATCH(...)
	{
		ASSERT(false);
		return E_OUTOFMEMORY;
	};
	return E_OUTOFMEMORY;
};

void CFileStream::_CreateFile(DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes)
{
	BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);	//from MFC

	ASSERT(AfxIsValidString(m_oStreamNameString));
	TCHAR acFullNameTemp[_MAX_PATH];
	AfxFullPath(acFullNameTemp, m_oStreamNameString);
	m_oStreamNameString = acFullNameTemp;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if(_g_FileStream_WinWersion.GetVersion() < CWinVersion::WinNT)
	{
		dwShareMode &= ~FILE_SHARE_DELETE;	//dla Win9x wy³¹cz tê flagê
	}
	HANDLE hFile = ::CreateFile(m_oStreamNameString, dwDesiredAccess, dwShareMode, &sa, 
		dwCreationDisposition, dwFlagsAndAttributes, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_hFile = hFile;
		return;
	}
	DWORD dwErrorCode = ::GetLastError();
	if (dwErrorCode == ERROR_ACCESS_DENIED)
	{
		if(::SetFileAttributes(m_oStreamNameString,
			::GetFileAttributes(m_oStreamNameString) & ~(DWORD(FILE_ATTRIBUTE_READONLY))))
		{
			hFile = ::CreateFile(m_oStreamNameString, dwDesiredAccess, dwShareMode, &sa, 
				dwCreationDisposition, dwFlagsAndAttributes, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				m_hFile = hFile;
				return;
			}
		}
	}

	ThrowNavoException2(ERCO_UNABLE_TO_OPEN_FILE, IDPAGE_NOTAVAILABLE, (LPCTSTR)m_oStreamNameString, 
		GetLastError_To_String(dwErrorCode));
}

BEGIN_DISPATCH_MAP(CFileStream, CCmdTargetInterface)
	//{{AFX_DISPATCH_MAP(CFileStream)
	DISP_PROPERTY_EX(CFileStream, "value", GetValueAUTO, SetValueAUTO, VT_VARIANT)
	DISP_DEFVALUE(CFileStream,"value")
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

VARIANT CFileStream::GetValueAUTO()
{
	ALL_TRY
	{
		COleSafeArray oSafeArray;
		SCP<IStream> poStreamSP = GetStream();
		long nFileSize = GetStreamSize(poStreamSP);
		oSafeArray.CreateOneDim(VT_UI1,nFileSize);

		{
			CSafeArrayAccessHolder<BYTE> oSAAH(oSafeArray);
			BYTE * pDataPtr = oSAAH.GetData();
			CStreamHolder oSH(poStreamSP);
			const long nChunkSize = 1024 * 4;
			while(nChunkSize == oSH.Read(pDataPtr,nChunkSize))
			{
				pDataPtr += nChunkSize;
			}
		}
		return oSafeArray.Detach();
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

void CFileStream::SetValueAUTO(const VARIANT FAR& newValue)
{
	ALL_TRY
	{
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoAutoException(roNavoException);
	}
}

//-----------------------------------------------------------------------


void CFileRemover::TryToRemove()
{
	try
	{
		if (m_oFileName.GetLength())
		{
			NavoDeleteFile(m_oFileName);
		};
	}
	catch(...)
	{
		//TO_DO: ³apaæ tylko co potrzeba. inne rzucaæ
		// najprawdopodnobniej SetStatus threw. Có¿... probowalismy
	};
};


long CBufferToFile::Seek(long lSeek, EOffsetBase eBase)
{
	LARGE_INTEGER liPosition;
	ULARGE_INTEGER liNewPosition;
	liPosition.QuadPart = LONGLONG(lSeek);
	HRESULT hResult;
	if (eBase == CURRENT)
	{
		hResult = GetStream()->Seek(liPosition, STREAM_SEEK_CUR, &liNewPosition); 
	}
	else
	{
		hResult = GetStream()->Seek(liPosition, STREAM_SEEK_SET, &liNewPosition); 
	};
	if (hResult != S_OK)
	{
		ThrowNavoException1(ERCO_ISTREAM_SEEK_FaILED, IDPAGE_NOTAVAILABLE,
			SCODE_To_String(hResult));
	};
	ASSERT(!liNewPosition.HighPart);
	return (long)liNewPosition.QuadPart;
};

void CBufferToFile::MoveBack ()
{
	if (m_lPosition)
	{
		m_lPosition--;
	}
	else
	{
		long lPosition = Seek(0);
		if (lPosition <= m_lBufferSize)
		{
			return;
		};
		Seek(-(m_lBufferSize + m_lBufferLength));
		m_bEndOfFile = false;
		ReadBlock();
		m_lPosition = m_lBufferLength - 1;
	};
};

long CBufferToFile::ReadLine(CArray <TCHAR, TCHAR &> & raSource, bool bWithCR)
{
	TCHAR cCharacter;
	ASSERT(raSource.GetSize() > 0); // powinienes nadac (sensowny) rozmar poczatkowy
	raSource[0] = '\0';
	CArrayWriter <TCHAR> oArrayWriter(raSource);
	do
	{
		if (IsEndOfFile())
		{
			if (oArrayWriter.CharactersWritten())
			{
				break;
			}
			else
			{
				return -1;
			};
		};
		cCharacter = GetChar();
		if (cCharacter == '\n')
		{
			break;
		};
		if (cCharacter == '\r')
		{
			if (!IsEndOfFile() && GetChar() != '\n')
			{
				MoveBack();
			};
			break;
		};
		oArrayWriter << cCharacter;
	}
	while (true);
	if (bWithCR)
	{
		oArrayWriter << '\r' << '\n';
	}
	oArrayWriter << '\0';
	return oArrayWriter.CharactersWritten() - 1; // bez tego ostatniego zera
};

//luzne funkcje
const TCHAR * _g_pchNAVO2001Update			= _T("Update");

const TCHAR * GetUpdateSubDir()
{
	return _g_pchNAVO2001Update;
}

void CleanNavoTemporaryFiles()
{
	CString oString;
	LONG lResult =  SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),_T("InstallationRoot"),oString);
	ASSERT(lResult == ERROR_SUCCESS);
	if(!oString.IsEmpty())
	{

		EnsureEndingBackslash(oString);
		CString oTempString = oString + _g_pchNAVO2001Temporary;
		EnsureEndingBackslash(oTempString);

		//ignoruj problemy z usuwaniem - jak siê nie da to nie da
		ALL_TRY
		{
			NavoRemoveDirectoryTree(oTempString);
		}
		ALL_CATCH(...)
		{
		};

		NavoCreateDirectoryTree(oTempString);
		CString oUpdateString = oString + GetUpdateSubDir();
		EnsureEndingBackslash(oUpdateString);

		//ignoruj problemy z usuwaniem - jak siê nie da to nie da
		ALL_TRY
		{
			NavoRemoveDirectoryTree(oUpdateString);
		}
		ALL_CATCH(...)
		{
		};
	}
}

long GetStreamSize(IStream * pStream)
{
	return (long) get_stream_size64(pStream);
}

__int64 get_stream_size64(IStream * pStream)
{
	ASSERT(pStream);
	STATSTG statstg;
	HRESULT hr = pStream->Stat(&statstg,STATFLAG_NONAME);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_UNABLE_TO_GET_STREAM_SIZE, IDPAGE_NOTAVAILABLE,hr);
	}
	return statstg.cbSize.QuadPart;
}

void SaveStreamToFile(SCP <IStream> & iStreamSCP, LPCTSTR pcFileName, bool bEncode,ULONGLONG unLength /*= MAXLONGLONG*/)
{
	ULARGE_INTEGER ulInfinity;
	ulInfinity.QuadPart = unLength;
	HRESULT hr = iStreamSCP->CopyTo(CreateFileStream_Write(pcFileName,bEncode),ulInfinity,NULL,NULL);
	if(hr != S_OK)
	{
		ThrowNavoException1(ERCO_SAVESTREAMTOFILE_FAILED,IDPAGE_NOTAVAILABLE,hr);
	}
}

HRESULT SaveStreamToFile(SCP <IStream> & iStreamSCP, CFile * pDestinationFile,
						 INotificationSink * poNotificationSink,long nLength)
{
	ASSERT(iStreamSCP.PointsObject());
	ASSERT(pDestinationFile);
	CString oInformationString;

	const long nCopyPartSize = 0x00001000; //4KB

	long nStreamSize = min(GetStreamSize(iStreamSCP),nLength);
	//write stream data, in part to allow abort
	for(long nSizeCopied = 0; nSizeCopied < nStreamSize; nSizeCopied += nCopyPartSize)
	{
		char cBuffer[ nCopyPartSize ];
		long nChunkSize = min(nCopyPartSize,nStreamSize-nSizeCopied);

		HRESULT hr = iStreamSCP->Read((LPVOID)cBuffer,nChunkSize,NULL);
		if(hr != S_OK)
		{
			return hr;
		}
		pDestinationFile->Write(cBuffer,nChunkSize);
		if(nStreamSize > nCopyPartSize)	//wyœwieltaj tylko dla du¿ych
		{
			if(poNotificationSink)
			{
				oInformationString.Format(_T("Kopiowanie pliku %s"),pDestinationFile->GetFileName());
				if(StdNotifyOnProgress(NewSCP(poNotificationSink,true),NOTF_COPYING_FILE,
					nSizeCopied,nStreamSize,oInformationString) != S_OK)
				{
					return ERROR_CANCELLED;
				}
			}
		}
	}
	return S_OK;
}

HRESULT ReadStreamFromFile(CFile * pSourceFile,SCP <IStream> & iStreamSCP, 
						   INotificationSink * poNotificationSink,long nLength)
{
	ASSERT(iStreamSCP.PointsObject());
	ASSERT(pSourceFile);
	CString oInformationString;

	const long nCopyPartSize = 0x00001000; //4KB

	long nStreamSize = min((long)pSourceFile->GetLength(),nLength);
	/*	
	ULARGE_INTEGER uliNewSize;
	uliNewSize.QuadPart = nStreamSize;
	HRESULT hr = iStreamSCP->SetSize(uliNewSize);
	if(hr != S_OK)
	{
	return hr;
	}
	*/
	//write stream data, in part to allow abort
	for(long nSizeCopied = 0; nSizeCopied < nStreamSize; nSizeCopied += nCopyPartSize)
	{
		char cBuffer[ nCopyPartSize ];
		long nChunkSize = min(nCopyPartSize,nStreamSize-nSizeCopied);

		pSourceFile->Read(cBuffer,nChunkSize);
		HRESULT hr = iStreamSCP->Write((LPVOID)cBuffer,nChunkSize,NULL);
		if(hr != S_OK)
		{
			return hr;
		}
		if(nStreamSize > nCopyPartSize)	//wyœwieltaj tylko dla du¿ych
		{
			if(poNotificationSink)
			{
				oInformationString.Format(_T("Kopiowanie pliku %s"),pSourceFile->GetFileName());
				if(StdNotifyOnProgress(NewSCP(poNotificationSink,true),NOTF_COPYING_FILE,
					nSizeCopied,nStreamSize,oInformationString) != S_OK)
				{
					return ERROR_CANCELLED;
				}
			}
		}
	}
	return S_OK;
}

HRESULT IStream_CopyTo(IStream * pSrcIStream,IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
					   ULARGE_INTEGER * pulBytesRead /* = NULL*/, ULARGE_INTEGER * pulBytesWritten /* = NULL*/)
{
	ASSERT(pSrcIStream);

	char cArray[32768];
	ULONGLONG lBytesToCopy = ulToCopy.QuadPart;
	ULONGLONG lTotalBytesRead = 0;
	ULONGLONG lTotalBytesWritten = 0;
	while(lBytesToCopy > 0)
	{
		DWORD lBytesRead = 0;
		DWORD lBytesWritten = 0;
		HRESULT hr = pSrcIStream->Read(cArray,min(lohyper(lBytesToCopy),sizeof(cArray)),&lBytesRead);
		if(hr != S_OK)
		{
			return hr;
		}
		if(lBytesRead == 0)		//strumieñ krótszy ni¿ ¿¹dano bajtów do skopiowania
		{
			break;
		}
		if(pDestIStream)
		{
			hr = pDestIStream->Write(cArray,lBytesRead,&lBytesWritten);
		}
		else	//"null" write case
		{
			hr = S_OK;
		}
		if(hr != S_OK)
		{
			return hr;
		}
		lTotalBytesRead += lBytesRead;
		lTotalBytesWritten += lBytesWritten;
		lBytesToCopy -= lBytesRead;
	}
	if(pulBytesRead)
	{
		pulBytesRead->QuadPart = lTotalBytesRead;
	}
	if(pulBytesWritten)
	{
		pulBytesWritten->QuadPart = lTotalBytesWritten;
	}
	return S_OK;
}

SCP <IStream> CompressStream(SCP <IStream> & rpoInputStreamSP)
{
	SCP<IStreamFilter> pStreamFilterSP;
	pStreamFilterSP.CreateInstance(CLSID_NAVO2001StreamFilter,CLSCTX_ALL);
	pStreamFilterSP->AttachInput(rpoInputStreamSP.Get());
	pStreamFilterSP->SetParam(SFT_COMPRESS);
	SCP<IStream> pFilteredStreamSP;
	pFilteredStreamSP.QueryInterface(pStreamFilterSP);
	return pFilteredStreamSP;
}

SCP <IStream> UncompressStream(SCP <IStream> & rpoInputStreamSP)
{
	SCP<IStreamFilter> pStreamFilterSP;
	pStreamFilterSP.CreateInstance(CLSID_NAVO2001StreamFilter,CLSCTX_ALL);
	pStreamFilterSP->AttachInput(rpoInputStreamSP.Get());
	pStreamFilterSP->SetParam(SFT_UNCOMPRESS);
	SCP<IStream> pFilteredStreamSP;
	pFilteredStreamSP.QueryInterface(pStreamFilterSP);
	return pFilteredStreamSP;
}

//returns pointer to base64 encoded stream (pull mode read). Entry stream : any binary
SCP <IStream> Base64EncodeStream(SCP <IStream> & rpoInputStreamSP)
{
	SCP<IStreamFilter> pStreamFilterSP;
	pStreamFilterSP.CreateInstance(CLSID_NAVO2001StreamFilter,CLSCTX_ALL);
	pStreamFilterSP->AttachInput(rpoInputStreamSP.Get());
	pStreamFilterSP->SetParam(SFT_BASE64ENCODE);
	SCP<IStream> pFilteredStreamSP;
	pFilteredStreamSP.QueryInterface(pStreamFilterSP);
	return pFilteredStreamSP;
}

//returns pointer to base64 decoded stream (pull mode read). Entry stream: base 64 encoded
SCP <IStream> Base64DecodeStream(SCP <IStream> & rpoInputStreamSP)
{
	SCP<IStreamFilter> pStreamFilterSP;
	pStreamFilterSP.CreateInstance(CLSID_NAVO2001StreamFilter,CLSCTX_ALL);
	pStreamFilterSP->AttachInput(rpoInputStreamSP.Get());
	pStreamFilterSP->SetParam(SFT_BASE64DECODE);
	SCP<IStream> pFilteredStreamSP;
	pFilteredStreamSP.QueryInterface(pStreamFilterSP);
	return pFilteredStreamSP;
}

HRESULT download_url_2_file(LPCTSTR lpURL,LPCTSTR lpFile,bool bUI);

SCP <IStream> OpenURLStream(const TCHAR * pszURL)
{
	LPCSTR pcExtension = _tcsrchr(pszURL,'.');
	if(pcExtension != NULL)
	{
		pcExtension++;
	}
	else
	{
		pcExtension = "";
	}

	CString oString = GenerateUniqueFileName("URL", pcExtension);

	SCP <IStream> iStreamSCP;
	HRESULT hResult = download_url_2_file(pszURL,oString,true);
	if (hResult != S_OK)
	{
		ThrowNavoException2(ERCO_UNABLE_TO_OPEN_STREAM, IDPAGE_NOTAVAILABLE, pszURL,
			SCODE_To_String(hResult));
	};
	return OpenFileStream_Read(oString,false);
};

#endif //_MINI_CORE_

static volatile long __lUniqueFileNameNumber = 1000;

CString GenerateUniqueFileName(LPCTSTR pcPrefix, LPCTSTR pcExtension)
{
	ASSERT(pcExtension);			//provide extension
	ASSERT(pcExtension[0] != '.');	//but without leading dot

	static CSimpleCriticalSection m_oSCS;
	
	::Sleep(16);

	long lCurrentNumber;
	{
		//CSimpleLock oLock(m_oSCS);
		//lCurrentNumber = __lUniqueFileNameNumber++;
		
		lCurrentNumber = (long) ::GetTickCount();
	};

	CString oString;
	LONG lResult =  SafeGetRegistryKeyString(HKEY_LOCAL_MACHINE, GetSetupRegistryKeyName(),_T("InstallationRoot"),oString);
	ASSERT(lResult == ERROR_SUCCESS);

	if(oString.IsEmpty())
	{
		TCHAR cTmpFilePath[_MAX_PATH];
		if (!::GetTempPath(sizeof(cTmpFilePath), cTmpFilePath))
		{
			DWORD dwLastError = ::GetLastError();
			ThrowNavoException1(ERCO_GETTEMPPATH_FAILED,IDPAGE_NOTAVAILABLE,GetLastError_To_String(dwLastError));
		};
		oString = CString(cTmpFilePath);
	}
	else
	{
		EnsureEndingBackslash(oString);
		oString += _g_pchNAVO2001Temporary;
	}

	EnsureEndingBackslash(oString);

	oString += pcPrefix + Long2String((long)::GetCurrentProcessId()) + "_" +
		Long2String(lCurrentNumber) + "." + CString(pcExtension);

	return oString;
}

bool NavoDeleteFile(LPCTSTR lpFileName)
{
	if (!::DeleteFile(lpFileName))
	{
		DWORD dwErrorCode = ::GetLastError();
		if(dwErrorCode == ERROR_FILE_NOT_FOUND)
		{
			return true;	//nie ma - o to nam w³aœnie chodzi³o
		}
		if (dwErrorCode == ERROR_ACCESS_DENIED)
		{
			::SetFileAttributes(lpFileName, FILE_ATTRIBUTE_NORMAL);
		};
		if(!::DeleteFile(lpFileName))
		{
			DWORD dwErrorCode = ::GetLastError();
			ASSERT(dwErrorCode != ERROR_SUCCESS);
			return false;
		}
	}
	return true;
}

long GetDirectoryDiskUsage(CString oDirectoryString)
{
	long lUsage = 0;
	CFileFind oFileFind;
	if (oDirectoryString.GetAt(oDirectoryString.GetLength() - 1) == '\\')
	{
		oDirectoryString.Delete(oDirectoryString.GetLength() - 1);
	};
	if (oFileFind.FindFile(oDirectoryString + "\\*.*"))
	{
		enum
		{
			OK,
			LAST,
		} eState = OK;
		while (eState != LAST)
		{
			if (!oFileFind.FindNextFile())
			{
				eState = LAST;
			};
			CString oFilePathString = oDirectoryString + '\\' + oFileFind.GetFileName();
			if (oFileFind.IsDirectory())
			{
				if (!oFileFind.IsDots())
				{
					lUsage += GetDirectoryDiskUsage(oFilePathString);
				}
			}
			else
			{
				lUsage += (long) oFileFind.GetLength();
			};
		};
	};
	oFileFind.Close();
	return lUsage;
};

void NavoCreateDirectory(const TCHAR *pcDirName)
{
	if (!::CreateDirectory(pcDirName, NULL))
	{
		DWORD dwResult = GetLastError();

		if (dwResult == ERROR_ALREADY_EXISTS)
		{
			return;
		};
		ThrowNavoException2(ERCO_UNABLE_TO_CREATE_DIRECTORY, IDPAGE_NOTAVAILABLE, pcDirName,GetLastError_To_String(dwResult));
	};
};

void NavoCreateDirectoryTree(CString oPathNameString)
{
	EnsureEndingBackslash(oPathNameString);
	long lIndex;
	CString oTmpDirString;
	do
	{
		lIndex = oPathNameString.Find('\\');
		if (lIndex != -1)
		{
			oTmpDirString += CString(oPathNameString, lIndex);
			oPathNameString = (LPCTSTR)oPathNameString + lIndex + 1;
			if (!oTmpDirString.IsEmpty() && oTmpDirString.GetAt(oTmpDirString.GetLength() - 1) != ':')
			{
				NavoCreateDirectory(oTmpDirString);
			};
			oTmpDirString += '\\';
		};
	}
	while (lIndex != -1);
};

bool NavoRemoveDirectoryTree(CString oDirectoryString, bool bThrowIfFailed, bool bOnlyDirectoryTree)
{
	CFileFind oFileFind;
	bool bResult = true;
	if (oDirectoryString.GetAt(oDirectoryString.GetLength() - 1) == '\\')
	{
		oDirectoryString.Delete(oDirectoryString.GetLength() - 1);
	};
	if (oFileFind.FindFile(oDirectoryString + "\\*.*"))
	{
		enum
		{
			OK,
			LAST,
		} eState = OK;
		while (eState != LAST)
		{
			if (!oFileFind.FindNextFile())
			{
				eState = LAST;
			};
			CString oFilePathString = oDirectoryString + '\\' + oFileFind.GetFileName();
			if (oFileFind.IsDirectory())
			{
				if (!oFileFind.IsDots())
				{
					NavoRemoveDirectoryTree(oFilePathString, bThrowIfFailed, bOnlyDirectoryTree);
				}
			}
			else
			{
				if (!bOnlyDirectoryTree)
				{
					NavoDeleteFile(oFilePathString);
				};
			};
		};
	};
	oFileFind.Close();
	bResult = ::RemoveDirectory(oDirectoryString) != FALSE;
	DWORD dwErrorCode = ::GetLastError();
	if (dwErrorCode == ERROR_FILE_NOT_FOUND)
	{
		return true;
	};
	if (dwErrorCode == ERROR_ACCESS_DENIED)
	{
		::SetFileAttributes(oDirectoryString, FILE_ATTRIBUTE_NORMAL);
	};
	if (!bResult && !::RemoveDirectory(oDirectoryString))
	{
	}
	else
	{
		bResult = true;
	};
	if (!bResult && bThrowIfFailed)
	{
		ThrowNavoException2(ERCO_UNABLE_TO_DELETE_DIRECTORY, IDPAGE_NOTAVAILABLE, 
			oDirectoryString,GetLastError_To_String(dwErrorCode));
	};
	return bResult;
};

CString NavoGetFullPathName(LPCTSTR pcFileName)
{
	LPTSTR pcDummy;
	CString oFileNameString;
	if (!::GetFullPathName(pcFileName, _MAX_PATH, oFileNameString.GetBuffer(_MAX_PATH), &pcDummy))
	{
		ThrowNavoException2(ERCO_GETFULLPATHNAME_FAILURE,IDPAGE_NOTAVAILABLE,pcFileName,GetLastError_To_String(::GetLastError()));
	};
	oFileNameString.ReleaseBuffer();
	oFileNameString.MakeLower();
	return oFileNameString;
};

bool CheckEnvVariablePath(LPCTSTR pcVarName)
{
	TCHAR acValue[1024];
	DWORD dwResult;
	if (pcVarName)
	{
		if ((dwResult = ::GetEnvironmentVariable(pcVarName, acValue, sizeof(acValue))) == 0)
		{
			return false;
		};
	}
	else
	{
		if ((dwResult = ::GetTempPath(sizeof(acValue), acValue)) == 0)
		{
			return false;
		};
	};
	long lVarLength = _tcslen(acValue);
	if (!lVarLength)
	{
		return false;
	};
	if (acValue[lVarLength - 1] != '\\' && acValue[lVarLength - 1] != '/')
	{
		acValue[lVarLength++] = '\\';
		acValue[lVarLength] = '\0';
	};
	LPCTSTR pcTestFileName = _T("$_123321.tmp");
	TCHAR acFilePath[1024 + 100];
	_tcscpy(acFilePath, acValue);
	_tcscat(acFilePath, pcTestFileName);
	HANDLE hFile;
	if ((hFile = ::CreateFile(acFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == (HANDLE)INVALID_HANDLE_VALUE)
	{
		// sprobuj naprawic
		if (!::CreateDirectory(acValue, NULL))
		{
			return false;
		};
		if ((hFile = ::CreateFile(acFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == (HANDLE)INVALID_HANDLE_VALUE)
		{
			return false;
		};
	};
	if (!::CloseHandle(hFile))
	{
		return false;
	};
	if (!::DeleteFile(acFilePath))
	{
		return false;
	};
	return true;
};


/*
void NavoCreateFile(CFile & roFile,LPCTSTR pcFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes)
{
BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);	//from MFC

ASSERT(AfxIsValidString(pcFileName));
ASSERT(roFile.m_hFile == (UINT)INVALID_HANDLE_VALUE); // nie zamkniety?
roFile.m_hFile = (UINT)CFile::hFileNull;
roFile.SetFilePath("");
TCHAR acFullNameTemp[_MAX_PATH];
AfxFullPath(acFullNameTemp, pcFileName);
roFile.SetFilePath(acFullNameTemp);
SECURITY_ATTRIBUTES sa;
sa.nLength = sizeof(sa);
sa.lpSecurityDescriptor = NULL;
sa.bInheritHandle = TRUE;
HANDLE hFile = ::CreateFile(pcFileName, dwDesiredAccess, dwShareMode, &sa, dwCreationDisposition, dwFlagsAndAttributes, NULL);
if (hFile == INVALID_HANDLE_VALUE)
{
DWORD dwErrorCode = ::GetLastError();
ThrowNavoException2(ERCO_UNABLE_TO_OPEN_FILE, 0, (LPCTSTR)roFile.GetFilePath(), 
GetLastError_To_String(dwErrorCode));
};
roFile.m_hFile = (HFILE)hFile;

//m_bCloseOnDelete = TRUE; - caller has to close
}
*/

