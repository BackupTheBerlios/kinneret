/***************************************************************************
                          wizard.cpp  -  description
                             -------------------
    begin                : Sat Jul 12 2003
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
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include <unistd.h>
#include <getopt.h>

#include "db.h"
#include "isp.h"
#include "hardware.h"
#include "authentication.h"
#include "dialer.h"
#include "connection.h"
#include "parse.h"

int DoWizard()
{/*
	Database db;
	vector<string> list = db.ListISPs();
	vector<string> internal = db.ListISPs(true);
	vector<string>::iterator iter;
	int j;

	int distro;
	cout << "Distros:\n1) Debian based (Knoppix, Linbrew etc.)\n2) Non-debian\nEnter type of distro you use: ";
	cin >> distro;

	cout << endl << "Listing known ISPs:" << endl;
	for (j = 0, iter = list.begin() ; iter != list.end() ; iter++, j++)
		cout << j + 1 << ") " << list[j] << endl;

	cout << "Enter your ISP number: ";
	cin >> j;

	ISP isp(&db);
	if (isp.LoadISP(internal[j - 1]))
	{
		cerr << "Invalid ISP.\n";
		return -1;
	}

	cout << endl << "Method:\n1) ADSL\n2) Cable\nEnter your method: ";
	cin >> j;

	int method = j;

	cout << endl << isp.getName() << endl;
	cout << "Listing modems:" << endl;
	list = db.ListHWs(Broadband);
	for (j = 0, iter = list.begin() ; iter != list.end() ; iter++, j++)
		cout << j + 1 << ") " << list[j] << endl;

	cout << "Enter your modem number: ";
	cin >> j;

	int conmethod;
	cout << endl << "Dialing method:\n1) PPtP Dialer\n2) PPPoE Dialer\n3) Dialer, Address from DHCP server\nEnter dialing method: ";
	cin >> conmethod;

	Ethernet::ConnectionType type;
	switch (conmethod)
	{
	case 1:
		type = Ethernet::ConPPtP;
		break;

	case 2:
		type = Ethernet::ConPPPoE;
		break;

	case 3:
		type = Ethernet::ConDHCP;
		break;
	}

	Ethernet modem(&db, type);
	if (modem.Load(db.getModemByName(list[j - 1], Broadband)))
	{
		cerr << "This modem is not supported yet, we're working on it...\n";
		return -1;
	}

	if (modem.pAddress->addrType == Ethernet::AddrNone)
	{
		cerr << "Connection method unsupported for this modem.\n";
		return -1;
	}

	string eth;
	cout << "Enter ethernet device (e.g. eth0, eth1 etc.): ";
	cin >> eth;
	modem.setEth(eth);

	string username, passwd;
	cout << endl << "Username (without suffix): ";
	cin >> username;
	if (method == 1 && !isp.getADSLSuffix().empty())
	{
		username += string("@[*isp::adsl::usrsuffix*]");
		cout << Parse(username, &isp, 0, 0, 0) << endl;
	}

	else if (method == 2 && !isp.getCableSuffix().empty())
	{
		username += string("@[*isp::cable::usrsuffix*]");
		cout << Parse(username, &isp, 0, 0, 0) << endl;
	}

	cout << "Password: ";
	cin >> passwd;

	Authentication auth(username, passwd);

	cout << endl << "Using dialer: " << db.ResolveDialer(&isp, &modem) << endl;

	Dialer dial(&db);
	dial.LoadDialer(db.ResolveDialer(&isp, &modem));
	dial.setDebian(distro == 1);

	Connection con(&modem, &isp, &auth, &dial);

	string strName;

	cout << "Enter a name for this connection: ";
	cin >> strName;

	con.setName(strName);

	cout << "Building scripts..." << endl;
	if (con.Make())
	{
		cerr << "ERROR: Cannot create scripts.\n";
		return -1;
	}

	cout << "Compressing..." << endl;
	if (con.Install())
	{
		cerr << "ERROR: Cannot compress scripts.\n";
		return -1;
	}

	cout << "Done.\n";
*/
	return 0;
}

