/*
 * 
 * NAVO Enterprise 2012 common side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System;
using navo2012.proxy;
using navo2012.net.host;
using System.IO;

namespace navo2012.net.enterprise.common
{
    public interface irmt_Server
    {
        int Server_CreateServerClient();

        #region ServerClient
        string ServerClient_GetUniqueId(int iServerClient);

        int ServerClient_GetService(int iServerClient, tag_navoservicetype eNST);
        int ServerClient_AdviseLM(int iServerClient, string pcUserName, string pcComputerName);
        #endregion
        #region AppDBManager
        void AppDBManager_Init(int iServerClient, int iAppDBManager, string lpAppName);
        void AppDBManager_GetFinalStream(int iServerClient, int iAppDBManager, int IdFile,
            string pcEnvironentStr, out Stream oStream, out navo2012_stream_info oNSI);
        void AppDBManager_GetItemInfo(int iServerClient, int iAppDBManager,
            int nInfoType, int IdFile, out DateTime pModifDate, out int pnVarCntr, out int[] ppVarNr);
        void AppDBManager_StreamProvGet(int iServerClient, int iAppDBManager,
            int IdFile, out Stream oStream, out navo2012_stream_info oNSI);
        #endregion
        #region ObjectServer
        void ObjectServer_SetProp(int iServerClient, int iObjectServer, int nProp, object vValue);
        void ObjectServer_SetCoManagers(int iServerClient, int iObjectServer,
            string pcAppName, int iLockManager, int nLockManCookie, int nOptions);
        int ObjectServer_FindOnField(int iServerClient, int iObjectServer, int nTypeId, string lpWhereClause);
        void ObjectServer_ExecSQL(int iServerClient, int iObjectServer, string lpSQLCommand, out int pRecordsAffected);
        void ObjectServer_GetObjectIfNewer2(int iServerClient, int iObjectServer, int nTypeId, int IdObj,
            int VersionNoReturn, sbyte bWriteLock, out int pDataLength, out byte[] lpBinaryData);
        void ObjectServer_GetSharedVariable(int iServerClient, int iObjectServer, int lVarNr, out object pvValue);
        void ObjectServer_SetSharedVariable(int iServerClient, int iObjectServer,
            int nOriginatorCookie, int lVarNr, object nNewValue);
        void ObjectServer_GetStream(int iServerClient, int iObjectServer, int IdParent, int IdMapping,
            out Stream oStream, out navo2012_stream_info oNSI, out int pVersion, out int pStreamId);
        void ObjectServer_GetUniqueIdent(int iServerClient, int iObjectServer, int nTypeId, out int pNewId);
        void ObjectServer_MakeTransaction(int iServerClient, int iObjectServer, byte[] arrBinData,
            navo2012_blob_info[] arrBlobInfo, navo2012_lock[] arrLockInfo, sbyte bCommit);
        void ObjectServer_OpenOnStatement(int iServerClient, int iObjectServer,
            int TypeId, string lpWhereClause, string lpOrderByClause, string lpJoinClause, sbyte bForwardOnly,
            int nTop, out INAVO2012ObjectCollection pCollection);
        void ObjectServer_OpenCollection(int iServerClient, int iObjectServer, int CollectionId,
            int IdParent, out int pTotalCount, out INAVO2012ObjectCollection pCollection);
        void ObjectServer_OpenDiscoRecSet(int iServerClient, int iObjectServer, string lpSQLClause, out Stream oStream, out navo2012_stream_info oNSI);
        #endregion
        #region CntResourceManager
        void CntResourceManager_CreateResource(int iServerClient, int iLockManager, string pcResName, int nMaxUsage);
        void CntResourceManager_DeleteResource(int iServerClient, int iLockManager, string pcResName);
        void CntResourceManager_ReleaseResource(int iServerClient, int iLockManager, string pcResName, int nOriginatorCookie);
        void CntResourceManager_UseResource(int iServerClient, int iLockManager, string pcResName, int nOriginatorCookie);
        #endregion
    }
}