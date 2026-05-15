//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using System;
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
        }
        /// <summary>invokes method on owned object
        /// returns plain type</summary>
        public TType invoke_method_plain<TType>(String strMethodName, params object[] oParams)
        {
            return (TType)m_oCOMObject.GetType().InvokeMember(strMethodName, BindingFlags.InvokeMethod, null, m_oCOMObject, oParams);
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
    }
}