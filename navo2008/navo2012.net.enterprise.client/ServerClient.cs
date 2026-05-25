/*
 * 
 * NAVO Enterprise 2012 client side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System;
using System.Runtime.InteropServices;
using navo2012.net.enterprise.common;
using navo2012.proxy;

namespace navo2012.net.enterprise.client
{
    [ComVisible(true)]
    public class ServerClient : IServerClient
    {
        #region constructor
        /// <summary>universal constructor</summary>
        internal ServerClient(string strServerName)
        {
            m_strTCPPort = "6080";
            m_strServerName = strServerName;
        }
        #endregion
        #region interface
        public void AdviseLM(string pcUserName, string pcComputerName, out int pCookie)
        {
            pCookie = _remote_server(false).ServerClient_AdviseLM(m_iServerClient, pcUserName, pcComputerName);
        }

        public void AdviseNM(object pONSinkUnknown, string pcUserName, string pcComputerName, tag_notifysinkclass eNSC, out int pCookie)
        {
            pCookie = -1;
        }

        public void EnumRegistryKeys(int hKeyClass, string lpSubKey, out string plpValue)
        {
            throw new NotImplementedException();
        }

        public void GetRegistryKeyString(int hKeyClass, string lpSubKey, string lpName, out string plpValue)
        {
            throw new NotImplementedException();
        }

        public void GetService(tag_navoservicetype eNST, out object ppUnknown)
        {
            int iService = _remote_server(false).ServerClient_GetService(m_iServerClient, eNST);

            switch (eNST)
            {
                case tag_navoservicetype.nst_notman:
                    {
                        NotificationManager oNotificationManager = new NotificationManager(this, iService);
                        ppUnknown = oNotificationManager;
                    }
                    return;
                case tag_navoservicetype.nst_lockman:
                    {
                        LockManager oLockManager = new LockManager(this, iService);
                        ppUnknown = oLockManager;
                    }
                    return;
                case tag_navoservicetype.nst_appdb:
                    {
                        AppDBManager oAppDBManager = new AppDBManager(this, iService);
                        ppUnknown = oAppDBManager;
                    }
                    return;
                case tag_navoservicetype.nst_objserver:
                    {
                        ObjectServer oObjectServer = new ObjectServer(this, iService);
                        ppUnknown = oObjectServer;
                    }
                    return;
            }

            ppUnknown = null;
        }

        public void GetUniqueId(out string ppUniqueId)
        {
            ppUniqueId = _remote_server(false).ServerClient_GetUniqueId(m_iServerClient);
        }

        public void GetUpdateVersionIfNewer(int nUpdateType, string lpClientVersion, out IStream ppDataStream, out IStream ppInfoStream)
        {
            ppDataStream = null;
            ppInfoStream = null;

            //throw new NotImplementedException();
        }

        public void SetRegistryKeyString(int hKeyClass, string lpSubKey, string lpName, string lpValue)
        {
            throw new NotImplementedException();
        }

        public void UnAdviseLM(int nCookie)
        {
            throw new NotImplementedException();
        }

        public void UnAdviseNM(int nCookie)
        {
        }
        #endregion
        #region implementation
        internal int _iServerClient
        {
            get { return m_iServerClient; }
        }
        internal irmt_Server _remote_server(bool bReconnect)
        {
            if (m_oRemoteServer == null || bReconnect)
            {
                m_oRemoteServer = (irmt_Server)Activator.GetObject(typeof(irmt_Server),
                    String.Format("tcp://{0}:{1}/{2}", m_strServerName, m_strTCPPort, "navo2012.net.enterprise.server"));

                if (m_iServerClient == 0)
                {
                    m_iServerClient = m_oRemoteServer.Server_CreateServerClient();
                }
            }

            return m_oRemoteServer;
        }
        #endregion
        #region data members
        private string m_strServerName;
        private string m_strTCPPort;
        private irmt_Server m_oRemoteServer;
        private int m_iServerClient;
        #endregion
    }
}
