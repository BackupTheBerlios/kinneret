/***************************************************************************
                          parse.cpp  -  description
                             -------------------
    begin                : Mon Jun 30 2003
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
#include "parse.h"
#include "xml.h"

string Parse(string str, ISP *isp, Authentication *auth, Hardware *hw, Dialer *dial)
{
	// this will parse the string once and will try to parse it again.
	// the recoursion will stop when there is nothing to parse.
	string ret = str;

	// parse...
	while (ret.find("[*") != string::npos)
	{
		string::size_type st = ret.find("[*");
		string::size_type en = ret.find("*]");

		string name = ret.substr(st + 2, en - st - 2);

		if (name.find("isp::") != string::npos)
		{
			if (isp == 0)
			{
				cerr << "No valid ISP module.\n";
				return string("");
			}

			if (name == "isp::name")						name = isp->getName();
			else if (name == "isp::cname")					name = isp->getCName();
			else if (name == "isp::dns1")					name = isp->getDNS1();
			else if (name == "isp::dns2")					name = isp->getDNS2();
			else if (name == "isp::homepage")				name = isp->getHomepage();
			else if (name == "isp::tech")					name = isp->getTech();
			else if (name == "isp::join")					name = isp->getJoin();
			else if (name == "isp::pop3")					name = isp->getPOP3();
			else if (name == "isp::smtp")					name = isp->getSMTP();
			else if (name == "isp::emailsuffix")			name = isp->getEMailSuffix();
			else if (name == "isp::cable::gateway")			name = isp->getCableGateway();
			else if (name == "isp::cable::remotename")		name = isp->getCableRemotename();
			else if (name == "isp::adsl::usrsuffix")		name = isp->getADSLSuffix();
			else if (name == "isp::cable::usrsuffix")		name = isp->getCableSuffix();
			else
			{
				cerr << "Invalid reference name " << name << endl;
				return string("");
			}
		}

		else if (name.find("auth::") != string::npos)
		{
			if (auth == 0)
			{
				cerr << "No valid authentication module.\n";
				return string("");
			}

			if (name == "auth::usr")	name = auth->getUsername();
			else if (name == "auth::passwd")	name = auth->getPasswd();
			else
			{
				cerr << "Invalid reference name " << name << endl;
				return string("");
			}
		}

		else if (name.find("hw::") != string::npos)
		{
			if (auth == 0)
			{
				cerr << "No valid hardware module.\n";
				return string("");
			}

			if (name == "hw::eth")						name = dynamic_cast<Ethernet*>(hw)->getEth();
			else if (name == "hw::adsl::gateway")		name = dynamic_cast<Ethernet*>(hw)->getIP();
			else if (name == "hw::adsl::remotename")	name = dynamic_cast<Ethernet*>(hw)->getRemotename();
			else
			{
				cerr << "Invalid reference name " << name << endl;
				return string("");
			}
		}

		else if (name.find("dialer::") != string::npos)
		{
			if (auth == 0)
			{
				cerr << "No valid hardware module.\n";
				return string("");
			}

			if (name == "dialer::iface")	name = dial->getIFace();
			else
			{
				cerr << "Invalid reference name " << name << endl;
				return string("");
			}
		}

		else
		{
			cerr << "Invalid reference name " << name << endl;
			return string("");
		}

		ret.replace(st, en - st + 2, name);
	}

	// done
	return ret;
}



