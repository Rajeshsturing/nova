/*
 * 
 * NAVO Enterprise 2012 server side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System.Collections.Generic;
using System.Threading;
using navo2012.net.host;
using navo2012.proxy;
using nxappcore;
using n8.common;

namespace navo2012.net.enterprise.server
{
    /// <summary>Server, singleton</summary>
    public class Server : hostable_service_
    {
        #region constructor
        /// <summary>universal constructor</summary>
        public Server()
        {
            m_oSyncRoot = new object();
            m_oExitNowEvent = new ManualResetEvent(false);
            m_oAllowToExitEvent = new ManualResetEvent(true);
            m_dictServerClient = new Dictionary<int, ServerClient>();
        }
        #endregion
        #region hostable-service
        /// <summary>run</summary>
        public override void run()
        {
            TraceMsg("NAVO Enterprise 2012.Server started");
            
            m_oAllowToExitEvent.Reset();
            _g_oServer = this;
            _start_tcp_listener();

            TraceMsg("NAVO Enterprise 2012.Server listening");
            
            m_oExitNowEvent.WaitOne();

            _stop_tcp_listener();
            _g_oServer = null;
            m_oAllowToExitEvent.Set();
        }
        /// <summary>signal exit and wait for completition</summary>
        public override void signal_exit_and_wait()
        {
            m_oExitNowEvent.Set();
            m_oAllowToExitEvent.WaitOne();
        }
        /// <summary>
        /// 
        /// </summary>
        public override void Dispose()
        {
        }
        /// <summary>start remote service listener</summary>
        private void _start_tcp_listener()
        {
            m_oTCPListener = new tcp_listener();
            m_oTCPListener.publish_to_network(6080);
            m_oTCPListener.register_service(typeof(rmt_Server), "navo2012.net.enterprise.server", false);
        }
        /// <summary>stop remote service listener</summary>
        private void _stop_tcp_listener()
        {
            if (m_oTCPListener != null)
            {
                m_oTCPListener.Dispose();
                m_oTCPListener = null;
            }
        }
        #endregion
        #region operations
        internal int _create_ServerClient()
        {
            IServerClient _ServerClient = Microsoft.VisualBasic.Interaction.CreateObject("navo2002.server") as IServerClient;

            ServerClient oServerClient = new ServerClient(_ServerClient);

            lock (_SyncRoot)
            {
                int iServerClient = ++m_iGenerator;
                m_dictServerClient.Add(iServerClient, oServerClient);
                return iServerClient;
            }
        }
        internal ServerClient _get_ServerClient(int iServerClient)
        {
            lock (_SyncRoot)
            {
                return m_dictServerClient[iServerClient];
            }
        }
        internal void _destroy_ServerClient(int iServerClient)
        {
            ServerClient oServerClient = null;

            lock (_SyncRoot)
            {
                oServerClient = m_dictServerClient[iServerClient];
                m_dictServerClient.Remove(iServerClient);
            }

            oServerClient.destroy();
        }
        #endregion
        #region properties
        /// <summary>SyncRoot</summary>
        private object _SyncRoot
        {
            get { return m_oSyncRoot; }
        }
        /// <summary>returns TheServer</summary>
        internal static Server TheServer
        {
            get { return _g_oServer; }
        }
        #endregion
        #region data members
        /// <summary>trace msg event</summary>
        public override event fpTraceMsg TraceMsg;
        /// <summary>sync-root</summary>
        private object m_oSyncRoot;
        /// <summary>exit-now-request</summary>
        private ManualResetEvent m_oExitNowEvent;
        /// <summary>allowed-to-exit flag</summary>
        private ManualResetEvent m_oAllowToExitEvent;

        private tcp_listener m_oTCPListener;
        /// <summary>serverclient dictionary</summary>
        private Dictionary<int, ServerClient> m_dictServerClient;
        /// <summary>ident generator</summary>
        private int m_iGenerator;
        /// <summary>The Server</summary>
        private static Server _g_oServer;
        #endregion
    }
}
