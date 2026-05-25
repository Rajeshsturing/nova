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
    public class NotificationManager : INotificationManager
    {
        internal NotificationManager(ServerClient oServerClient, int iNotificationManager)
        {
            m_oServerClient = oServerClient;
            m_iNotificationManager = iNotificationManager;
        }
        internal int _iNotificationManager
        {
            get { return m_iNotificationManager; }
        }
    
        public void Advise(object pONSinkUnknown, string pcUserName, string pcComputerName, tag_notifysinkclass eNSC, out int pCookie)
        {
            throw new NotImplementedException();
        }

        public void Close()
        {
            throw new NotImplementedException();
        }

        public void GetProp(int nCookie, int nProp, out object pvValue)
        {
            throw new NotImplementedException();
        }

        public void NotifyMultipleUsers(int nOriginatorCookie, int nCount, ref int pDestinatorCookies, int lEvenCode, ref object pDataVariant)
        {
            throw new NotImplementedException();
        }

        public void NotifySharedVariableChange(int nOriginatorCookie, int lVarNr, object nNewValue)
        {
            throw new NotImplementedException();
        }

        public void NotifyUser(int nOriginatorCookie, int nDestinatorCookie, int lEvenCode, ref object pDataVariant)
        {
            throw new NotImplementedException();
        }

        public void QuerySinks(out int pDataLength, IntPtr lpBinaryData)
        {
            throw new NotImplementedException();
        }

        public void SetProp(int nCookie, int nProp, object vValue)
        {
            throw new NotImplementedException();
        }

        public void UnAdvise(int nCookie)
        {
            throw new NotImplementedException();
        }

        private ServerClient m_oServerClient;
        private int m_iNotificationManager;
    }
}