/*
 * NAVO ECWS 3 Project 
 * Copyright 2013-2016
 */


using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace navo.cocoon.data.utils
{
    /// <summary>wraps .NET Stream into Interop IStream</summary>
    public class InteropCOMStream : IStream
    {
        #region constructor
        /// <summary>universal constructor</summary>
        public InteropCOMStream(Stream oStream)
        {
            m_oStream = oStream;
        }
        #endregion
        #region IStream interface
        public void Clone(out IStream ppstm)
        {
            throw new NotImplementedException();
        }

        public void Commit(int grfCommitFlags)
        {
            m_oStream.Flush();
        }

        public void LockRegion(long libOffset, long cb, int dwLockType)
        {
            throw new NotImplementedException();
        }

        public void CopyTo(IStream pstm, long cb, IntPtr pcbRead, IntPtr pcbWritten)
        {
            throw new NotImplementedException();
        }

        public void Read(byte[] pv, int cb, IntPtr pcbRead)
        {
            int iRead = m_oStream.Read(pv, 0, cb);
            if (pcbRead != IntPtr.Zero)
            {
                Marshal.WriteInt32(pcbRead, iRead);
            }
        }

        public void Seek(long dlibMove, int dwOrigin, IntPtr plibNewPosition)
        {
            long iPosition = m_oStream.Seek(dlibMove, (SeekOrigin)dwOrigin);
            if (plibNewPosition != IntPtr.Zero)
            {
                Marshal.WriteInt64(plibNewPosition, iPosition);
            }
        }

        public void Write(byte[] pv, int cb, IntPtr pcbWritten)
        {
            m_oStream.Write(pv, 0, cb);
            if (pcbWritten != IntPtr.Zero)
            {
                Marshal.WriteInt32(pcbWritten, cb);
            }
        }

        public void Revert()
        {
            throw new NotImplementedException();
        }

        public void SetSize(long libNewSize)
        {
            m_oStream.SetLength(libNewSize);
        }

        public void Stat(out STATSTG pstatstg, int grfStatFlag)
        {
            pstatstg = new STATSTG();
        }

        public void UnlockRegion(long libOffset, long cb, int dwLockType)
        {
            throw new NotImplementedException();
        }
        #endregion
        #region data members
        /// <summary>wrapped stream</summary>
        private Stream m_oStream;
        #endregion
    }
}
