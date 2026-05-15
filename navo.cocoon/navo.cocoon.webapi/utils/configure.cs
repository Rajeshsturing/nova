using System.Web.Http;

namespace navo.cocoon.webapi
{
    public static class WebApiConfig
    {
        public static void Register(HttpConfiguration oConfig)
        {
            oConfig.MapHttpAttributeRoutes();
        }
    }
}