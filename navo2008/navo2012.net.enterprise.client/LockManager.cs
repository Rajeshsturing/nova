/*
 * 
 * NAVO Enterprise 2012 client side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */
using System;
using System.Runtime.InteropServices;
using navo2012.proxy;

namespace navo2012.net.enterprise.client
{
    [ComVisible(true)]
    public class LockManager : ILockManager, ICntResourceManager
    {
        internal LockManager(ServerClient oServerClient, int iLockManager)
        {
            m_oServerClient = oServerClient;
            m_iLockManager = iLockManager;
        }
        internal int _iLockManager
        {
            get { return m_iLockManager; }
        }
        public void Advise(string pcUserName, string pcComputerName, out int pCookie)
        {
            throw new NotImplementedException();
        }

        public void Lock(int nOriginatorCookie, sbyte bLock, int nCount, ref tag_navolock pNavoLock)
        {
            throw new NotImplementedException();
        }

        public void UnAdvise(int nCookie)
        {
            throw new NotImplementedException();
        }

        public void CreateResource(string pcResName, int nMaxUsage)
        {
            m_oServerClient._remote_server(false).CntResourceManager_CreateResource(
                m_oServerClient._iServerClient, m_iLockManager, pcResName, nMaxUsage);
        }

        public void DeleteResource(string pcResName)
        {
            m_oServerClient._remote_server(false).CntResourceManager_DeleteResource(
                m_oServerClient._iServerClient, m_iLockManager, pcResName);
        }

        public void ReleaseResource(string pcResName, int nOriginatorCookie)
        {
            m_oServerClient._remote_server(false).CntResourceManager_ReleaseResource(
               m_oServerClient._iServerClient, m_iLockManager, pcResName, nOriginatorCookie);
        }

        public void UseResource(string pcResName, int nOriginatorCookie)
        {
            m_oServerClient._remote_server(false).CntResourceManager_UseResource(
               m_oServerClient._iServerClient, m_iLockManager, pcResName, nOriginatorCookie);
        }

        private ServerClient m_oServerClient;
        private int m_iLockManager;

    }
}