/*
 * 
 * NAVO Enterprise 2012 server side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System.Collections.Generic;
using navo2012.proxy;

namespace navo2012.net.enterprise.server
{
    internal class ServerClient
    {
        #region constructor / destructor
        /// <summary>universal constructor</summary>
        internal ServerClient(IServerClient oServerClient)
        {
            m_oSyncRoot = new object();
            m_dictServices = new Dictionary<int, object>();

            m_oServerClient = oServerClient;
        }
        internal void destroy()
        {
        }
        #endregion
        #region operations
        internal string GetUniqueId()
        {
            string strId;
            m_oServerClient.GetUniqueId(out strId);
            return strId;
        }
        internal int GetService(tag_navoservicetype eNST)
        {
            object oService;

            m_oServerClient.GetService(eNST, out oService);

            lock (_SyncRoot)
            {
                int iService = ++m_iGenerator;
                m_dictServices.Add(iService, oService);
                return iService;
            }
        }
        internal int AdviseLM(string pcUserName, string pcComputerName)
        {
            int iCookie;
            m_oServerClient.AdviseLM(pcUserName, pcComputerName, out iCookie);
            return iCookie;
        }
        internal IAppDBManager _get_AppDBManager(int iService)
        {
            lock (_SyncRoot)
            {
                return m_dictServices[iService] as IAppDBManager;
            }
        }
        internal IObjectServer _get_ObjectServer(int iService)
        {
            lock (_SyncRoot)
            {
                return m_dictServices[iService] as IObjectServer;
            }
        }
        internal ILockManager _get_LockManager(int iService)
        {
            lock (_SyncRoot)
            {
                return m_dictServices[iService] as ILockManager;
            }
        }
        #endregion
        #region implementation
        /// <summary>SyncRoot</summary>
        private object _SyncRoot
        {
            get { return m_oSyncRoot; }
        }
        #endregion
        #region data members
        /// <summary>sync-root</summary>
        private object m_oSyncRoot;
        /// <summary>ident generator</summary>
        private int m_iGenerator;

        private IServerClient m_oServerClient;
        private Dictionary<int, object> m_dictServices;
        #endregion
    }
}
