//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;

namespace navo.cocoon.features
{
    public class eb_query_utils
    {
        public static int select_count(eb_client_access oClientAccess, string strSQL)
        {
            using (ne_trans oTransaction = oClientAccess.create_transaction())
            {
                using (ne_recordset oRecordSet = oTransaction.createadors(strSQL))
                {
                    int iCount = (int)oRecordSet.get_field(0);

                    return iCount;
                }
            }
        }

        public static string top_clause(int iToTake)
        {
            return iToTake == 0 ? "" : $" top {iToTake} ";
        }
    }
}