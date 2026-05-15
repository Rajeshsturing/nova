//--------------------------------------------------------------------------
// 
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016-2017
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.ebwrap;
using navo.cocoon.features;
using System.Web.Http;

namespace navo.cocoon.webapi
{
    [RoutePrefix("api/v4/customer")]
    public class customer_controller : ApiController
    {
        [Route("get/{id:int}")]
        public customer Get(int id)
        {
            api_controller_plus oController = new api_controller_plus(this);

            using (eb_client_access oAccess = eb_client_manager.manager.get_client_access_for_token(oController.get_ncct()))
            {
                if (oAccess == null)
                {
                    return null;
                }

                using (ne_trans oTransaction = oAccess.create_transaction())
                {
                    return oTransaction.read_customer(id);
                }
            }
        }
    }
}