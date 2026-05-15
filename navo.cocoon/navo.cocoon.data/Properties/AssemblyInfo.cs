//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016-18
//
// Assembly Infos
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;

using System.Reflection;
using System.Runtime.InteropServices;

[assembly: AssemblyTitle("navo.cocoon.data")]
[assembly: AssemblyDescription("navo.cocoon.data from " + version_info.PRODUCT_NAME)]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany(version_info.PRODUCT_COMPANY)]
[assembly: AssemblyProduct(version_info.PRODUCT_NAME)]
[assembly: AssemblyCopyright(version_info.PRODUCT_COPYRIGHT)]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]
[assembly: AssemblyVersion(version_info.PRODUCT_VERSION)]
[assembly: AssemblyFileVersion(version_info.PRODUCT_VERSION)]

[assembly: ComVisible(false)]


namespace navo.cocoon.data
{
    public class version_info
    {
        public const string PRODUCT_COPYRIGHT = "Copyright NAVO Sp. z o.o. All Rights reserved 1996-2024";
        public const string PRODUCT_NAME = "NAVO.Cocoon for EuroBusiness 5.0";
        public const string PRODUCT_COMPANY = "NAVO Sp. z o.o.";
        public const string PRODUCT_VERSION = "2024.11.23.00";
    }
}