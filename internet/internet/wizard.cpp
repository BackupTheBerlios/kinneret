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

#include "internet.h"

#include "db.h"
#include "isp.h"
#include "hardware.h"
#include "authentication.h"
#include "dialer.h"
#include "connection.h"
#include "parse.h"

int SelectFromList(vector<string> list)
{
	// print the list
	vector<string>::iterator iter;
	unsigned int j = 1;
	for (iter = list.begin() ; iter != list.end() ; iter++, j++)
		cout << j << ") " << *iter << endl;

	cout << endl;

	do
	{
		cout << "Enter selecteion (1-" << list.size() << "): ";
		cin >> j;
	} while (j <= 0 || j > list.size());

	return j;
}

int DoWizard(const ConfigFile &conf, const CommandLine &cmdline) throw (Error)
{
	try
	{
		Database db(conf.strDBPath);
		Description desc;
	
		cout << "Welcome to the internet connection's tool wizard!\n\n";

		// Debian
		cout << "Is this Linux based on Debian?\n";
		vector<string> vec;
		vec.push_back("Yes (e.g. Debian, Knnopix, Kinneret etc.)");
		vec.push_back("No (e.g. RedHat, Mandrake etc.)");
		int j = SelectFromList(vec);
		desc.bDebianBased = (j == 1);

		cout << endl;

		// ISP
		cout << "Please select your ISP from the list:\n";
		vector<string> list = db.ListISPs();
		vector<string> clist = db.ListISPs(true);
		j = SelectFromList(list);
		desc.strISP = clist[j - 1];
		db.getISPPath(desc.strISP);		// will throw an exception of ISP is invalid

		cout << endl;

		// Connection Method
		cout << "You are connecting to the internet using...\n";
		vec.clear();
		vec.push_back("ADSL");
		vec.push_back("Cables");
		vec.push_back("LAN");
		vec.push_back("Dialup");
		j = SelectFromList(vec);

		switch (j)
		{
		case 1:
			desc.conMethod = ADSL;
			break;

		case 2:
			desc.conMethod = Cable;
			break;

		case 3:
			desc.conMethod = LANSlave;
			break;

		case 4:
			desc.conMethod = Analog;
			break;
		}

		cout << endl;

		if (desc.conMethod == ADSL || desc.conMethod == Cable)
		{
			// Modem
			cout << "Please select your modem from the list:\n";
			vec = db.ListHWs(Broadband);
			j = SelectFromList(vec);
			desc.strModem = vec[j - 1];
			db.getModemByName(desc.strModem, Broadband);	// again, for the exception

			cout << endl;

			// Dual?
			string strModemFile = db.getModemByName(desc.strModem, Broadband);
			Hardware::MinorType minor = getHardwareType(strModemFile, Broadband, &db);
			if (minor == Hardware::Unknown) throw Error("Invalid modem");
			switch (minor)
			{
			case Hardware::BBDual:
				cout << "Your modem is connected to the computer through...\n";
				vec.clear();
				vec.push_back("Ethernet");
				vec.push_back("USB");
				j = SelectFromList(vec);
				desc.interInterface = (j == 1) ? interEthernet : interUSB;

				cout << endl;
				break;

			case Hardware::BBUSB:
				desc.interInterface = interUSB;
				break;

			case Hardware::BBEth:
				desc.interInterface = interEthernet;
				break;

			default:
				break;
			}

			// Eth
			cout << "Which ethernet device your modem occupies?\n";
			vec.clear();

			// list eths
			int ret = system("cat /proc/net/dev | grep eth | cut -b 3-6 > /tmp/.eths");

			ifstream eths("/tmp/.eths");
			if (!eths || ret != 0) throw Error("Cannot query ethernet interfaces");

			while (!eths.eof())
			{
				char szBuffer[0xFF];
				eths.getline(szBuffer, 0xFF);
				if (strlen(szBuffer))
				{
					szBuffer[4] = 0;
					vec.push_back(szBuffer);
				}
			}

			eths.close();
			j = SelectFromList(vec);

			desc.strEth = vec[j - 1];

			cout << endl;

			cout << "Username: ";
			cin >> desc.strUsername;

			system("stty -echo");
			cout << "Password: ";
			cin >> desc.strPasswd;
			system("stty echo");

			cout << endl << endl;

			// Server
			cout << "Do you need to enter a server name?\n";
			vec.clear();
			vec.push_back("Yes");
			vec.push_back("No");
			j = SelectFromList(vec);
			if (j == 1)
			{
				cout << "Server: ";
				cin >> desc.strServer;
			}

			// Connection name
			char szBuffer[0xFF];
			cin.getline(szBuffer, 0xFF);
			do
			{
				cout << "Connetion Name (Unique!): ";
				cin.getline(szBuffer, 0xFF);
				desc.strConnectionName = string(szBuffer);
			} while (FileExists(conf.strDBPath + "connections/" + desc.strConnectionName + ".tar.gz"));

			cout << endl;

			cout << "You are about to create:\n";
			cout << "Scripts for ";
			if (!desc.bDebianBased) cout << "non-";
			cout << "Debian based systems, for ";

			cout << ((desc.conMethod == ADSL) ? "ADSL" : "Cable") << ", ";
			cout << "to " << desc.strISP << "," << endl;
			cout << "Using " << desc.strModem << ", on " << desc.strEth << endl;
			cout << "that is connected to ";
			cout << ((desc.interInterface == interUSB) ? "a USB port." : "an Ethernet card.");
			cout << endl;
			cout << "\nIs this correct [yn] ? ";

			char c;
			do
			{
				cin >> c;
			} while (c != 'n' && c != 'y');
			if (c == 'n') throw Error("Canceled by user");

			MakeFromDesc(desc, db, conf, cmdline);

			cout << "Done.\n\n";
		}

		else if (desc.conMethod == LANSlave)
		{
			// Eth
			cout << "Which ethernet device your modem occupies?\n";
			vec.clear();

			// list eths
			int ret = system("cat /proc/net/dev | grep eth | cut -b 3-6 > /tmp/.eths");

			ifstream eths("/tmp/.eths");
			if (!eths || ret != 0) throw Error("Cannot query ethernet interfaces");

			while (!eths.eof())
			{
				char szBuffer[0xFF];
				eths.getline(szBuffer, 0xFF);
				if (strlen(szBuffer))
				{
					szBuffer[4] = 0;
					vec.push_back(szBuffer);
				}
			}

			eths.close();
			j = SelectFromList(vec);

			desc.strEth = vec[j - 1];

			cout << endl;

			// Address
			cout << "Static address, or obtained by DHCP?\n";
			vec.clear();
			vec.push_back("Static (Manual)");
			vec.push_back("From DHCP");
			j = SelectFromList(vec);
			if (j == 1)
			{
				char szBuffer[0xFF];
				
				desc.bLANDHCP = false;
				cout << "IP address of interface: ";
				cin >> desc.strLANIP;
				char c;
				cin.get(c);

				// Mask
				cout << "IP mask [default: 255.255.255.0]: ";
				cin.getline(szBuffer, 0xFF);
				desc.strLANMask = string(szBuffer);
				if (strlen(szBuffer) == 0) desc.strLANMask = string("255.255.255.0");

				// Broadcast
				cout << "Broadcast address [default: 255.255.255.255]: ";
				cin.getline(szBuffer, 0xFF);
				desc.strLANBroadcast = string(szBuffer);
				if (strlen(szBuffer) == 0) desc.strLANBroadcast = string("255.255.255.255");
			}

			else
			{
				char c;
				cin.get(c);
				desc.strLANIP = string("");
				desc.bLANDHCP = true;
			}

			char szBuffer[0xFF];

			// Gateway
			cout << "Gateway [default: 192.168.0.1]: ";
			cin.getline(szBuffer, 0xFF);
			desc.strLANGateway = string(szBuffer);
			if (desc.strLANGateway.empty()) desc.strLANGateway = string("192.168.0.1");

			cout << endl << endl;

			// Connection name
			do
			{
				cout << "Connetion Name (Unique!): ";
				cin.getline(szBuffer, 0xFF);
				desc.strConnectionName = string(szBuffer);
			} while (FileExists(conf.strDBPath + "connections/" + desc.strConnectionName + ".tar.gz"));

			cout << endl;

			///////////////////////////
			cout << "You are about to create:\n";
			cout << "Scripts for ";
			if (!desc.bDebianBased) cout << "non-";
			cout << "Debian based systems, for LAN connectio, " << endl;
			cout << "to " << desc.strISP << "," << endl;
			cout << "Using " << desc.strEth << endl;
			cout << "through " << desc.strLANGateway << endl;
			cout << "the interface will have ";

			if (desc.bLANDHCP) cout << "it's address from a DHCP server";
			else
			{
				cout << "the static address " << desc.strLANIP;
				cout << " with the network mask " << desc.strLANMask << endl;
				cout << "The interface will use the broadcast address " << desc.strLANBroadcast << endl;
			}
			
			cout << "\nIs this correct [yn] ? ";

			char c;
			do
			{
				cin >> c;
			} while (c != 'n' && c != 'y');
			if (c == 'n') throw Error("Canceled by user");

			////////////
			MakeFromDesc(desc, db, conf, cmdline);

			cout << "Done.\n\n";
		}

		else if (desc.conMethod == Analog)
		{
			// Phones
			cout << "Please select the server near you:\n";
			ISP isp(&db);
			isp.LoadISP(desc.strISP);
			map<string, string> ph = isp.getDialupMap();
			map<string, string>::iterator iter;
			int count = 0;
			for (iter = ph.begin() ; iter != ph.end() ; iter++, count++)
				cout << count + 1 << ") " << iter->second << " (" << iter->first << ")" << endl;

			cout << endl;

			do
			{
				cout << "Enter selecteion (1-" << count << "): ";
				cin >> j;
			}
			while (j <= 0 || j > count);

			count = 0;
			for (iter = ph.begin() ; count < j - 1 ; iter++, count++);
			string phonenum = iter->second;

			cout << endl;
			cout << "What area code are you in?\n";
			vec.clear();
			vec.push_back("02");
			vec.push_back("03");
			vec.push_back("04");
			vec.push_back("06");
			vec.push_back("07");
			vec.push_back("08");
			vec.push_back("09");
			j = SelectFromList(vec);

			string strarea = vec[j - 1];

			// compile ATDT code
			string phonecode = phonenum.substr(0, 2);
			if (strarea == phonecode)
				desc.strATDT = phonenum.substr(3, 7);
			else desc.strATDT = phonecode + phonenum.substr(3, 7);

			cout << "Username: ";
			cin >> desc.strUsername;

			system("stty -echo");
			cout << "Password: ";
			cin >> desc.strPasswd;
			system("stty echo");

			cout << endl << endl;
/*
			// Server
			cout << "Do you need to enter a server name?\n";
			vec.clear();
			vec.push_back("Yes");
			vec.push_back("No");
			j = SelectFromList(vec);
			if (j == 1)
			{
				cout << "Server: ";
				cin >> desc.strServer;
			}
*/
			// Connection name
			char szBuffer[0xFF];
			cin.getline(szBuffer, 0xFF);
			do
			{
				cout << "Connetion Name (Unique!): ";
				cin.getline(szBuffer, 0xFF);
				desc.strConnectionName = string(szBuffer);
			} while (FileExists(conf.strDBPath + "connections/" + desc.strConnectionName + ".tar.gz"));

			cout << endl;

			cout << "You are about to create:\n";
			cout << "Scripts for ";
			if (!desc.bDebianBased) cout << "non-";
			cout << "Debian based systems, for a dialup connection,\n";
			cout << "connecting to " << phonenum << " (ATDT " << desc.strATDT << ").\n";
			cout << endl;
			cout << "\nIs this correct [yn] ? ";

			char c;
			do
			{
				cin >> c;
			} while (c != 'n' && c != 'y');
			if (c == 'n') throw Error("Canceled by user");

			MakeFromDesc(desc, db, conf, cmdline);

			cout << "Done.\n\n";
		}
	}

	catch (...)
	{
		throw;
	}
	
	return 0;
}

