//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using ADODB;
using navo2012.proxy;
using nxm.biz.data.store;
using nxm.biz.store;
using nxm.core;
using nxm.core.data.ps;
using nxm.core.os;
using nxm.core.services;
using nxm.core.types;
using nxm.erp.navo_eurobusiness.ps;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;

namespace navo.cocoon.store
{
    [ComVisible(true)]
    public class store_transaction : IObjectServerExtension, IDisposable
    {
        public void Init(IObjectServerExtensionHost pHost)
        {
            using (new com_holder(pHost))
            {
                store_manager_hub oServerGlobalStoreManagerHub = null;

                Connection oConnection = null;

                {
                    object _oServerDBConnection = null;
                    pHost.GetDBConnection(out _oServerDBConnection);

                    oConnection = (Connection)_oServerDBConnection;

                }
                {
                    object _oServerGlobalStoreHub = null;
                    pHost.GetStoreHub(out _oServerGlobalStoreHub);

                    oServerGlobalStoreManagerHub = (store_manager_hub)_oServerGlobalStoreHub;
                }

                string strSQLServer = "";
                string strDataBase = "";

                for (int iIter = 0; iIter < oConnection.Properties.Count; iIter++)
                {
                    Property oProperty = oConnection.Properties[iIter];
                    string strPropName = oProperty.Name;
                    object oPropValue = oProperty.Value;

                    Debug.WriteLine($"{strPropName}={oPropValue}");

                    if ("Server Name" == strPropName)
                    {
                        strSQLServer = oProperty.Value.ToString();
                    }
                    if ("Current Catalog" == strPropName)
                    {
                        strDataBase = oProperty.Value.ToString();
                    }
                }
                service_connection_param oParams = new service_connection_param();
                oParams.parameters = new _variant_set_("server_path", strSQLServer, "database_name", strDataBase);

                m_oStorageOperations = new navo_eurobusiness_erp_store_ps_operations(oParams, oConnection);

                m_oStoreManager = oServerGlobalStoreManagerHub.get_instance_for_database(strSQLServer, strDataBase);

                oConnection.CommitTransComplete += _on_sql_transaction_commit;
                oConnection.RollbackTransComplete += _on_sql_transaction_rollback;
            }
        }
        #region client API
        /// <summary>perform global initialization. makes nothing when already initialized</summary>
        [FixedName]
        public string initialize(int iFixedAreaLastSeqNo, int iMode, bool bFlush)
        {
            _store_error_info_ oErrorInfo = m_oStoreManager.initialize(m_oStorageOperations, (uint)iFixedAreaLastSeqNo, (store_manager.eInitializeMode)iMode, bFlush);

            return oErrorInfo == null ? "" : oErrorInfo.ToString();
        }
        /// <summary>apply document (must be already strored in n5gmop/n5realprod database</summary>
        [FixedName]
        public string apply_document(int iSeqNo, bool bForDelete, bool bIsStoreDoc, bool bFlush)
        {
            if (!m_bHasStoreManagerLock)
            {
                int iRetryCount = 5;

                while (iRetryCount-- > 0)
                {
                    m_bHasStoreManagerLock = m_oStoreManager.try_begin_store_transaction();

                    if (m_bHasStoreManagerLock)
                    {
                        Debug.Assert(m_oUndoInfo == null);

                        m_oUndoInfo = new disposable_holder();

                        break;
                    }
                    else
                    {
                        Thread.Sleep(1000);
                    }
                }
            }

            if (!m_bHasStoreManagerLock)
            {
                return new _store_error_info_()
                {
                    Type = _store_error_info_.eType.system_busy
                }.ToString();
            }

            Debug.Assert(m_oUndoInfo != null);

            apply_doc_params oParams = new apply_doc_params
            {
                SeqNo = (uint)iSeqNo,
                isStoreDoc = bIsStoreDoc,
                ForDelete = bForDelete
            };

            _store_error_info_ oErrorInfo = m_oStoreManager.process_request(m_oStorageOperations, oParams.as_enumerable(), bFlush, m_oUndoInfo);

            return oErrorInfo == null ? "" : oErrorInfo.ToString();
        }
        /// <summary>update runtime states and flush splits and current stock to DB</summary>
        [FixedName]
        public string flush()
        {
            _store_error_info_ oErrorInfo = m_oStoreManager.process_request(m_oStorageOperations, null, true, null);

            return oErrorInfo == null ? "" : oErrorInfo.ToString();
        }

        /// <summary>return current stock for specified product/subproduct and specified store (0 = all stores)</summary>
        [FixedName]
        public decimal get_stock(int iSeqNo, int iProductID, int iProductSubID, int iStoreID)
        {
            return m_oStoreManager.get_stock((uint)iSeqNo, (uint)iProductID, (uint)iProductSubID, (uint)iStoreID);
        }
        #endregion
        #region implementation
        private void _on_sql_transaction_rollback(Error pError, ref EventStatusEnum adStatus, Connection pConnection)
        {
            if (m_bHasStoreManagerLock)
            {
                _store_transaction_rollback();
            }

            Debug.Assert(!m_bHasStoreManagerLock);
        }

        private void _on_sql_transaction_commit(Error pError, ref EventStatusEnum adStatus, Connection pConnection)
        {
            if (m_bHasStoreManagerLock)
            {
                _store_transaction_commit();
            }

            Debug.Assert(!m_bHasStoreManagerLock);
        }

        private void _store_transaction_rollback()
        {
            m_oUndoInfo?.Dispose();
            m_oUndoInfo = null;

            m_bHasStoreManagerLock = false;
            m_oStoreManager.end_store_transaction();
        }
        private void _store_transaction_commit()
        {
            m_oUndoInfo?.dont_care_anything();
            _store_transaction_rollback();
        }
        #endregion
        #region IDisposable Support
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                _store_transaction_rollback();
            }
        }
        public void Dispose()
        {
            Dispose(true);
        }
        #endregion
        #region data members
        private navo_eurobusiness_erp_store_ps_operations m_oStorageOperations;
        private store_manager m_oStoreManager;
        private disposable_holder m_oUndoInfo;
        private bool m_bHasStoreManagerLock;
        #endregion
    }
}