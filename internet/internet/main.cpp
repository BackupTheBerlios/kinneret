/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Jun  7 14:04:08 IDT 2003
    copyright            : (C) 2003 by Itay 'z9u2K' Duvdevani
    email                : z9u2k@linux-kinneret.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "internet.h"

#include "db.h"
#include "isp.h"
#include "hardware.h"
#include "authentication.h"
#include "dialer.h"
#include "connection.h"
#include "parse.h"

#include "wizard.h"

int main(int argc, char *argv[])
{
	ConfigFile Conf;
	CommandLine CmdLine;
	
	try
	{
		// Load config file, database path
		Conf.LoadConfig();

		// Parse command line
		CmdLine.Parse(argc, argv);

		// Wizard
		if (CmdLine.bWizard)			return DoWizard(Conf, CmdLine);

		// Create database
		Database db(Conf.strDBPath);

		// Information
		if (CmdLine.bListISPs)			InfoListISPs(db);
		if (CmdLine.bListConnections)	InfoListConnections(Conf);
		if (CmdLine.bShowDefault)		InfoShowDefault(Conf);
		if (CmdLine.clISPInfo.bIs)		InfoISP(db, CmdLine.clISPInfo.strOpt);
		if (CmdLine.clHWInfo.bIs)		InfoHW(db, CmdLine.clHWInfo.strOpt);
		if (CmdLine.clListHWs.bIs)		InfoListHWs(db, CmdLine.clListHWs.strOpt);

		// Manage
		if (CmdLine.clDelete.bIs)		ManageDelete(Conf, CmdLine, CmdLine.clDelete.strOpt);
		if (CmdLine.clSetDefault.bIs)	ManageSetDefault(Conf, CmdLine, CmdLine.clSetDefault.strOpt);
		if (CmdLine.clExtract.bIs)		ManageExtract(Conf, CmdLine, argc, argv, CmdLine.clExtract.strOpt);

		// Use
		if (CmdLine.clInit.bIs)			Use(Conf, CmdLine, "init", CmdLine.clInit.strOpt);
		if (CmdLine.clBoot.bIs)			Use(Conf, CmdLine, "boot", CmdLine.clBoot.strOpt);
		if (CmdLine.clConnect.bIs)		Use(Conf, CmdLine, "connect", CmdLine.clConnect.strOpt);
		if (CmdLine.clKill.bIs)			Use(Conf, CmdLine, "disconnect", CmdLine.clKill.strOpt);

		// Instate of nesting an if statement, I'll simply return
		// from the main function.
		if (!CmdLine.bCreateMode) return 0;

		// Create
		////////////////////////////////////////////////////////////////
		// A R-E-A-L-Y BIG TODO:                                      //
		// Consider people that are connected using dialup or ISDN... //
		////////////////////////////////////////////////////////////////
		Description desc;

		// Parse method first, so we'll know hot to act.
		if (CmdLine.clMethod.strOpt == "adsl" || CmdLine.clMethod.strOpt == "cable")
		{
			// Broadband

			// Debian
			if (CmdLine.clDebian.strOpt == "yes") desc.bDebianBased = true;
			else if (CmdLine.clDebian.strOpt == "no") desc.bDebianBased = false;

			if (CmdLine.bVerbose)
			{
				cout << "Will build scripts for ";
				if (desc.bDebianBased == false) cout << "non-";
			
				cout << "Debian based systems\n";
			}

			// ISP
			desc.strISP = CmdLine.clISP.strOpt;
			db.getISPPath(desc.strISP);		// will throw an exception of ISP is invalid

			// Connection method
			if (CmdLine.clMethod.strOpt == "adsl") desc.conMethod = ADSL;
			else if (CmdLine.clMethod.strOpt == "cable") desc.conMethod = Cable;

			// Modem
			desc.strModem = CmdLine.clModem.strOpt;
			db.getModemByName(CmdLine.clModem.strOpt, Broadband);	// again, for the exception
			if (CmdLine.bVerbose)
				cout << "Modem's file is: " << db.getModemByName(CmdLine.clModem.strOpt, Broadband) << endl;

			// Dual (?)
			string strModemFile = db.getModemByName(CmdLine.clModem.strOpt, Broadband);
			Hardware::MinorType minor = getHardwareType(strModemFile, Broadband, &db);
			if (minor == Hardware::Unknown) throw Error("Invalid modem");
			if (minor == Hardware::BBDual)
			{
				if (CmdLine.clIFace.strOpt.empty())
					throw Error("This is a dual modem, please specify the --iface flag.");

				if (CmdLine.bVerbose) cout << "The modem has two interfaces." << endl;

				if (CmdLine.clIFace.strOpt == "eth")
				{
					if (CmdLine.bVerbose) 
						cout << "The modem is connected using an ethernet card." << endl;
					desc.interInterface = interEthernet;
				}
				
				else if (CmdLine.clIFace.strOpt == "usb")
				{
					if (CmdLine.bVerbose)
						cout << "The modem is connected using the USB port." << endl;
					desc.interInterface = interUSB;
				}
			}

			// Eth
			desc.strEth = CmdLine.clDevice.strOpt;
			if ((desc.strEth.length() != 4) ||(desc.strEth[0] != 'e') || (desc.strEth[1] != 't') ||
					(desc.strEth[2] != 'h') || (!isdigit(desc.strEth[3])))
						throw Error("--dev must be of the form: ethn!");

			// Username
			desc.strUsername = CmdLine.clUsername.strOpt;

			// Server
			desc.strServer = CmdLine.clServer.strOpt;

			// Password
			desc.strPasswd = CmdLine.clPasswd.strOpt;

			// Connection name
			if (FileExists(Conf.strDBPath + "connections/" + CmdLine.clName.strOpt + ".tar.gz"))
				throw Error("Connection name must be unique");

			desc.strConnectionName = CmdLine.clName.strOpt;
		
			MakeFromDesc(desc, db, Conf, CmdLine);
		}

		if (CmdLine.clMethod.strOpt == "lan")
		{
			desc.conMethod = LANSlave;
			
			// Debian
			if (CmdLine.clDebian.strOpt == "yes") desc.bDebianBased = true;
			else if (CmdLine.clDebian.strOpt == "no") desc.bDebianBased = false;

			if (CmdLine.bVerbose)
			{
				cout << "Will build scripts for ";
				if (desc.bDebianBased == false) cout << "non-";

				cout << "Debian based systems\n";
			}

			// ISP
			desc.strISP = CmdLine.clISP.strOpt;
			db.getISPPath(desc.strISP);		// will throw an exception of ISP is invalid

			// Eth
			desc.strEth = CmdLine.clDevice.strOpt;
			if ((desc.strEth.length() != 4) ||(desc.strEth[0] != 'e') || (desc.strEth[1] != 't') ||
					(desc.strEth[2] != 'h') || (!isdigit(desc.strEth[3])))
						throw Error("--dev must be of the form: ethn!");

			// LAN
			if (CmdLine.clLANIP.strOpt == string("dhcp"))
			{
				desc.strLANIP = string("");
				desc.bLANDHCP = true;
			}

			else
			{
				desc.strLANIP = CmdLine.clLANIP.strOpt;
				desc.bLANDHCP = false;
			}
			
			desc.strLANMask = 		CmdLine.clLANMask.strOpt;
			desc.strLANBroadcast =	CmdLine.clLANBroadcast.strOpt;
			desc.strLANGateway =	CmdLine.clLANGateway.strOpt;

			// Connection name
			if (FileExists(Conf.strDBPath + "connections/" + CmdLine.clName.strOpt + ".tar.gz"))
				throw Error("Connection name must be unique");

			desc.strConnectionName = CmdLine.clName.strOpt;

			MakeFromDesc(desc, db, Conf, CmdLine);
		}

		if (CmdLine.clMethod.strOpt == "dialup")
		{
			desc.conMethod = Analog;

			// Debian
			if (CmdLine.clDebian.strOpt == "yes") desc.bDebianBased = true;
			else if (CmdLine.clDebian.strOpt == "no") desc.bDebianBased = false;

			if (CmdLine.bVerbose)
			{
				cout << "Will build scripts for ";
				if (desc.bDebianBased == false) cout << "non-";

				cout << "Debian based systems\n";
			}

			// ATDT
			string phonecode = CmdLine.clPhoneNumber.strOpt.substr(0, 2);
			if (CmdLine.clMyArea.strOpt == phonecode)
				desc.strATDT = CmdLine.clPhoneNumber.strOpt.substr(3, 7);
			else desc.strATDT = phonecode + CmdLine.clPhoneNumber.strOpt.substr(3, 7);

			// Username
			desc.strUsername = CmdLine.clUsername.strOpt;

			// Server
			desc.strServer = CmdLine.clServer.strOpt;

			// Password
			desc.strPasswd = CmdLine.clPasswd.strOpt;

			if (CmdLine.bVerbose) cout << "ATDT: " << desc.strATDT << endl;
			
			// Connection name
			if (FileExists(Conf.strDBPath + "connections/" + CmdLine.clName.strOpt + ".tar.gz"))
				throw Error("Connection name must be unique");

			desc.strConnectionName = CmdLine.clName.strOpt;
			MakeFromDesc(desc, db, Conf, CmdLine);
		}
	}

	catch (Error &error)
	{
		if (!CmdLine.bQuite) cerr << error.Msg();
		cout << endl;
		
		return -1;
	}

	catch (...)
	{
		if (!CmdLine.bQuite) cerr << "ERROR: Unknown error";
		cout << endl;
		
		return -1;
	}

	cout << endl;
	return 0;
}



