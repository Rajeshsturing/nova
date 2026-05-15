//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using System.Web.Http;

namespace navo.cocoon.webapi.Controllers
{
    [RoutePrefix("api/v4/health")]
    public class health_controller : ApiController
    {
        [Route("{item}")]
        public string Get(string item)
        {
            switch (item)
            {
                case "ws":
                case "full_name":
                    return $"{version_info.PRODUCT_NAME} {version_info.PRODUCT_VERSION}";
                case "version":
                    return version_info.PRODUCT_VERSION;
                default:
                    return "???";
            }
        }
    }
}
