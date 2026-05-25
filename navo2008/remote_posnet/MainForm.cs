/*
 * 
 * NAVO Enterprise 2012 universal host .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */

using System;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using Microsoft.Win32;


namespace navo2012.remote_posnet
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            RegistryKey oRemotePosnet = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\NAVO\NAVO2002\RemotePosnet");
            if (oRemotePosnet != null)
            {
                string strPort = (string)oRemotePosnet.GetValue("COM", "COM1");
                bool bVerbose = ((string)oRemotePosnet.GetValue("Verbose", "0")) == "1";

                COMSettings = new comm_settings(strPort);
                VerboseMode = bVerbose;
            }

            //clear input directory
            foreach (string strFile in file_util._naked_find_file_names(INPUT_DIRECTORY, "*.xml", false))
            {
                try
                {
                    add_message("Usuwam stary plik:" + strFile);
                    File.Delete(strFile);
                }
                catch (Exception oException)
                {
                    add_message(oException.Message);
                }
            }
        }
        #region event handlers
        /// <summary>FormLoad event</summary>
        private void MainForm_Load(object sender, EventArgs e)
        {
            add_message("Rozpoczęcie pracy");
            Timer.Tick += new EventHandler(_on_timer_tick);
            Timer.Enabled = true;
        }

        /// <summary>Form Closing</summary>
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            Timer.Enabled = false;

            if (MessageBox.Show("Czy chcesz zakończyć pracę programu ?", this.Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) != System.Windows.Forms.DialogResult.Yes)
            {
                e.Cancel = true;
                return;
            }

            add_message("Zakończenie pracy");
        }
        #endregion
        #region utilitity
        /// <summary>add message to message list</summary>
        public void add_message(string strMessage)
        {
            //if (this.InvokeRequired)
            //{
            //    this.Invoke(new hostable_service_.fpTraceMsg(add_message), strMessage);
            //}
            //else

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

            try
            {
                using (FileStream oFS = new FileStream(@".\\remote_posnet_log.txt", FileMode.OpenOrCreate, FileAccess.ReadWrite))
                {
                    oFS.Seek(0L, SeekOrigin.End);
                    using (StreamWriter oSW = new StreamWriter(oFS))
                    {
                        oSW.WriteLine(strMessage);
                    }
                }
            }
            catch
            {
            }
        }
        void _on_timer_tick(object sender, EventArgs e)
        {
            Timer.Enabled = false;

            try
            {
                //check input directory
                foreach (string strFile in file_util._naked_find_file_names(INPUT_DIRECTORY, "*.xml", false))
                {
                    print_document.do_print_document(this, strFile);
                }
            }
            finally
            {
                Timer.Enabled = true;
            }
        }
        #endregion
        #region data members
        public comm_settings COMSettings { get; set; }
        public bool VerboseMode { get; set; }

        public const string ROOT_DIRECTORY = @"c:\remote_posnet\";
        public const string INPUT_DIRECTORY = ROOT_DIRECTORY + @"in\";
        public const string DONE_DIRECTORY = ROOT_DIRECTORY + @"done\";
        public const string OUT_DIRECTORY = ROOT_DIRECTORY + @"out\";
        #endregion
    }
}
