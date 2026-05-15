//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.ebwrap;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;

namespace navo.cocoon
{
    [ComVisible(true)]
    public class message_sink : IDisposable
    {
        public message_sink(ne_trans oTransaction, Action<int, string> fpOnMessage)
        {
            m_oTransaction = oTransaction;
            m_fpOnMessage = fpOnMessage;
            m_oTransaction.message_sink(this);
        }
        public void on_message(int iErrorCode, string strMessage)
        {
            m_fpOnMessage?.Invoke(iErrorCode, strMessage);
        }
        #region IDisposable Members
        public void Dispose()
        {
            GC.SuppressFinalize(this);
            Dispose(true);
        }
        public void Dispose(bool bDisposing)
        {
            if (bDisposing)
            {
                m_oTransaction?.message_sink(null);
                m_oTransaction = null;
            }
        }
        #endregion
        private ne_trans m_oTransaction;
        private Action<int, string> m_fpOnMessage;
    }
}