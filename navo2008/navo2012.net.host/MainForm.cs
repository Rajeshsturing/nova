/*
 * 
 * NAVO Enterprise 2012 universal host .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;
using n8.common;

namespace navo2012.net.host
{
    public partial class MainForm : Form
    {
        public MainForm(IEnumerable<hostable_service_> collServices)
        {
            m_collServices = collServices;

            InitializeComponent();
        }
        #region event handlers
        /// <summary>FormLoad event</summary>
        private void MainForm_Load(object sender, EventArgs e)
        {
            foreach (hostable_service_ oService in m_collServices)
            {
                oService.TraceMsg += add_message;
                new Thread(new ThreadStart(oService.run)).Start();
            }
        }
        /// <summary>Form Closing</summary>
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            foreach (hostable_service_ oService in m_collServices)
            {
                oService.TraceMsg -= add_message;
                oService.signal_exit_and_wait();
            }
        }
        #endregion
        #region utilitity
        /// <summary>add message to message list</summary>
        public void add_message(string strMessage)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new hostable_service_.fpTraceMsg(add_message), strMessage);
            }
            else
            {
                add_message(strMessage, true);
            }
        }
        /// <summary>add message to message list</summary>
        public void add_message(string strMessage, bool bWithTimeStamp)
        {
            while (messages_list.Items.Count > 2000)
            {
                messages_list.Items.RemoveAt(0);
            }
            if (bWithTimeStamp)
            {
                strMessage = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss ") + strMessage;
            }
            messages_list.Items.Add(strMessage);
            messages_list.SelectedIndex = messages_list.Items.Count - 1;
        }
        #endregion
        #region data members
        /// <summary>hosted servers</summary>
        private IEnumerable<hostable_service_> m_collServices;
        #endregion
    }
}
