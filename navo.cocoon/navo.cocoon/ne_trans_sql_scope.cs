//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016-2019
// 
// 2019-03-11
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;

using System;

namespace navo.cocoon.data.utils
{
    public class ne_trans_sql_scope : IDisposable
    {
        public ne_trans_sql_scope(ne_trans oTrans, string strBeginSQL, string strEndSQL)
        {
            m_oTrans = oTrans;
            m_strEndSQL = strEndSQL;

            if (!strBeginSQL._is_void_())
            {
                m_oTrans.exec_sql(strBeginSQL);
            }
        }

        #region IDisposable Support

        protected virtual void Dispose(bool disposing)
        {
            if (!m_bDisposedValue)
            {
                if (disposing)
                {
                    if (!m_strEndSQL._is_void_())
                    {
                        m_oTrans.exec_sql(m_strEndSQL);
                    }
                    m_oTrans = null;
                }

                m_bDisposedValue = true;
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }

        #endregion

        private ne_trans m_oTrans;
        private bool m_bDisposedValue = false; // To detect redundant calls
        private string m_strEndSQL;
    }
}