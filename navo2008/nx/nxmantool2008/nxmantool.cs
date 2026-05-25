using System;
using System.Reflection;
using System.Runtime.InteropServices;

namespace nxmantool
{
	/// <summary>
	/// NX Management Tool
	/// </summary>
	class cnxmantool
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static int Main(string[] args)
		{
			int nResult = -2;
			if(args.Length == 0)
			{
				display_usage();
			}
			else
			{
				string strCmd = args[0];
				switch(strCmd.ToLower())
				{
					case "-regasm":
					{
						if(args.Length < 2)
						{
							display_usage();
						}
						else
						{
							if(regasm(args[1]))
							{
								Console.WriteLine("Assembly " + args[1] + " registered succesfully");
								nResult = 0;
							}
							else
							{
								Console.WriteLine("Failed register " + args[1] + " assembly");
								nResult = -1;
							}
						}
					}
						break;
					default:
					{
						display_usage();
					}
						break;
				}
			}
			return nResult;
		}

		static void display_usage()
		{
			Console.WriteLine(
				@"NXMANTOOL 1.0
Copyright (C) NAVO 2004-2005

Usage:
-regasm   assembly_full_path
-unregasm assembly_full_path");
		}

		static bool regasm(string strAssemblyFilePath)
		{
			Assembly oAssembly = Assembly.LoadFrom(strAssemblyFilePath);
			RegistrationServices oRS = new RegistrationServices();
			return oRS.RegisterAssembly(oAssembly,AssemblyRegistrationFlags.SetCodeBase);
		}

		static bool unregasm(string strAssemblyFilePath)
		{
			Assembly oAssembly = Assembly.LoadFrom(strAssemblyFilePath);
			RegistrationServices oRS = new RegistrationServices();
			return oRS.UnregisterAssembly(oAssembly);
		}

	}
}
