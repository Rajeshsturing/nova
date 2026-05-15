//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.ebwrap;
using navo.cocoon.features;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;
using System.Net.Http;
using System.Web.Http;

namespace navo.cocoon.webapi
{
    [RoutePrefix("api/v4/document")]
    public class document_controller : ApiController
    {
        [Route("get/{type}/{id:int}")]
        public logi_document Get(string type, int id)
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
                    return oTransaction.read_logi_document(oAccess, type, id, true);
                }
            }
        }

        [Route("doaction")]
        public logi_document Action(string action, string parameters = null)
        {
            api_controller_plus oController = new api_controller_plus(this);
            string strJSON = Request.Content.ReadAsStringAsync().Result;
            logi_document oDocument = JsonConvert.DeserializeObject<logi_document>(strJSON);

            JObject oParams = parameters._is_void_() ? null : JObject.Parse(parameters);

            using (eb_client_access oClientAccess = eb_client_manager.manager.get_client_access_for_token(oController.get_ncct()))
            {
                if (oClientAccess == null)
                {
                    oDocument._error_code = "999";
                    oDocument._error_message = api_controller_plus.ERROR_MISSING_INVALID_NCCT;

                    return oDocument;
                }

                using (ne_trans oTransaction = oClientAccess.create_transaction())
                {
                    logi_document oResult = logi_document_operations.save_logi_document(oClientAccess, oDocument, action, oParams);

                    return oResult;
                }
            }
        }

        [Route("printout/{type}/{id:int}/{pubtype:int?}")]
        public HttpResponseMessage GetPrintOut(string type, int id, int pubtype = 0)
        {
            api_controller_plus oController = new api_controller_plus(this);
            using (eb_client_access oClientAccess = eb_client_manager.manager.get_client_access_for_token(oController.get_ncct()))
            {
                if (oClientAccess == null)
                {
                    return new HttpResponseMessage()
                    {
                        Content = new StringContent(api_controller_plus.ERROR_MISSING_INVALID_NCCT)
                    };

                }

                string strPrivatePath = logi_document_util.create_publication_as_pdf(oClientAccess, type, id, pubtype);

                if (strPrivatePath.StartsWith(":"))
                {
                    return new HttpResponseMessage()
                    {
                        Content = new StringContent(strPrivatePath)
                    };
                }
                HttpResponseMessage oResponse =
                    new HttpResponseMessage()
                    {
                        Content = new StreamContent(new FileStream(strPrivatePath, FileMode.Open, FileAccess.Read))
                    };

                ////create and set cookie in response
                //CookieHeaderValue oCookie = new CookieHeaderValue("fileDownload", "true");
                //oCookie.Expires = DateTimeOffset.Now.AddSeconds(60);
                //oCookie.Domain = Request.RequestUri.Host;
                //oCookie.Path = "/";
                //oResponse.Headers.AddCookies(oCookie.as_enumerable());

                return oResponse;
            }
        }
    }
}