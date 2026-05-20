
//--------------------------------------------------------------------------
// NXM.System project
// Copyright NXM Sp. z o.o. All Rights reserved 2010-2015
//
// change_set - change set
// 
// created: 2015-05-05
//--------------------------------------------------------------------------

using nxm.biz.data;
using nxm.biz.data.store;
using nxm.core.data.ps;
using nxm.core.services;
using nxm.core.types;
using nxm.erp.navo_eurobusiness.ps;
using System;
using System.Diagnostics;

namespace nxm.biz.store
{
    public class _dev_tests_
    {
        public static void run()
        {
            Console.WriteLine("NAVO JetGM demonstrator technologii/ test kompatybilnosci");
            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("UWAGA! PRZED URUCHOMIENIEM TEGO PROGRAMU ZRÓB ARCHIWUM DANYCH");
            Console.WriteLine("Wpisz 'GOTOWE' i naciśnij ENTER aby mieć pewność, że zrobiłeś archiwum.");
            Console.WriteLine("----------------------------------------------------------");
            string strTest = Console.ReadLine();
            if (strTest != "GOTOWE")
            {
                Console.WriteLine("Dla bezpieczeństwa wychodzę.");
                return;
            }

            Console.WriteLine("Wpisz nazwę serwera SQL i naciśnij ENTER [domyślnie .\\navo2012].");
            string strSQL = Console.ReadLine();
            if (strSQL == "")
            {
                strSQL = ".\\navo2012";
            }
            Console.WriteLine("Wpisz nazwę bazy danych i naciśnij ENTER [domyślnie navo2002].");
            string strDB = Console.ReadLine();
            if (strDB == "")
            {
                strDB = "navo2002";
            }
            Stopwatch oSW = new Stopwatch();
            service_connection_param oParams = new service_connection_param();
            oParams.parameters = new _variant_set_("server_path", strSQL, "database_name", strDB);

            ierp_store_ps_operations oStorageOperations = new navo_eurobusiness_erp_store_ps_operations(oParams, null);

            store_manager oSM = store_manager.create();

            Console.WriteLine("----------------------------------------------------------");
            Console.WriteLine("wstępne ładowanie danych (tylko raz przy starcie całego systemu");
            oSW.Start();
            _store_error_info_ oError = oSM.initialize(oStorageOperations, 0, store_manager.eInitializeMode.default_, false);
            if(oError!=null)
            {
                System.Console.WriteLine(oError.ToString());
            }
            System.Console.WriteLine($"czas={oSW.ElapsedMilliseconds / 1000.0m} s");


            if (oSM.try_begin_store_transaction())
            {
                try
                {
                    Console.WriteLine("----------------------------------------------------------");
                    Console.WriteLine("synchronizacja danych (np. przed raportami)");
                    oSW.Restart();

                    oError = oSM.process_request(oStorageOperations, null, true, null);
                    if (oError != null)
                    {
                        System.Console.WriteLine(oError.ToString());
                    }
                    System.Console.WriteLine($"czas={oSW.ElapsedMilliseconds / 1000.0m} s");
                    oSW.Restart();

                    Console.WriteLine("----------------------------------------------------------");
                    Console.WriteLine("obsługa wstawienia dokumentu np. WZ");

                    oError = oSM.process_request(oStorageOperations,
                        new apply_doc_params()
                        {
                            SeqNo = 1163840,
                            isStoreDoc = true,
                            ForDelete = false
                        }.as_enumerable(), false, null);
                    if (oError != null)
                    {
                        System.Console.WriteLine(oError.ToString());
                    }
                    System.Console.WriteLine($"czas={oSW.ElapsedMilliseconds / 1000.0m} s");
                }
                finally
                {
                    oSM.end_store_transaction();
                }
            }

            Console.WriteLine("naciśnij ENTER aby zakończyć.");
            System.Console.ReadLine();
        }
    }
}