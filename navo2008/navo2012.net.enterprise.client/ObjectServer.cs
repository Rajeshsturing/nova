/*
 * 
 * NAVO Enterprise 2012 client side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */
using System;
using System.IO;
using System.Runtime.InteropServices;
using navo2012.net.host;
using navo2012.proxy;
using nxappcore;

namespace navo2012.net.enterprise.client
{
    [ComVisible(true)]
    public class ObjectServer : IObjectServer
    {
        internal ObjectServer(ServerClient oServerClient, int iObjectServer)
        {
            m_oServerClient = oServerClient;
            m_iObjectServer = iObjectServer;
        }
        public void CanDelete(int nTypeId, int IdObj, out object pADORecordset)
        {
            throw new NotImplementedException();
        }

        public void Close(sbyte bOK)
        {
            throw new NotImplementedException();
        }

        public void CreateExtension(string lpExtensionProgId, out object pExtensionDisp)
        {
            throw new NotImplementedException();
        }

        public void ExecSQL(string lpSQLCommand, out int pRecordsAffected)
        {
            m_oServerClient._remote_server(false).ObjectServer_ExecSQL(
                m_oServerClient._iServerClient, m_iObjectServer, lpSQLCommand, out pRecordsAffected);
        }

        public void FindOnField(int nTypeId, string lpWhereClause, out int pFoundId)
        {
            pFoundId = m_oServerClient._remote_server(false).ObjectServer_FindOnField(
                m_oServerClient._iServerClient, m_iObjectServer, nTypeId, lpWhereClause);
        }

        public void FinishTransaction(sbyte bSuccess)
        {
            throw new NotImplementedException();
        }

        public void GetObjectIfNewer(int TypeId, int IdObj, int VersionNoReturn, sbyte bWriteLock, out int pDataLength, IntPtr lpBinaryData)
        {
            throw new NotImplementedException();
        }

        public void GetObjectIfNewer2(int TypeId, int IdObj, int VersionNoReturn, sbyte bWriteLock, out int pDataLength, out byte[] lpBinaryData)
        {
            m_oServerClient._remote_server(false).ObjectServer_GetObjectIfNewer2(m_oServerClient._iServerClient, m_iObjectServer,
                TypeId, IdObj, VersionNoReturn, bWriteLock, out pDataLength, out lpBinaryData);
        }

        public void GetProp(tag_objsrv_prop nProp, out object pvValue)
        {
            throw new NotImplementedException();
        }

        public void GetSharedVariable(int lVarNr, out object pvValue)
        {
            m_oServerClient._remote_server(false).ObjectServer_GetSharedVariable(m_oServerClient._iServerClient, m_iObjectServer,
                lVarNr, out pvValue);
        }

        public void GetStream(int IdParent, int IdMapping, out IStream pStream, out navostreaminfo _NSI, out int pVersion, out int pStreamId)
        {
            navo2012_stream_info oNSI;
            Stream oStream;

            m_oServerClient._remote_server(false).ObjectServer_GetStream(m_oServerClient._iServerClient, m_iObjectServer,
                IdParent, IdMapping, out oStream, out oNSI, out pVersion, out pStreamId);

            _NSI.m_bCompressed = oNSI.m_bCompressed;
            _NSI.m_cExt = (sbyte[])oNSI.m_cExt.Clone();

            pStream = (oStream == null) ? null : new InteropCOMStream(oStream) as IStream;
        }

        public void GetUniqueIdent(int TypeId, out int pNewId)
        {
            m_oServerClient._remote_server(false).ObjectServer_GetUniqueIdent(m_oServerClient._iServerClient, m_iObjectServer,
                TypeId, out pNewId);
        }

        public void MakeTransaction2(ref byte[] pBinaryData, ref tag_transblobinfo[] pBlobInfo, ref tag_navolock[] pLockInfo, sbyte bCommit)
        {
            navo2012_blob_info[] arrBlobInfo = (pBlobInfo == null) ? null : new navo2012_blob_info[pBlobInfo.Length];
            navo2012_lock[] arrLockInfo = (pLockInfo == null) ? null : new navo2012_lock[pLockInfo.Length];

            //copy

            m_oServerClient._remote_server(false).ObjectServer_MakeTransaction(m_oServerClient._iServerClient, m_iObjectServer,
                pBinaryData, arrBlobInfo, arrLockInfo, bCommit);
        }

        public void MakeTransaction(int nDataLength, ref byte lpBinaryData, int nBlobInfoCount,
            ref tag_transblobinfo pBlobInfo, int nWriteLockCount, ref tag_navolock pNavoLock, sbyte bCommit)
        {
            throw new NotImplementedException();
        }

