/*
 * 
 * NAVO Enterprise 2012 client side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */
using System;
using System.Runtime.InteropServices;
using navo2012.proxy;
using navo2012.net.enterprise.common;
using navo2012.net.host;
using System.IO;
using nxappcore;

namespace navo2012.net.enterprise.client
{
    [ComVisible(true)]
    public class AppDBManager : IAppDBManager, IStreamProvider
    {
        internal AppDBManager(ServerClient oServerClient, int iAppDBManager)
        {
            m_oServerClient = oServerClient;
            m_iAppDBManager = iAppDBManager;
        }

        public void ChangeMode(int nNewMode)
        {
            throw new NotImplementedException();
        }

        public void Close(sbyte bOK)
        {
            throw new NotImplementedException();
        }

        public void CreateApp(string lpAppName, string lpLocalRootDirectory, int lKey)
        {
            throw new NotImplementedException();
        }

        public void Delete(int IdFile)
        {
            throw new NotImplementedException();
        }

        public void DropApp(string lpAppName)
        {
            throw new NotImplementedException();
        }

        public void EnumFileGroup(string lpGroupName, out ISimpleEnumId ppSimpleEnumFileId)
        {
            throw new NotImplementedException();
        }

        public void GetFinalStream(int IdFile, string pcEnvironentStr, out IStream pStream, out navostreaminfo _NSI)
        {
            navo2012_stream_info oNSI;
            Stream oStream;
            m_oServerClient._remote_server(false).AppDBManager_GetFinalStream(m_oServerClient._iServerClient, m_iAppDBManager,
                IdFile, pcEnvironentStr, out oStream, out oNSI);

            _NSI.m_bCompressed = oNSI.m_bCompressed;
            _NSI.m_cExt = (sbyte[])oNSI.m_cExt.Clone();

            pStream = (oStream == null) ? null : new InteropCOMStream(oStream) as IStream;
        }

        public void GetItemInfo(int nInfoType, int IdFile, out DateTime pModifDate, out int pnVarCntr, IntPtr _ppVarNr)
        {
            throw new NotSupportedException();
        }

        public void Get(int IdFile, out IStream pStream, out navostreaminfo _NSI)
        {
            navo2012_stream_info oNSI;
            Stream oStream;

            m_oServerClient._remote_server(false).AppDBManager_StreamProvGet(m_oServerClient._iServerClient, m_iAppDBManager,
                IdFile, out oStream, out oNSI);

            _NSI.m_bCompressed = oNSI.m_bCompressed;
            _NSI.m_cExt = (sbyte[])oNSI.m_cExt.Clone();

            pStream = (oStream == null) ? null : new InteropCOMStream(oStream) as IStream;
        }

        public void GetItemInfo2(int nInfoType, int IdFile, out DateTime pModifDate, out int pnVarCntr, out int[] ppVarNr)
        {
            m_oServerClient._remote_server(false).AppDBManager_GetItemInfo(m_oServerClient._iServerClient, m_iAppDBManager,
                nInfoType, IdFile, out pModifDate, out pnVarCntr, out ppVarNr);
        }

        public void GetMode(out int pnMode)
        {
            throw new NotImplementedException();
        }

        public void Init(string lpAppName)
        {
            m_oServerClient._remote_server(false).AppDBManager_Init(m_oServerClient._iServerClient, m_iAppDBManager, lpAppName);
        }

        public void Pack(object varDestNameOrStream, object varDestNameOrStreamInfo)
        {
            throw new NotImplementedException();
        }

        public void SetOptions(int nOptions)
        {
            throw new NotImplementedException();
        }

        public void Unpack(object varSrcNameOrStream, object varSrcNameOrStreamInfo)
        {
            throw new NotImplementedException();
        }

        public void Upload(int IdFile, IStream pStream, string pcExtension)
        {
            throw new NotImplementedException();
        }

        private ServerClient m_oServerClient;
        private int m_iAppDBManager;

    }
}