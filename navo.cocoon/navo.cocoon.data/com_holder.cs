//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
//
//--------------------------------------------------------------------------

using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

namespace navo.cocoon.data.utils
{
    /// <summary>wraps COM object and releases it at dispose</summary>
    public class com_holder : IDisposable
    {
        #region public api
        /// <summary>universal constructor</summary>
        public com_holder(object oCOMObject)
        {
            m_oCOMObject = oCOMObject;
            Trace("holder created null=" + (oCOMObject == null) + " type=" + (oCOMObject == null ? "null" : oCOMObject.GetType().FullName));
        }
        /// <summary>invokes method on owned object
        /// returns plain type</summary>
        public TType invoke_method_plain<TType>(String strMethodName, params object[] oParams)
        {
            Trace("invoke_method_plain begin method=" + strMethodName
                + " argc=" + (oParams == null ? 0 : oParams.Length)
                + " target_null=" + (m_oCOMObject == null)
                + " target_type=" + (m_oCOMObject == null ? "null" : m_oCOMObject.GetType().FullName)
                + " " + FormatParams(oParams));
            try
            {
                if (m_oCOMObject == null)
                {
                    throw new InvalidOperationException("Cannot invoke COM method on a null COM object.");
                }

                TraceDispatchProbe(strMethodName);
                object oResult = m_oCOMObject.GetType().InvokeMember(strMethodName, BindingFlags.InvokeMethod, null, m_oCOMObject, oParams);
                Trace("invoke_method_plain ok method=" + strMethodName + " result_type=" + (oResult == null ? "null" : oResult.GetType().FullName) + " result=" + Convert.ToString(oResult));
                return (TType)oResult;
            }
            catch (Exception ex)
            {
                Trace("invoke_method_plain exception method=" + strMethodName + " " + FormatException(ex));
                throw;
            }
        }

        /// <summary>
        /// invokes method on owned object
        /// return com-holder for returned object</summary>
        public com_holder invoke_method_object(String strMethodName, params object[] oParams)
        {
            object oCOMObject = m_oCOMObject.GetType().InvokeMember(strMethodName,
                BindingFlags.InvokeMethod | BindingFlags.IgnoreCase | BindingFlags.Public | BindingFlags.Instance,
                null, m_oCOMObject, oParams);

            return (oCOMObject != null) ? new com_holder(oCOMObject) : null;
        }
        /// <summary>put property</summary>
        public void invoke_put_property(String strPropName, params object[] oParams)
        {
            m_oCOMObject.GetType().InvokeMember(strPropName,
                BindingFlags.SetProperty | BindingFlags.IgnoreCase | BindingFlags.Public | BindingFlags.Instance,
                null, m_oCOMObject, oParams);
        }
        public object _raw_object
        {
            get { return m_oCOMObject; }
        }
        #endregion
        #region IDisposable Members
        public void Dispose()
        {
            Dispose(true);

            GC.SuppressFinalize(this);
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }
        public void Dispose(bool bDisposing)
        {
            if (bDisposing)
            {
                if (m_oCOMObject != null)
                {
                    while (Marshal.ReleaseComObject(m_oCOMObject) > 0)
                    {
                    }
                }
            }
            m_oCOMObject = null;
        }
        #endregion
        #region data members
        /// <summary>COM Object </summary>
        private object m_oCOMObject;
        #endregion

        private static string FormatException(Exception ex)
        {
            if (ex == null)
            {
                return "null";
            }

            string strMessage = ex.GetType().FullName + " hresult=0x" + ex.HResult.ToString("X8") + " message=" + ex.Message;
            if (ex.InnerException != null)
            {
                strMessage += " inner=[" + FormatException(ex.InnerException) + "]";
            }
            strMessage += Environment.NewLine + ex.StackTrace;
            return strMessage;
        }

