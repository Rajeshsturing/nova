//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using Newtonsoft.Json;
using System;
using System.IO;
using System.Web.Http;

namespace navo.cocoon.webapi
{
    /// <summary>api/login</summary>
    public class login_controller : ApiController
    {
        [Route("api/v4/login")]
        public login_result Login()
        {
            Trace("login request begin");
            try
            {
                api_controller_plus oController = new api_controller_plus(this);

                string strJSON = Request.Content.ReadAsStringAsync().Result;
                Trace("login json read length=" + (strJSON == null ? "null" : strJSON.Length.ToString()));
                login_request oLogin = JsonConvert.DeserializeObject<login_request>(strJSON);
                Trace("login parsed app=" + oLogin?.application_name + " db=" + oLogin?.database + " server=" + oLogin?.eb_server + " account=" + oLogin?.account_id + " mode=" + oLogin?.mode + " ui=" + oLogin?.ui_style);

                login_result oResult = eb_client_manager.manager.create_token_for_login(oLogin);
                Trace("login result category=" + oResult?.user_category + " user=" + oResult?.user_name + " token_empty=" + string.IsNullOrWhiteSpace(oResult?.token));

                return oResult;
            }
            catch (Exception ex)
            {
                Trace("login exception " + ex);
                throw;
            }
        }

        [Route("api/v4/logoff")]
        public string Logoff()
        {
            api_controller_plus oController = new api_controller_plus(this);

            return eb_client_manager.manager.release_token(oController.get_ncct()) ? null : api_controller_plus.ERROR_MISSING_INVALID_NCCT;
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
                File.AppendAllText(path, DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") + " [login_controller] " + message + Environment.NewLine);
            }
            catch
            {
            }
        }
    }
}
