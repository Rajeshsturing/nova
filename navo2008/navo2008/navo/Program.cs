//--------------------------------------------------------------------------
// integrated with NXM.System project
// Copyright NXM Sp. z o.o. All Rights reserved 2010-2024
//
// recreated: /../2024-09-23
//--------------------------------------------------------------------------


using nxhub;
using nxm.setup.uss;
using nxm.setup.uss.data;
using nxm.system;
using nxm.system.core.data.types.basic;
using nxm.system.core.data.types.ownership;
using nxm.system.platform.windows;
using nxm.system.runtime;
using System;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace navo
{
    class Program
    {
        #region OLE32 imports
        [DllImport("ole32.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int CoInitializeSecurity(
    IntPtr pVoid,
    int cAuthSvc,
    IntPtr asAuthSvc,
    IntPtr pReserved1,
    int dwAuthnLevel,
    int dwImpLevel,
    IntPtr pReserved2,
    int dwCapabilities,
    IntPtr pReserved3);

        [DllImport("ole32.dll", SetLastError = true)]
        public static extern int CoInitializeEx(IntPtr pvReserved, uint dwCoInit);

        [DllImport("ole32.dll", SetLastError = true)]
        public static extern void CoUninitialize();
        #endregion

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int fpRunNAVOApplication(IntPtr hInstance, [MarshalAs(UnmanagedType.LPStr)] string lpCmdLine, int nCmdShow);

        [MTAThread]
        static int Main(string[] arrOptions)
        {
            assembly_loader.register_same_folder_resolver();

            IntPtr hLibrary = _dll_import_kernel32.LoadLibrary("navo2012.pagemanager.dll");

            try
            {
                //Load
                if (hLibrary == IntPtr.Zero)
                {
                    MessageBox.Show(
                        "Nie można załadować biblioteki navo2012.pagemanager.dll lub któregoś niezbędnego komponentu",
                        nxappcore.global_config.gc_strProduct,
                        MessageBoxButtons.OK);

                    int iErrorCode = Marshal.GetLastWin32Error();
                    return iErrorCode;
                }

                int iHResult = CoInitializeEx(IntPtr.Zero, 0);

                using (new disposable_action(CoUninitialize))
                {
                    iHResult = CoInitializeSecurity(IntPtr.Zero, -1, IntPtr.Zero, IntPtr.Zero,
                       3, 3, IntPtr.Zero,
                       0, IntPtr.Zero);


                    if (!arrOptions.Any(option_ => option_.normalize() == "-un"))
                    {
                        if (arrOptions.Any(option_ => option_.normalize() == "-ul"))
                        {
                            uss_hub.TheInstance.update_provider = uss_hub.LOCAL_PROVIDER;
                        }

                        _result_<updatable_target_info> resCheck = navo_use.check_for_updates();
                        if (resCheck && resCheck.result_ != null)
                        {
                            if (MessageBox.Show(
                                $"Dostępna jest aktualizacja [{resCheck.result_.package_info.version}] dla tej stacji roboczej. Czy chcesz ją teraz zainstalować?",
                                nxappcore.global_config.gc_strProduct,
                                MessageBoxButtons.YesNo) == DialogResult.Yes)
                            {
                                _result_<(_result_ start_result_, bool exit_now_)> resStart = navo_use.do_engine_update();

                                if (resStart && resStart.result_.start_result_)
                                {
                                    if (resStart.result_.exit_now_)
                                    {
                                        return 0;
                                    }
                                }
                            }
                        }
                    }

                    IntPtr hInstance = Marshal.GetHINSTANCE(typeof(Program).Module);

                    IntPtr pRunNAVOApplicationAddr = _dll_import_kernel32.GetProcAddress(hLibrary, "?RunNAVOApplication@@YAHPAUHINSTANCE__@@PADH@Z");
                    fpRunNAVOApplication fpRunNAVOApplication = Marshal.GetDelegateForFunctionPointer(pRunNAVOApplicationAddr, typeof(fpRunNAVOApplication)) as fpRunNAVOApplication;

                    string strAssemblyPath = Assembly.GetExecutingAssembly().Location;
                    int iLocation = strAssemblyPath.LastIndexOf(".dll");
                    if (iLocation == -1)
                    {
                        iLocation = strAssemblyPath.LastIndexOf(".exe");
                    }

                    string strParamsOnly = Environment.CommandLine.Substring(iLocation + 6);

                    iHResult = fpRunNAVOApplication.Invoke(hInstance, strParamsOnly, 1);
                    return iHResult;
                }
            }
            catch (Exception oException)
            {
                MessageBox.Show(oException.ToString());

                return oException.HResult;
            }
            finally
            {
                //Free
                if (hLibrary != IntPtr.Zero)
                {
                    _dll_import_kernel32.FreeLibrary(hLibrary);
                }
            }
        }
    }
}