        private void TraceDispatchProbe(string strMethodName)
        {
            IntPtr pUnknown = IntPtr.Zero;
            IntPtr pDispatch = IntPtr.Zero;
            try
            {
                pUnknown = Marshal.GetIUnknownForObject(m_oCOMObject);
                pDispatch = Marshal.GetIDispatchForObject(m_oCOMObject);

                IDispatchRaw oDispatch = m_oCOMObject as IDispatchRaw;
                if (oDispatch == null && pDispatch != IntPtr.Zero)
                {
                    oDispatch = (IDispatchRaw)Marshal.GetTypedObjectForIUnknown(pDispatch, typeof(IDispatchRaw));
                }
                if (oDispatch == null)
                {
                    Trace("dispatch_probe method=" + strMethodName
                        + " iunknown=0x" + pUnknown.ToInt64().ToString("X")
                        + " idispatch=0x" + pDispatch.ToInt64().ToString("X")
                        + " cast_ok=False");
                    return;
                }

                uint iTypeInfoCount;
                int iTypeInfoHr = oDispatch.GetTypeInfoCount(out iTypeInfoCount);
                string[] strNames = new string[] { strMethodName };
                int[] iDispIds = new int[] { -1 };
                Guid oIidNull = Guid.Empty;
                int iGetIdsHr = oDispatch.GetIDsOfNames(ref oIidNull, strNames, 1, 0, iDispIds);

                Trace("dispatch_probe method=" + strMethodName
                    + " iunknown=0x" + pUnknown.ToInt64().ToString("X")
                    + " idispatch=0x" + pDispatch.ToInt64().ToString("X")
                    + " cast_ok=True"
                    + " typeinfo_hr=0x" + iTypeInfoHr.ToString("X8")
                    + " typeinfo_count=" + iTypeInfoCount
                    + " getids_hr=0x" + iGetIdsHr.ToString("X8")
                    + " dispid=" + iDispIds[0]);
            }
            catch (Exception ex)
            {
                Trace("dispatch_probe exception method=" + strMethodName + " " + FormatException(ex));
            }
            finally
            {
                if (pDispatch != IntPtr.Zero)
                {
                    Marshal.Release(pDispatch);
                }
                if (pUnknown != IntPtr.Zero)
                {
                    Marshal.Release(pUnknown);
                }
            }
        }

        private static string FormatParams(object[] oParams)
        {
            if (oParams == null || oParams.Length == 0)
            {
                return "params=[]";
            }

            string strResult = "params=[";
            for (int i = 0; i < oParams.Length; i++)
            {
                object oParam = oParams[i];
                if (i > 0)
                {
                    strResult += "; ";
                }
                strResult += i + ":";
                if (oParam == null)
                {
                    strResult += "null";
                }
                else
                {
                    strResult += oParam.GetType().FullName + "=" + Convert.ToString(oParam);
                }
            }
            return strResult + "]";
        }

        [ComImport]
        [Guid("00020400-0000-0000-C000-000000000046")]
        [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
        private interface IDispatchRaw
        {
            [PreserveSig]
            int GetTypeInfoCount(out uint pctinfo);

            [PreserveSig]
            int GetTypeInfo(uint iTInfo, int lcid, out IntPtr ppTInfo);

            [PreserveSig]
            int GetIDsOfNames(
                ref Guid riid,
                [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPWStr, SizeParamIndex = 2)] string[] rgszNames,
                int cNames,
                int lcid,
                [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] int[] rgDispId);

            [PreserveSig]
            int Invoke(
                int dispIdMember,
                ref Guid riid,
                int lcid,
                ushort wFlags,
                IntPtr pDispParams,
                IntPtr pVarResult,
                IntPtr pExcepInfo,
                IntPtr puArgErr);
        }

        private static void Trace(string message)
        {
            try
            {
                string path = Environment.GetEnvironmentVariable("NAVO_COCOON_DIAG_LOG");
                if (string.IsNullOrWhiteSpace(path))
                {
                    path = @"C:\app\cocoon-diagnostics.log";
                }
                File.AppendAllText(path, DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") + " [com_holder] " + message + Environment.NewLine);
            }
            catch
            {
            }
        }
    }
}
