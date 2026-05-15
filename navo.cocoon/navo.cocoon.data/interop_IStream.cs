/*
 * NAVO ECWS 3 Project 
 * Copyright 2013-2016
 */


using navo2012.proxy;
using System;
using System.IO;
using System.Runtime.InteropServices;

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

        public void Commit(uint grfCommitFlags)
        {
            throw new NotImplementedException();
        }

        public void LockRegion(_ULARGE_INTEGER libOffset, _ULARGE_INTEGER cb, uint dwLockType)
        {
            throw new NotImplementedException();
        }

        public void RemoteCopyTo(IStream pstm, _ULARGE_INTEGER cb, out _ULARGE_INTEGER pcbRead, out _ULARGE_INTEGER pcbWritten)
        {
            throw new NotImplementedException();
        }

        public void RemoteRead(out byte pv, uint cb, out uint pcbRead)
        {
            unsafe
            {
                fixed (byte* pBuffer = &pv)
                {
                    byte[] arrBuffer = new byte[cb];
                    pcbRead = (uint)m_oStream.Read(arrBuffer, 0, (int)cb);
                    Marshal.Copy(arrBuffer, 0, new IntPtr(pBuffer), (int)pcbRead);
                }
            }
        }

        public void RemoteSeek(_LARGE_INTEGER dlibMove, uint dwOrigin, out _ULARGE_INTEGER plibNewPosition)
        {
            plibNewPosition.QuadPart = (ulong)m_oStream.Seek(dlibMove.QuadPart, (SeekOrigin)dwOrigin);
        }

        public void RemoteWrite(ref byte pv, uint cb, out uint pcbWritten)
        {
            unsafe
            {
                fixed (byte* pBuffer = &pv)
                {
                    byte[] arrBuffer = new byte[cb];
                    Marshal.Copy(new IntPtr(pBuffer), arrBuffer, 0, (int)cb);
                    m_oStream.Write(arrBuffer, 0, (int)cb);
                    pcbWritten = cb;
                }
            }
        }

        public void Revert()
        {
            throw new NotImplementedException();
        }

        public void SetSize(_ULARGE_INTEGER libNewSize)
        {
            m_oStream.SetLength((long)libNewSize.QuadPart);
        }

        public void Stat(out tagSTATSTG pstatstg, uint grfStatFlag)
        {
            pstatstg = new tagSTATSTG();
        }

        public void UnlockRegion(_ULARGE_INTEGER libOffset, _ULARGE_INTEGER cb, uint dwLockType)
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