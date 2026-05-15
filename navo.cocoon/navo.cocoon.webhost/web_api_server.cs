using Microsoft.Owin.Cors;
using Microsoft.Owin.Hosting;
using Owin;
using System;
using System.Web.Http;

namespace navo.cocoon.webhost
{
    public static class web_api_server
    {
        public static IDisposable start(string strListeningURL)
        {
            //netsh http add urlacl url=http://*:6000/ user=Everyone
            return WebApp.Start(strListeningURL, app_bldr_ => new _startup().Configuration(app_bldr_));
        }
    }

    /// <summary>required startup class</summary>
    public class _startup
    {
        public void Configuration(IAppBuilder app)
        {
            app.UseCors(CorsOptions.AllowAll);

            // Configure Web API for self-host. 
            HttpConfiguration oConfig = new HttpConfiguration();
            
            global::navo.cocoon.webapi.WebApiConfig.Register(oConfig);
            
            // Web API routes
            //oConfig.MapHttpAttributeRoutes();

            oConfig.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}",
                defaults: new { id = RouteParameter.Optional }
            );

            app.UseWebApi(oConfig);

        }
    }
}
