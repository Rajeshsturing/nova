/*
 * 
 * NAVO Enterprise 2012 client side .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */
using System.Runtime.InteropServices;
using navo2012.proxy;

namespace navo2012.net.enterprise.client
{
    [ComVisible(true)]
    [GuidAttribute("188CB16F-2012-4498-87D0-EBD8D9A00FB8")]
    public class ServerClientFactory : IServerClientFactory
    {
        #region constructor
        /// <summary>universal constructor</summary>
        public ServerClientFactory()
        {
        }
        #endregion
        #region
        /// <summary>create instance of server-client-proxy</summary>
        public void GetServerClient(string lpServerName, out IServerClient ppServerClient)
        {
            ppServerClient = new ServerClient(lpServerName);
        }
        #endregion
    }
}
