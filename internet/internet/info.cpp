/***************************************************************************
                          info.cpp  -  description
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

#include "db.h"
#include "isp.h"
#include "hardware.h"

void InfoListISPs(const Database &db) throw (Error)
{
	// List all of the registered ISPs, and their C names (so that the poor user could know
	// what to put in the disgusting command line).
	vector<string> vISPs;
	vector<string> vISPsC;

	// We'll need two lists, for regular names and for C names.
	try
	{
		vISPs = db.ListISPs(true);
		vISPsC = db.ListISPs(false);
	}

	catch (Error &error)
	{
		throw error;
	}

	// And an iterator for each list
	vector<string>::iterator iterLong;
	vector<string>::iterator iterC;

	cout << "Listing ISPs:" << endl;

	// a very trivial three-lined for-loop :P
	for (iterLong = vISPs.begin(), iterC = vISPsC.begin() ;
		 iterLong != vISPs.end() && iterC != vISPsC.end() ;
		 iterLong++, iterC++) cout << *iterLong << " - " << *iterC << endl;
}

void InfoListConnections(const ConfigFile &Conf)
{
	// Simply LS and remove extension
	cout << "Listing Connections:" << endl;
	string cmd = "ls '" + Conf.strDBPath + "connections/'*.tar.gz | rev | cut -b 8- | rev | cut -b ";
	char len[0xFF];
	sprintf(len, "%d-", Conf.strDBPath.length() + 13);
	cmd += len;

	if (system(cmd.c_str()) != 0) throw ErrorSystem();
}

void InfoISP(const Database &db, string strISP) throw (Error)
{
	ISP isp(&db);

	try
	{
		isp.LoadISP(strISP);
	}

	catch (Error &error)
	{
		throw error;
	}

	cout << "Name: "						<< isp.getName()			<< endl;
	cout << "C Name: "						<< isp.getCName()			<< endl;
	cout << "Primary DNS: "					<< isp.getDNS1()			<< endl;
	cout << "Secondary DNS: "				<< isp.getDNS2()			<< endl;
	cout << "Homepage: "					<< isp.getHomepage()		<< endl;
	cout << "Tech-support: "				<< isp.getTech()			<< endl;
	cout << "Costumer Center: "				<< isp.getJoin()			<< endl;
	cout << "Manual Proxy Server: "			<< isp.getProxyManual()		<< endl;
	cout << "Auto Proxy Server: "			<< isp.getProxyAuto()		<< endl;
	cout << "POP3 Server: "					<< isp.getPOP3()			<< endl;
	cout << "IMAP Server: "					<< isp.getIMAP()			<< endl;
	cout << "SMTP Server: "					<< isp.getSMTP()			<< endl;
	cout << "E-Mail Suffix: @"				<< isp.getEMailSuffix()		<< endl;
	cout << "Cable Gateway: "				<< isp.getCableGateway()	<< endl;
	cout << "Cable Remote Server Name: "	<< isp.getCableRemotename()	<< endl;
	cout << "ADSL Username Suffix: "		<< isp.getADSLSuffix()		<< endl;
	cout << "Cable Username Suffix: "		<< isp.getCableSuffix()		<< endl;
	cout << "Search Group: "				<< isp.getSG()				<< endl;

	cout << endl;
	
	cout << "ISDN Phones:" << endl;
	map<string, string> m = isp.getISDNMap();
	map<string, string>::iterator iter;
	for (iter = m.begin() ; iter != m.end() ; iter++)
		cout << iter->first << ": " << iter->second << endl;

	cout << endl;

	cout << "Dialup Phones:" << endl;
	m = isp.getDialupMap();
	for (iter = m.begin() ; iter != m.end() ; iter++)
		cout << iter->first << ": " << iter->second << endl;
	
	cout << endl;
}

void InfoHW(const Database &db, string strHW) throw (Error)
{
	try
	{
		string strModemFile;
		strModemFile = db.getModemByName(strHW, Broadband);

		USB usb(&db);
		usb.Load(strModemFile);

		Hardware::MinorType minType = getHardwareType(strModemFile, Broadband, &db);

		cout << "Type: ";
		switch (usb.getModemType())
		{
		case ADSL:
			cout << "ADSL";
			break;

		case Cable:
			cout << "Cable";
			break;

		default:
			break;
		}

		cout << endl;

		cout << "Interface: ";
		switch (minType)
		{
		case Hardware::BBEth:
			cout << "Ethernet" << endl;
			break;

		case Hardware::BBUSB:
			cout << "USB" << endl;
			break;

		case Hardware::BBDual:
			cout << "Dual, USB or Ethernet" << endl;
			break;

		default:
			cout << "Unknown" << endl;
			break;
		}

		// Method
		if (usb.getModemType() == ADSL)
		{
			cout << "VPN: ";
			switch (usb.getVPNType())
			{
			case Ethernet::PPtP:
				cout << "PPtP";
				break;

			case Ethernet::PPPoE:
				cout << "PPPoE";
				break;
			}

			cout << endl;

			// Addresses
			cout << "Address: "				<< usb.getIP()				<< endl;
			cout << "Remotename: "			<< usb.getRemotename()		<< endl;

			// Interface
			if (usb.getVPNType() == Ethernet::PPtP)
			{
				cout << "Interface IP: "		<< usb.getIfaceIP()			<< endl;
				cout << "Interface Mask: "		<< usb.getIfaceMask()		<< endl;
				cout << "Interface Broadcast: "	<< usb.getIfaceBroadcast()	<< endl;
				cout << "Interface Gateway: "	<< usb.getIfaceGateway()	<< endl;
			}
		}

		// Module
		if (minType == Hardware::BBUSB || minType == Hardware::BBDual)
			cout << "Module: " << usb.getDriver() << endl;
	}

	catch (...)
	{
		throw;
	}

	cout << endl;
}

void InfoListHWs(const Database &db, string strType) throw (Error)
{
	HardwareType ht = Broadband;

	// C style strings sucks... you can't switch with them...
	if (strType == "broadband")		ht = Broadband;
	else if (strType == "isdn")		ht = ISDN;
	else if (strType == "dialup")	ht = Dialup;

	vector<string> vHWs;

	try
	{
		vHWs = db.ListHWs(ht);
	}

	catch (...)
	{
		throw;
	}
	
	vector<string>::iterator iter;

	cout << "Listing Hardwares:" << endl;
	for (iter = vHWs.begin() ; iter != vHWs.end() ; iter++)
		cout << *iter << endl;
}

void InfoShowDefault(const ConfigFile &conf) throw (Error)
{
	string file = conf.strDBPath + "connections/default.tar.gz";
	ifstream f(file.c_str(), ios::in);
	if (!f) throw Error("You do not have a default connection");

	f.close();

	string cmd;
	cmd = "ls -l '" + conf.strDBPath + "connections/default.tar.gz' | rev | cut -b 8- > /tmp/.defcon";
	if (system(cmd.c_str()) != 0) throw ErrorSystem();

	f.open("/tmp/.defcon");
	if (!f) throw Error404("/tmp/.defcon");

	char buff[0xff];
	f.getline(buff, 0xff);
	f.close();

	cmd = buff;

	cmd.erase(cmd.find("/"));
	cmd = "echo '" + cmd + "' | rev";

	if (system(cmd.c_str()) != 0) throw ErrorSystem();
}

