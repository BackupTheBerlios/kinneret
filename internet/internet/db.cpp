/***************************************************************************
                          db.cpp  -  description
                             -------------------
    begin                : Thu Jun 12 2003
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
#include <fstream>
using namespace std;

#include <stdlib.h>

#include "db.h"
#include "isp.h"
#include "hardware.h"

#include "xml.h"

string Database::getISPPath(string strName) const throw (Error)
{
	string strLang = (nLang == Hebrew) ? string("he/") : string("en/");
	string Filename = strPath + string("isps/") + strLang + strName + string(".xml");

	// See if exists
	if (!FileExists(Filename)) throw Error404(Filename);
	return Filename;
}

string Database::getHWPath(string strName, HardwareType type) const throw (Error)
{
	string strHWT;
	switch (type)
	{
	case Broadband:
		strHWT = "broadband/";
		break;

	case ISDN:
		strHWT = "isdn/";
		break;

	case Dialup:
		strHWT = "dialup/";
		break;
	}
		
	string Filename = strPath + string("hws/") + strHWT + strName + string(".xml");

	// See if exists
	if (!FileExists(Filename)) throw Error404(Filename);
	return Filename;
}

string Database::getDialerPath(string strName) const throw (Error)
{
	string Filename = strPath + string("dialers/") + strName;

	// See if exists
	if (!FileExists(Filename)) throw Error404(Filename);
	return Filename;
}

vector<string> Database::ListISPs(bool bCNames) const throw (Error)
{
	ISP isp(this);
	vector<string> ret;
	string strName, strCmd;
	string strLang = (nLang == Hebrew) ? string("he/") : string("en/");

	strCmd = string("ls '") + strPath + string("isps/") + strLang + string("' > /tmp/.isps");
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	ifstream ls("/tmp/.isps");
	if (!ls) throw Error404("/tmp/.isps");
	
	while (!ls.eof())
	{
		ls >> strName;
		if (!strName.empty() && strName != "CVS")
		{
			strName.erase(strName.find(".xml"));

			// We need to open the xml and parse the name...
			isp.LoadISP(strName);

			if (!bCNames) strName = isp.getName();
			else strName = isp.getCName();
				
			ret.push_back(strName);
			strName.clear();
		}
	}

	ls.close();
	return ret;
}

vector<string> Database::ListHWs(HardwareType ht) const throw (Error)
{
	vector<string> ret;
	string strName, strCmd, strDir;

	switch (ht)
	{
	case Broadband:
		strDir = string("broadband");
		break;

	case Dialup:
		strDir = string("dialup");
		break;

	case ISDN:
		strDir = string("isdn");
		break;
	}

	strCmd = string("ls '") + strPath + string("hws/") + strDir + string("/") + string("' > /tmp/.hws");
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	ifstream ls("/tmp/.hws");
	if (!ls) throw Error404("/tmp/.hws");
	
	while (!ls.eof())
	{
		ls >> strName;
		if (!strName.empty() && strName != "CVS")
		{
			strName.erase(strName.find(".xml"));

			// We need to open the xml and parse the name...
			xmlKeepBlanksDefault(0);
			xmlDocPtr doc;

			try
			{
				doc = xmlParseFile(getHWPath(strName, ht).c_str());
			}

			catch (...)
			{
				throw;	// pass the exception to the caller,
				// he'll know what to do with it (probably passing it to the main
				// program, thus pringting and error and abotring...)
			}
			
			if (doc == 0) throw Error("Cannot initialize XML parser");
			
			xmlNodePtr cur = xmlDocGetRootElement(doc);
			if (cur == 0)
			{
				xmlFreeDoc(doc);
				throw Error("XML document is empty, invalid hardware file");
			}

			cur = cur->xmlChildrenNode;
			while (cur != 0)
			{
				if (IsNode(cur, "name")) strName = GetVal(doc, cur);
				cur = cur->next;
			}

			xmlFreeDoc(doc);
			xmlCleanupParser();

			// add the name			
			ret.push_back(strName);
			strName.clear();
		}
	}

	ls.close();
	return ret;
}

vector<string> Database::ListDialers() const throw (Error)
{
	vector<string> ret;
	string strName, strCmd;

	strCmd = string("ls '") + strPath + string("dialers/' > /tmp/.dlrs");
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	ifstream ls("/tmp/.dlrs");
	if (!ls) throw Error404("/tmp/.dlrs");
	
	while (!ls.eof())
	{
		ls >> strName;
		if (!strName.empty() && strName != "CVS")
		{
			ret.push_back(strName);
			strName.clear();
		}
	}

	ls.close();
	return ret;
}

string Database::ResolveDialer(ISP *isp, Hardware *hw, HardwareType ht) const throw (Error)
{
	switch (ht)
	{
	case Broadband:
		// ATM
		// we'll use RTTI, ADSL USB modems needs PPPoATM
		if (typeid(hw) == typeid(USB) && hw->getModemType() == ADSL) return string("atm");

		// Mess with Cables first, we only have one dialer... USB or Ethernet,
		// CDCEther makes them the same... :)
		if (hw->getModemType() == Cable)
		{
			return string("pptp_cable_resolv.conf_workaround");
		}

		// ADSL l8er...
		else if (hw->getModemType() == ADSL)
		{
			// PPtP or PPPoE ?
			// We can safly assume hw point to Ethernet or one of it's derived classes,
			// so dynamicly casting will be allowed.
			Ethernet *eth;
			if (!(eth = dynamic_cast<Ethernet*>(hw)))
				throw Error("Cast error, programmer's fault, please report a bug...");

			if (eth->getVPNType() == Ethernet::PPPoE) return string("pppoe_adsl");
			else if (eth->getVPNType() == Ethernet::PPtP)
			{
				if (isp->getCName() == "bezeqint") return string("pptp_adsl_bezeqint");
				else return string("pptp_adsl");
			}
		}
		
		break;

	default:
		throw Error("Cannot resolve dialer");
		break;
	}

	throw Error("Cannot resolve dialer");
}

string Database::getModemByName(string name, HardwareType ht) const throw (Error)
{
	vector<string> list;
	string strName, strCmd, strDir;

	switch (ht)
	{
	case Broadband:
		strDir = string("broadband");
		break;

	case Dialup:
		strDir = string("dialup");
		break;

	case ISDN:
		strDir = string("isdn");
		break;
	}

	strCmd = string("ls '") + strPath + string("hws/") + strDir + string("/") + string("' > /tmp/.hws");
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	ifstream ls("/tmp/.hws");
	if (!ls) throw Error404("/tmp/.hws");
	
	while (!ls.eof())
	{
		ls >> strName;
		if (!strName.empty() && strName != "CVS")
		{
			strName.erase(strName.find(".xml"));
			list.push_back(strName);
			strName.clear();
		}
	}

	ls.close();
	
	vector<string>::iterator iter;

	int j;
	for (iter = list.begin(), j = 0 ; iter != list.end() ; iter++, j++)
	{
		xmlKeepBlanksDefault(0);

		xmlDocPtr doc;
		try
		{
			doc = xmlParseFile(getHWPath(list[j], ht).c_str());
		}

		catch (...)
		{
			throw;
		}
		
		if (doc == 0) throw Error("Cannot initialize XML parser");

		xmlNodePtr cur = xmlDocGetRootElement(doc);
		if (cur == 0)
		{
			xmlFreeDoc(doc);
			throw Error("XML document is empty, invalid depencies file");
		}

		cur = cur->xmlChildrenNode;
		while (cur != 0)
		{
			if (IsNode(cur, "name")) strName = GetVal(doc, cur);
			cur = cur->next;
		}

		xmlFreeDoc(doc);
		xmlCleanupParser();
		
		if (name == strName) return list[j];
	}

	throw Error("No such hardware");
}



