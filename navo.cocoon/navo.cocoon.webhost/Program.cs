using navo.cocoon.data;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Threading;

namespace navo.cocoon.webhost
{
    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<string, string> dictOptions = try_parse_options(args);

            Console.WriteLine($"==================================================================");
            Console.WriteLine($"NAVO Cocoon WebHost version {version_info.PRODUCT_VERSION}");
            Console.WriteLine($"------------------------------------------------------------------");
            Console.WriteLine($"Today is {DateTime.Now.Date.ToShortDateString()}.");

            //normal
            //netsh http add urlacl url=http://*:7901/ user=Everyone

            //secure
            //netsh http add urlacl url=https://*:7903/ user=Everyone
            //netsh http add sslcert ipport=0.0.0.0:7903 certhash=‎b9829d2da13b44222218c42eb02147a464073a7e appid={20170406-a0a0-0b0b-c0c0-d0d0e0e0f0f0} 
            //start MMC with 'Certificates' snap-in and import nxm.system.p12 to 
            //Console root\Certificates (Local Computer)\Personal\Certificates

            string strListeningURL = Environment.GetEnvironmentVariable("NAVO_COCOON_LISTENING_URL");
            if (string.IsNullOrWhiteSpace(strListeningURL))
            {
                strListeningURL = "http://*:7901/";
            }

            if (dictOptions != null)
            {
                if (dictOptions.ContainsKey("listening_url"))
                {
                    strListeningURL = dictOptions["listening_url"];
                }
            }

            Console.WriteLine($"Web API 2 server will listen on {strListeningURL}");
            Console.WriteLine("Detected IP addresses:");

            try
            {
                foreach (NetworkInterface netInterface in NetworkInterface.GetAllNetworkInterfaces())
                {
                    //Console.WriteLine("Name: " + netInterface.Name);
                    //Console.WriteLine("Description: " + netInterface.Description);
                    //Console.WriteLine("Addresses: ");

                    IPInterfaceProperties ipProps = netInterface.GetIPProperties();

                    ipProps.UnicastAddresses
                        .Where(addr_ => addr_.Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                        ._for_each_(addr_ => Console.WriteLine(" " + addr_.Address.ToString()));

                    //Console.WriteLine("MAC:" + netInterface.GetPhysicalAddress().ToString());
                }

                Console.WriteLine("");

                using (IDisposable oServer = web_api_server.start(strListeningURL))
                {
                    Console.WriteLine("Press Ctrl+C to stop.");
                    Console.WriteLine($"==================================================================");

                    if (Environment.GetEnvironmentVariable("NAVO_COCOON_CONTAINER") == "1")
                    {
                        using (ManualResetEventSlim oStopEvent = new ManualResetEventSlim(false))
                        {
                            Console.CancelKeyPress += (sender_, event_) =>
                            {
                                event_.Cancel = true;
                                oStopEvent.Set();
                            };

                            oStopEvent.Wait();
                        }
                    }
                    else
                    {
                        Console.WriteLine("Press any key to stop.");
                        Console.ReadKey();
                    }

                    eb_client_manager.manager.release_all();

                    Console.WriteLine("Done");
                }
            }
            catch (Exception oException)
            {
                Console.WriteLine("Error occured:");

                Console.WriteLine(oException.ToString());

                if (Environment.GetEnvironmentVariable("NAVO_COCOON_CONTAINER") != "1")
                {
                    Console.WriteLine("Press any key to stop.");
                }
                Console.WriteLine($"==================================================================");
                if (Environment.GetEnvironmentVariable("NAVO_COCOON_CONTAINER") != "1")
                {
                    Console.ReadKey();
                }
            }
        }

        public static Dictionary<string, string> try_parse_options(string[] strOptionArray)
        {
            Dictionary<string, string> oDictionary = new Dictionary<string, string>();

            foreach (string strArg in strOptionArray)
            {
                int iInxOfEq = strArg.IndexOf('=');
                if (iInxOfEq <= 0)
                {
                    return null;
                }

                string strName = strArg.Substring(0, iInxOfEq).ToLower();
                string strValue = strArg.Substring(iInxOfEq + 1);

                oDictionary[strName] = strValue;
            }

            return oDictionary;
        }
    }
}
