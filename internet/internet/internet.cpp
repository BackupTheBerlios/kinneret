/***************************************************************************
                          internet.cpp  -  description
                             -------------------
    begin                : Sat Jul 19 2003
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
#include "internet.h"

#include "isp.h"
#include "db.h"
#include "hardware.h"
#include "dialer.h"
#include "authentication.h"
#include "connection.h"

bool FileExists(string file)
{
	ifstream f(file.c_str());
	if (!f) return false;
	return true;	// auto-closes f.
}

void Use(const ConfigFile &conf, const CommandLine &cmd, string strScript, string strCon) throw (Error)
{
	// Verify connection's name
	if (cmd.bVerbose) cout << "making sure connection exists...\n";
	if (cmd.bVerbose && strCon == string("default")) cout << "Using 'default' connection...\n";

	string file = conf.strDBPath + "connections/" + strCon + ".tar.gz";
	if (!FileExists(file)) throw Error("No such connection, use -C to list connections");
	
	if (cmd.bVerbose) cout << "Cleaning and re-creating /tmp/iwiz/...\n";
	if (system("rm -fr /tmp/iwiz/ 2>&1 > /dev/null") != 0) throw ErrorSystem();
	if (system("mkdir -p /tmp/iwiz/ 2>&1 > /dev/null") != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "Extracting script to /tmp/iwiz/...\n";
	string strCmd = "tar -C /tmp/iwiz/ -xzf '" + file + "' ./" + strScript + ".sh";
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "Running script...\n";
	strCmd = "/tmp/iwiz/" + strScript + ".sh";
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	cout << endl;
}

void MakeFromDesc(const Description &desc, const Database &db, const ConfigFile &conf) throw (Error)
{
	try
	{
		ISP isp(&db);
		isp.LoadISP(desc.strISP);

		Hardware *modem = 0;
		string strModemFile = db.getModemByName(desc.strModem, Broadband);

		Hardware::MinorType minor = getHardwareType(strModemFile, Broadband, &db);
		if (minor == Hardware::Unknown)
			throw Error("Unknown modem type");

		switch (minor)
		{
		case Hardware::BBEth:
			modem = new Ethernet(&db);
			break;

		case Hardware::BBUSB:
			modem = new USB(&db);
			break;

		case Hardware::BBDual:
			if (desc.interInterface == interEthernet)	modem = new Ethernet(&db);
			else if (desc.interInterface == interUSB)	modem = new USB(&db);
			break;

		default:
			throw Error("Unknown modem type");
			break;
		}

		modem->Load(strModemFile);
		
		if (desc.conMethod == ADSL || desc.conMethod == Cable)
		{
			Ethernet *eth;
			if (!(eth = dynamic_cast<Ethernet*>(modem)))
				throw Error("Cast error, programmer's fault, please report a bug...");
				// ugly, ugly, ugly, ugly... I know...
				// If you have any better idea, mail me...
				
			// modem => interface
			eth->setEth(desc.strEth);
		}

		string username(desc.strUsername), passwd(desc.strPasswd);

		// append suffix
		if (desc.conMethod == ADSL && !isp.getADSLSuffix().empty())
			username += string("@[*isp::adsl::usrsuffix*]");

		else if (desc.conMethod == Cable && !isp.getCableSuffix().empty())
			username += string("@[*isp::cable::usrsuffix*]");

		// A really stupid class, I know... but it's here for the future
		// (what if next year your ISP will require a finger print? :)
		Authentication auth(username, passwd);

		Dialer dial(&db);
		dial.LoadDialer(db.ResolveDialer(&isp, modem, Broadband));
		dial.setDebian(desc.bDebianBased);

		Connection con(modem, &isp, &auth, &dial);
		con.setName(desc.strConnectionName);
		if (FileExists(conf.strDBPath + "connections/" + desc.strConnectionName + ".tar.gz"))
			throw Error("Connection's name must be unique");

		con.Make();
		con.Install();

		if (!FileExists(conf.strDBPath + "connections/default.tar.gz"))
		{
			string strCmd = "rm -f '" + conf.strDBPath + "connections/default.tar.gz'";
			if (system(strCmd.c_str()) != 0) throw ErrorSystem();

			strCmd = "ln -s '" + conf.strDBPath + "connections/" + con.getName() + ".tar.gz' " + conf.strDBPath + "connections/default.tar.gz";
			if (system(strCmd.c_str()) != 0) throw ErrorSystem();
		}
		
		delete modem;
	}

	catch (bad_alloc)
	{
		throw ErrorOverflow();
	}

	catch (...)
	{
		throw;
	}
}
