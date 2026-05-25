/*
 * 
 * NAVO Enterprise 2012 server side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System;
using navo2012.net.enterprise.common;
using navo2012.proxy;
using System.Runtime.InteropServices;
using navo2012.net.host;
using System.IO;
using nxappcore;

namespace navo2012.net.enterprise.server
{
    /// <summary>remote server interface</summary>
    public class rmt_Server : MarshalByRefObject, irmt_Server
    {
        public int Server_CreateServerClient()
        {
            return Server.TheServer._create_ServerClient();
        }
        #region ServerClient
        public string ServerClient_GetUniqueId(int iServerClient)
        {
            return Server.TheServer._get_ServerClient(iServerClient).GetUniqueId();
        }
        public int ServerClient_GetService(int iServerClient, tag_navoservicetype eNST)
        {
            return Server.TheServer._get_ServerClient(iServerClient).GetService(eNST);
        }
        public int ServerClient_AdviseLM(int iServerClient, string pcUserName, string pcComputerName)
        {
            return Server.TheServer._get_ServerClient(iServerClient).AdviseLM(pcUserName, pcComputerName);
        }
        #endregion
        #region AppDBManager
        public void AppDBManager_Init(int iServerClient, int iAppDBManager, string lpAppName)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_AppDBManager(iAppDBManager).Init(lpAppName);
        }
        public void AppDBManager_GetFinalStream(int iServerClient, int iAppDBManager, int IdFile, string pcEnvironentStr, out Stream oStream, out navo2012_stream_info oNSI)
        {
            navostreaminfo _NSI;
            IStream _Stream;

            Server.TheServer._get_ServerClient(iServerClient)._get_AppDBManager(iAppDBManager).GetFinalStream(IdFile, pcEnvironentStr, out _Stream, out _NSI);

            oNSI.m_bCompressed = _NSI.m_bCompressed;
            oNSI.m_cExt = (sbyte[])_NSI.m_cExt.Clone();

            oStream = (_Stream == null) ? null : new nxcomstream(_Stream);
        }
        public void AppDBManager_GetItemInfo(int iServerClient, int iAppDBManager,
              int nInfoType, int IdFile, out DateTime pModifDate, out int pnVarCntr, out int[] ppVarNr)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_AppDBManager(iAppDBManager).GetItemInfo2(nInfoType, IdFile, out pModifDate, out pnVarCntr, out ppVarNr);
        }
        public void AppDBManager_StreamProvGet(int iServerClient, int iAppDBManager, int IdFile, out Stream oStream, out navo2012_stream_info oNSI)
        {
            IAppDBManager oAppDBManager = Server.TheServer._get_ServerClient(iServerClient)._get_AppDBManager(iAppDBManager);
            Guid oGUID = typeof(IStreamProvider).GUID;

            IntPtr ptrUnknown = Marshal.GetIUnknownForObject(oAppDBManager);
            IntPtr ptrStreamProv;
            Marshal.QueryInterface(ptrUnknown, ref oGUID, out ptrStreamProv);
            IStreamProvider oStreamProv = Marshal.GetObjectForIUnknown(ptrStreamProv) as IStreamProvider;
            Marshal.Release(ptrUnknown);

            navostreaminfo _NSI;
            IStream _Stream;

            oStreamProv.Get(IdFile, out _Stream, out _NSI);
            oNSI.m_bCompressed = _NSI.m_bCompressed;
            oNSI.m_cExt = (sbyte[])_NSI.m_cExt.Clone();

            oStream = (_Stream == null) ? null : new nxcomstream(_Stream);

            Marshal.Release(ptrStreamProv);
        }
        #endregion
        #region ObjectServer
        public void ObjectServer_SetProp(int iServerClient, int iObjectServer, int nProp, object vValue)
        {
            IObjectServer oObjectServer = Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer);
            oObjectServer.SetProp((tag_objsrv_prop)nProp, vValue);
        }

        public void ObjectServer_SetCoManagers(int iServerClient, int iObjectServer,
            string pcAppName, int iLockManager, int nLockManCookie, int nOptions)
        {
            ServerClient oServerClient = Server.TheServer._get_ServerClient(iServerClient);
            IObjectServer oObjectServer = oServerClient._get_ObjectServer(iObjectServer);
            ILockManager oLockManager = oServerClient._get_LockManager(iLockManager);

            oObjectServer.SetCoManagers(pcAppName, oLockManager, nLockManCookie, nOptions);
        }

        public int ObjectServer_FindOnField(int iServerClient, int iObjectServer, int nTypeId, string lpWhereClause)
        {
            int idFound;
            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).FindOnField(nTypeId, lpWhereClause, out idFound);
            return idFound;
        }
        public void ObjectServer_ExecSQL(int iServerClient, int iObjectServer, string lpSQLCommand, out int pRecordsAffected)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).ExecSQL(lpSQLCommand, out pRecordsAffected);
        }
        public void ObjectServer_GetObjectIfNewer2(int iServerClient, int iObjectServer, int nTypeId, int IdObj,
            int VersionNoReturn, sbyte bWriteLock, out int pDataLength, out byte[] lpBinaryData)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).GetObjectIfNewer2(nTypeId, IdObj,
                VersionNoReturn, bWriteLock, out pDataLength, out lpBinaryData);
        }
        public void ObjectServer_GetSharedVariable(int iServerClient, int iObjectServer, int lVarNr, out object pvValue)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).
                GetSharedVariable(lVarNr, out pvValue);
        }
        public void ObjectServer_SetSharedVariable(int iServerClient, int iObjectServer,
            int nOriginatorCookie, int lVarNr, object nNewValue)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).
                SetSharedVariable(nOriginatorCookie, lVarNr, nNewValue);
        }
        public void ObjectServer_GetUniqueIdent(int iServerClient, int iObjectServer, int nTypeId, out int pNewId)
        {
            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).GetUniqueIdent(nTypeId, out pNewId);
        }
        public void ObjectServer_GetStream(int iServerClient, int iObjectServer, int IdParent, int IdMapping,
            out Stream oStream, out navo2012_stream_info oNSI, out int pVersion, out int pStreamId)
        {
            navostreaminfo _NSI;
            IStream _Stream;

            Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer).
                GetStream(IdParent, IdMapping, out _Stream, out _NSI, out pVersion, out pStreamId);

            oNSI.m_bCompressed = _NSI.m_bCompressed;
            oNSI.m_cExt = (sbyte[])_NSI.m_cExt.Clone();

            oStream = (_Stream == null) ? null : new nxcomstream(_Stream);
        }
        public void ObjectServer_MakeTransaction(int iServerClient, int iObjectServer, byte[] arrBinData,
           navo2012_blob_info[] arrBlobInfo, navo2012_lock[] arrLockInfo, sbyte bCommit)
        {
            IObjectServer oObjectServer = Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer);

            tag_transblobinfo[] _BlobInfo = (arrBlobInfo == null) ? null : new tag_transblobinfo[arrBlobInfo.Length];
            if (arrBlobInfo != null)
            {
                for (int iIter = 0; iIter < arrBlobInfo.Length; iIter++)
                {
                    _BlobInfo[iIter] = new tag_transblobinfo();
                    arrBlobInfo[iIter].marshal(_BlobInfo[iIter]);
                }
            }

            tag_navolock[] _LockInfo = (arrLockInfo == null) ? null : new tag_navolock[arrLockInfo.Length];
            if (arrLockInfo != null)
            {
                for (int iIter = 0; iIter < arrBlobInfo.Length; iIter++)
                {
                }
            }

            oObjectServer.MakeTransaction2(ref arrBinData, ref _BlobInfo, ref _LockInfo, bCommit);
        }
        public void ObjectServer_OpenOnStatement(int iServerClient, int iObjectServer,
            int TypeId, string lpWhereClause, string lpOrderByClause, string lpJoinClause, sbyte bForwardOnly,
            int nTop, out INAVO2012ObjectCollection pCollection)
        {
            IObjectServer oObjectServer = Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer);

            INAVOObjectCollection _Collection;
            oObjectServer.OpenOnStatement(TypeId, lpWhereClause, lpOrderByClause, lpJoinClause, bForwardOnly, nTop, out _Collection);

            pCollection = new ServerNAVOObjectCollection(_Collection) as INAVO2012ObjectCollection;
        }
        public void ObjectServer_OpenCollection(int iServerClient, int iObjectServer, int CollectionId,
            int IdParent, out int pTotalCount, out INAVO2012ObjectCollection pCollection)
        {
            IObjectServer oObjectServer = Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer);

            INAVOObjectCollection _Collection;
            oObjectServer.OpenCollection(CollectionId, IdParent, out pTotalCount, out _Collection);

            pCollection = new ServerNAVOObjectCollection(_Collection) as INAVO2012ObjectCollection;
        }
        public void ObjectServer_OpenDiscoRecSet(int iServerClient, int iObjectServer, string lpSQLClause, out Stream oStream, out navo2012_stream_info oNSI)
        {
            navostreaminfo _NSI;
            IStream _Stream;

            IObjectServer oObjectServer = Server.TheServer._get_ServerClient(iServerClient)._get_ObjectServer(iObjectServer);
            oObjectServer.OpenDiscoRecSet(lpSQLClause, out _Stream, out _NSI);

            oNSI.m_bCompressed = _NSI.m_bCompressed;
            oNSI.m_cExt = (sbyte[])_NSI.m_cExt.Clone();

            oStream = (_Stream == null) ? null : new nxcomstream(_Stream);
        }
        #endregion
        #region CntResourceManager
        public void CntResourceManager_CreateResource(int iServerClient, int iLockManager, string pcResName, int nMaxUsage)
        {
            ILockManager oLockManager = Server.TheServer._get_ServerClient(iServerClient)._get_LockManager(iLockManager);
            IntPtr ptrUnknown = Marshal.GetComInterfaceForObject(oLockManager, typeof(ICntResourceManager));
            ICntResourceManager oCntResourceManager = Marshal.GetObjectForIUnknown(ptrUnknown) as ICntResourceManager;

            oCntResourceManager.CreateResource(pcResName, nMaxUsage);

            Marshal.Release(ptrUnknown);

        }
        public void CntResourceManager_DeleteResource(int iServerClient, int iLockManager, string pcResName)
        {
            ILockManager oLockManager = Server.TheServer._get_ServerClient(iServerClient)._get_LockManager(iLockManager);
            IntPtr ptrUnknown = Marshal.GetComInterfaceForObject(oLockManager, typeof(ICntResourceManager));
            ICntResourceManager oCntResourceManager = Marshal.GetObjectForIUnknown(ptrUnknown) as ICntResourceManager;

            oCntResourceManager.DeleteResource(pcResName);

            Marshal.Release(ptrUnknown);
        }
        public void CntResourceManager_ReleaseResource(int iServerClient, int iLockManager, string pcResName, int nOriginatorCookie)
        {
            ILockManager oLockManager = Server.TheServer._get_ServerClient(iServerClient)._get_LockManager(iLockManager);
            IntPtr ptrUnknown = Marshal.GetComInterfaceForObject(oLockManager, typeof(ICntResourceManager));
            ICntResourceManager oCntResourceManager = Marshal.GetObjectForIUnknown(ptrUnknown) as ICntResourceManager;

            oCntResourceManager.ReleaseResource(pcResName, nOriginatorCookie);

            Marshal.Release(ptrUnknown);
        }
        public void CntResourceManager_UseResource(int iServerClient, int iLockManager, string pcResName, int nOriginatorCookie)
        {
            ILockManager oLockManager = Server.TheServer._get_ServerClient(iServerClient)._get_LockManager(iLockManager);
            IntPtr ptrUnknown = Marshal.GetComInterfaceForObject(oLockManager, typeof(ICntResourceManager));
            ICntResourceManager oCntResourceManager = Marshal.GetObjectForIUnknown(ptrUnknown) as ICntResourceManager;

            oCntResourceManager.UseResource(pcResName, nOriginatorCookie);

            Marshal.Release(ptrUnknown);
        }
        #endregion
    }

    public class ServerNAVOObjectCollection : MarshalByRefObject, INAVO2012ObjectCollection
    {
        internal ServerNAVOObjectCollection(INAVOObjectCollection oNAVOObjectCollection)
        {
            m_oNAVOObjectCollection = oNAVOObjectCollection;
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

        private INAVOObjectCollection m_oNAVOObjectCollection;
    }
}