        public void OpenCollection(int CollectionId, int IdParent, out int pTotalCount, out INAVOObjectCollection pCollection)
        {
            INAVO2012ObjectCollection _Collection;
            m_oServerClient._remote_server(false).ObjectServer_OpenCollection(m_oServerClient._iServerClient, m_iObjectServer,
                CollectionId, IdParent, out pTotalCount, out _Collection);

            pCollection = new ClientNAVOObjectCollection(_Collection) as INAVOObjectCollection;
        }

        public void OpenDiscoRecSet(string lpSQLClause, out IStream pADORecordset, out navostreaminfo _NSI)
        {
            navo2012_stream_info oNSI;
            Stream oStream;

            m_oServerClient._remote_server(false).ObjectServer_OpenDiscoRecSet(m_oServerClient._iServerClient, m_iObjectServer,
                lpSQLClause, out oStream, out oNSI);

            _NSI.m_bCompressed = oNSI.m_bCompressed;
            _NSI.m_cExt = (sbyte[])oNSI.m_cExt.Clone();

            pADORecordset = (oStream == null) ? null : new InteropCOMStream(oStream) as IStream;
        }

        public void OpenFTSQuery(int IdMapping, string lpQuery, out INAVOObjectCollection pCollection)
        {
            throw new NotImplementedException();
        }

        public void OpenOnStatement(int TypeId, string lpWhereClause, string lpOrderByClause, string lpJoinClause, sbyte bForwardOnly,
            int nTop, out INAVOObjectCollection pCollection)
        {
            INAVO2012ObjectCollection _Collection;

            m_oServerClient._remote_server(false).ObjectServer_OpenOnStatement(m_oServerClient._iServerClient, m_iObjectServer,
                TypeId, lpWhereClause, lpOrderByClause, lpJoinClause, bForwardOnly, nTop, out _Collection);

            pCollection = new ClientNAVOObjectCollection(_Collection) as INAVOObjectCollection;
        }

        public void ReadFromArchive(string lpSAUser, string lpPwd, string lpArchivePwd, IStream pSrcStream)
        {
            throw new NotImplementedException();
        }

        public void SetCoManagers(string pcAppName, ILockManager pLockManager, int nLockManCookie, int nOptions)
        {
            LockManager oLockManager = pLockManager as LockManager;

            m_oServerClient._remote_server(false).ObjectServer_SetCoManagers(m_oServerClient._iServerClient, m_iObjectServer,
                pcAppName, oLockManager._iLockManager, nLockManCookie, nOptions);
        }

        public void SetProp(tag_objsrv_prop nProp, object vValue)
        {
            m_oServerClient._remote_server(false).ObjectServer_SetProp(m_oServerClient._iServerClient, m_iObjectServer,
               (int)nProp, vValue);
        }

        public void SetSharedVariable(int nOriginatorCookie, int lVarNr, object nNewValue)
        {
            m_oServerClient._remote_server(false).ObjectServer_SetSharedVariable(m_oServerClient._iServerClient, m_iObjectServer,
                nOriginatorCookie, lVarNr, nNewValue);
        }

        public void WriteToArchive(string lpSAUser, string lpPwd, string lpArchivePwd, IStream pDestStream)
        {
            throw new NotImplementedException();
        }

        private ServerClient m_oServerClient;
        private int m_iObjectServer;

    }

    public class ClientNAVOObjectCollection : INAVOObjectCollection
    {
        public ClientNAVOObjectCollection(INAVO2012ObjectCollection oNAVOObjectCollection)
        {
            m_oNAVOObjectCollection = oNAVOObjectCollection;
        }

        public void Fetch(tag_fetchdir FetchDirection, ref int nCount, out int pDataLength, IntPtr lpBinaryData, int nAbsolutePosition)
        {
            throw new NotImplementedException();
        }

        public void Fetch2(tag_fetchdir FetchDirection, ref int nCount, out int pDataLength, out byte[] lpBinaryData, int nAbsolutePosition)
        {
            m_oNAVOObjectCollection.Fetch2(FetchDirection, ref nCount, out pDataLength, out lpBinaryData, nAbsolutePosition);
        }

        public void GetCount(out int pnCount)
        {
            m_oNAVOObjectCollection.GetCount(out pnCount);
        }

        public void Refresh(int nPositionToKeep, out int pnCount)
        {
            m_oNAVOObjectCollection.Refresh(nPositionToKeep, out pnCount);
        }

        private INAVO2012ObjectCollection m_oNAVOObjectCollection;
    }
}