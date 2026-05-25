/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Low level file logging
*/

#ifndef _NAVOLOG_H_
#define _NAVOLOG_H_

class CNavoLog
{
public:
	CNavoLog(bool bRawMode = false):
		m_hFile(INVALID_HANDLE_VALUE),
		m_bRawMode(bRawMode)
	{
	}
	void Open(LPCTSTR lpLogFileName)
	{
		if(IsHandleValid())
		{
			Close();
		}

		m_hFile = ::CreateFile(lpLogFileName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,
			OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,NULL);
		
		if(IsHandleValid())
		{
			if(m_bRawMode)
			{
				::SetFilePointer(m_hFile, 0, NULL, FILE_BEGIN);
			}
			else
			{
				::SetFilePointer(m_hFile, 0, NULL, FILE_END);
				*this << _T("===log opened===\r\n");
			}
		}
	}
	virtual CNavoLog & operator << (LPCTSTR lpLine)
	{
		if(!m_bRawMode)
		{
			TCHAR cDate[ 32 ];
			TCHAR cTime[ 32 ];
			_tstrdate(cDate);
			_tstrtime(cTime);
			WriteString(cDate);
			WriteString(_T(" "));
			WriteString(cTime);
			WriteString(_T("\t"));
		}
		WriteString(lpLine);
		if(!m_bRawMode)
		{
			WriteString(_T("\r\n"));
		}
		return *this;
	}

	bool IsHandleValid() const
	{
		return (m_hFile != INVALID_HANDLE_VALUE);
	}

	void Close()
	{
		if(IsHandleValid())
		{
			if(!m_bRawMode)
			{
				*this << _T("===log closed===\r\n");
			}
			::CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
		}
	}
	~CNavoLog()
	{
		Close();
	}
private:
	void WriteString(LPCTSTR lpString)
	{
		ASSERT(IsHandleValid());
		if(IsHandleValid())
		{
			DWORD dwBytesWritten;
			::WriteFile(m_hFile,lpString,_tcslen(lpString),&dwBytesWritten,NULL);
		}
	}
	HANDLE m_hFile;
	bool   m_bRawMode;
};

#else
	#error __FILE__ already included
#endif
