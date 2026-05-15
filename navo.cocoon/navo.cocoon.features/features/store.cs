//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data.utils;
using navo.cocoon.ebwrap;

namespace navo.cocoon.features
{
    public partial class hub
    {
        [FixedName]
        public string store_apply_document(object oEBTransaction, int iSeqNo, bool bForDelete, bool bIsStoreDoc, bool bFlush)
        {
            using (ne_trans oTransaction = new ne_trans(oEBTransaction, ne_object_factory.wrap, ne_object_list_factory.wrap))
            {
                string strError = _ensure_extension(oTransaction);

                if (strError != "")
                {
                    return strError;
                }

                strError = _store_transaction_extension.invoke_method_plain<string>("apply_document", iSeqNo, bForDelete, bIsStoreDoc, bFlush);

                return strError;
            }
        }

        [FixedName]
        public string store_flush(object oEBTransaction)
        {
            using (ne_trans oTransaction = new ne_trans(oEBTransaction, ne_object_factory.wrap, ne_object_list_factory.wrap))
            {
                string strError = _ensure_extension(oTransaction);

                if (strError != "")
                {
                    return strError;
                }

                strError = _store_transaction_extension.invoke_method_plain<string>("flush");

                return strError;
            }
        }

        private string _ensure_extension(ne_trans oTransaction)
        {
            if (m_oStoreTransactionExtensionHolder == null)
            {
                m_oStoreTransactionExtensionHolder = new com_holder(oTransaction.createserverextension(SERVER_EXTENSION_PROGID));

                string strError = m_oStoreTransactionExtensionHolder.invoke_method_plain<string>("initialize", 0, 0 /*=navo.cocoon.store.store_manager.eInitializeMode.default_*/, false);
                if (strError != "")
                {
                    return strError;
                }
            }

            return "";
        }
        private com_holder _store_transaction_extension
        {
            get { return m_oStoreTransactionExtensionHolder; }
        }

        private const string SERVER_EXTENSION_PROGID = "navo.cocoon.store.store_transaction";

        private com_holder m_oStoreTransactionExtensionHolder;
    }
}