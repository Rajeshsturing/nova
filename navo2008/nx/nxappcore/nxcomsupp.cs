using System;
using System.IO;
using System.Runtime.InteropServices;
using nxappcore;
using navo2012.proxy;

namespace nxappcore
{
    /// <summary>
    /// COM support for interop with NX
    /// </summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxappcore_nxcomsupport)]
    public class nxcomsupp
    {
        static nxcomsupp()
        {
        }

        /// <summary>
        /// creates file-based stream
        /// </summary>
        /// <param name="oFileNameString">file name</param>
        /// <returns>opened stream</returns>
        public static Stream create_file_stream(string oFileNameString)
        {
            return new FileStream(oFileNameString, FileMode.Create);
        }

        /// <summary>
        /// opens existing, file-based stream
        /// </summary>
        /// <param name="oFileNameString">file name</param>
        /// <returns>opened stream</returns>
        public static Stream open_file_stream(string oFileNameString)
        {
            return new FileStream(oFileNameString, FileMode.Open);
        }
    }

    /// <summary>
    /// obudowa na na IStream dostarczany z NE2002
    /// </summary>
    public class nxcomstream : Stream
    {
        public nxcomstream(object oStream)
        {
            m_IStream = (System.Runtime.InteropServices.ComTypes.IStream)oStream;
        }

        public System.Runtime.InteropServices.ComTypes.IStream IStream
        {
            get
            {
                return m_IStream;
            }
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            unsafe
            {
                int iBytesRead = 0;
                int* pBytesRead = &iBytesRead;
                m_IStream.Read(buffer, count, new IntPtr(pBytesRead));
                return iBytesRead;
            }
        }
        public override void Write(byte[] buffer, int offset, int count)
        {
            unsafe
            {
                int iBytesWritten = 0;
                int* pBytesWritten = &iBytesWritten;
                m_IStream.Write(buffer, count, new IntPtr(pBytesWritten));
            }
        }
        public override bool CanRead
        {
            get
            {
                return true;
            }
        }
        public override bool CanWrite
        {
            get
            {
                return true;
            }
        }
        public override bool CanSeek
        {
            get
            {
                return false;
            }
        }
        public override void Flush()
        {
        }
        public override long Length
        {
            get
            {
                throw new NotImplementedException();
            }
        }
        public override long Position
        {
            get
            {
                throw new NotImplementedException();
            }
            set
            {
                throw new NotImplementedException();
            }
        }
        public override long Seek(long offset, SeekOrigin origin)
        {
            IntPtr ptrNewPos = new IntPtr();
            m_IStream.Seek(offset, (int)origin, ptrNewPos);
            return ptrNewPos.ToInt64();
        }
        public override void SetLength(long value)
        {
            m_IStream.SetSize(value);
        }




        System.Runtime.InteropServices.ComTypes.IStream m_IStream;
    }

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
            throw new NotImplementedException();
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
    /// <summary>
    /// ró¿ne utilities
    /// </summary>
    public class nxstreamutil
    {
        static nxstreamutil()
        {
        }
        /// <summary>
        /// zamienia strumien tekstowy na tablice 
        /// wg zasady, kazda linia w jednym elemencie
        /// </summary>
        /// <param name="oInputStream"></param>
        /// <returns></returns>
        public static nxarray stream2linearray(Stream oInputStream)
        {
            nxarray oArray = new nxarray();
            StreamReader oStreamReader = new StreamReader(oInputStream);
            for (string oString = oStreamReader.ReadLine();
                oString != null; oString = oStreamReader.ReadLine())
            {
                oArray.add(oString);
            }
            return oArray;
        }
    }
}
