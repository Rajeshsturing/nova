//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using Newtonsoft.Json;
using System.Web.Http;

namespace navo.cocoon.webapi
{
    /// <summary>api/login</summary>
    public class login_controller : ApiController
    {
        [Route("api/v4/login")]
        public login_result Login()
        {
            api_controller_plus oController = new api_controller_plus(this);

            string strJSON = Request.Content.ReadAsStringAsync().Result;
            login_request oLogin = JsonConvert.DeserializeObject<login_request>(strJSON);

            login_result oResult = eb_client_manager.manager.create_token_for_login(oLogin);

            return oResult;
        }

        [Route("api/v4/logoff")]
        public string Logoff()
        {
            api_controller_plus oController = new api_controller_plus(this);

            return eb_client_manager.manager.release_token(oController.get_ncct()) ? null : api_controller_plus.ERROR_MISSING_INVALID_NCCT;
        }
    }
}
