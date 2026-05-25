//--------------------------------------------------------------------------
// NAMAMAS project
// Copyright NAVO Sp. z o.o. All Rights reserved
//
// namamas.common
// result - method execution result (result code and data)
// 
// created: 2011-08-16/../2012-07-13
//--------------------------------------------------------------------------

using System;

namespace n8.core
{
    /// <summary>method execution result (result code)</summary>
    [Serializable]
    public class result
    {
        #region constructor
        /// <summary>universal constructor</summary>
        /// 
        protected result()
        {
            m_strErrorCode = "";
            m_strErrorParams = null;
        }
        protected result(string strErrorCode, params string[] strErrorParams)
        {
            m_strErrorCode = strErrorCode;
            m_strErrorParams = strErrorParams;
        }
        #endregion
        #region operations
        /// <summary>return OK result</summary>
        public static result OK()
        {
            return new result("");
        }
        /// <summary>return ERROR result</summary>
        public static result ERROR(string strErrorCode, params string[] strErrorParams)
        {
            return new result(strErrorCode, strErrorParams);
        }
        #endregion
        #region properties
        /// <summary>boolean operator</summary>
        public static implicit operator bool(result oResult)
        {
            return oResult.m_strErrorCode == "";
        }
        /// <summary>returns error code</summary>
        public string error_code
        {
            get { return m_strErrorCode; }
        }
        /// <summary>returns error parameters</summary>
        public string[] error_params
        {
            get { return m_strErrorParams; }
        }
        #endregion
        #region data members
        /// <summary>result/error code</summary>
        protected string m_strErrorCode;
        /// <summary>error parameters</summary>
        protected string[] m_strErrorParams;
        #endregion
    }

    /// <summary>method execution result (result code and data)</summary>
    [Serializable]
    public class result<TResult> : result
    {
        #region constructor
        /// <summary>universal constructor</summary>
        protected result(TResult oResult, string strErrorCode, params string[] strErrorParams)
            : base(strErrorCode, strErrorParams)
        {
            m_oResult = oResult;
        }
        #endregion
        #region operations
        /// <summary>return OK result</summary>
        public static result<TResult> OK(TResult oResult)
        {
            return new result<TResult>(oResult, "");
        }
        /// <summary>return ERROR result</summary>
        public static new result<TResult> ERROR(string strErrorCode, params string[] strErrorParams)
        {
            return new result<TResult>(default(TResult), strErrorCode, strErrorParams);
        }
        /// <summary>return casted ERROR result</summary>
        public static result<TResult> CAST_ERROR(result oResult)
        {
            return new result<TResult>(default(TResult), oResult.error_code, oResult.error_params);
        }
        /// <summary>returns casted result</summary>
        public static result<TResult> CAST(result oResult, TResult oResultVal)
        {
            return new result<TResult>(oResultVal, oResult.error_code, oResult.error_params);
        }
        #endregion
        #region properties
        /// <summary>result</summary>
        public TResult result_
        {
            get
            {
                return m_oResult;
            }
        }
        #endregion
        #region data members
        /// <summary>result data</summary>
        protected TResult m_oResult;
        #endregion
    }

    /// <summary>Extension on Exception</summary>
    public static class Exception_extension
    {
        public static string message(this Exception oException)
        {
            return oException.Message +
                ((oException.InnerException != null) ? ":" + oException.InnerException.Message : "");
        }
    }
}