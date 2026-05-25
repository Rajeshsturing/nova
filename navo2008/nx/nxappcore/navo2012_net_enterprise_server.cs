/*
 * 
 * NAVO Enterprise 2012 service .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System;
using System.IO;
using navo2012.proxy;
using nxappcore;

namespace navo2012.net.host
{
    [Serializable]
    public struct navo2012_stream_info
    {
        public sbyte m_bCompressed;
        public sbyte[] m_cExt;
    }

    [Serializable]
    public struct navo2012_blob_info
    {
        public int m_IdMapping;
        public int m_IdParent;
        public navo2012_stream_info m_oNSI;
        public Stream m_oStream;

        public void marshal(tag_transblobinfo oTBI)
        {
            oTBI.m_IdMapping = m_IdMapping;
            oTBI.m_IdParent = m_IdParent;
            oTBI.m_oNSI.m_bCompressed = m_oNSI.m_bCompressed;
            oTBI.m_oNSI.m_cExt = (sbyte[])m_oNSI.m_cExt.Clone();

            oTBI.m_pIStream = (m_oStream == null) ? null : new InteropCOMStream(m_oStream) as IStream;
        }
    }
    [Serializable]
    public struct navo2012_lockid
    {
        public int m_class;
        public int m_extra;
        public int m_idobj;
        public int m_typeid;
    }
    [Serializable]
    public struct navo2012_lock
    {
        public navo2012_lockid m_fullid;
        public tag_navolocktype m_type;
    }

    public interface INAVO2012ObjectCollection
    {
        void Fetch2(tag_fetchdir FetchDirection, ref int nCount, out int pDataLength, out byte[] lpBinaryData, int nAbsolutePosition);
        void GetCount(out int pnCount);
        void Refresh(int nPositionToKeep, out int pnCount);
    }

}