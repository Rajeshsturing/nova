/*
 * 
 * NAVO Enterprise 2012 universal host .Net Remoting transport
 * Copyright 2012 by NAVO Sp. z o.o.
 * 
 */
using System;
using System.Windows.Forms;
using n8.common;

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
            hostable_service_[] arrServices =
                new hostable_service_[] 
                { 
                    //new navo2012.net.enterprise.server.Server(),
                    new n8.server.Server()
                };

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Application.Run(new MainForm(arrServices));
        }
    }
}
