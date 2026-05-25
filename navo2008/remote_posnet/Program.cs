/*
 * 
 * NAVO Enterprise 2012 universal host .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */
using System;
using System.Windows.Forms;
using navo2012.remote_posnet;

namespace navo2012.net.host
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Application.Run(new MainForm());
        }
    }
}
