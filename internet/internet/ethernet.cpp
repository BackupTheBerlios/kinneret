/***************************************************************************
                          ethernet.cpp  -  description
                             -------------------
    begin                : Thu Jun 19 2003
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
#include "hardware.h"
#include "db.h"

#include "xml.h"

void Ethernet::MakeInit(ostream &stream) const
{
	stream << endl;
}

void Ethernet::MakeBoot(ostream &stream) const
{
	if (!ipInterface.strIP.empty() || !ipInterface.strMask.empty() ||
		!ipInterface.strBroadcast.empty() || !ipInterface.strGateway.empty())
	{
		stream << "# bring up interface and set addresses" << endl;
		stream << "ifconfig " << strEth << " ";

		if (!ipInterface.strIP.empty())			stream << ipInterface.strIP << " ";
		if (!ipInterface.strMask.empty())		stream << "netmask " << ipInterface.strMask << " ";
		if (!ipInterface.strBroadcast.empty())	stream << "broadcast " << ipInterface.strBroadcast << " ";
		if (!ipInterface.strGateway.empty())
		{
			stream << endl;
			stream << endl << "# set default route's gateway" << endl;
			stream << "route del default" << endl;
			stream << "route add default gw " << ipInterface.strGateway << endl;
		}
	}

	else stream << "ifconfig " << strEth << " up\n";
	stream << endl;
}

void Ethernet::Load(string name) throw (Error)
{
	xmlKeepBlanksDefault(0);

	xmlDocPtr doc;

	try
	{
		doc = xmlParseFile(pDB->getHWPath(name, Broadband).c_str());
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
		throw Error("XML document is empty, invalid hardware file");
	}

	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "name")) strName = GetVal(doc, cur);

		if (IsNode(cur, "hardware"))
		{
			xmlNodePtr save = cur;
			cur = cur->xmlChildrenNode;

			while (cur != 0)
			{
				if (IsNode(cur, "type"))
				{
					if (GetVal(doc, cur) == "adsl")			moType = ADSL;
					else if (GetVal(doc, cur) == "cable")	moType = Cable;
					else throw Error("Invalid modem type");
				}
				
				cur = cur->next;
			}

			cur = save;
		}
		
		if (IsNode(cur, "vpn"))
		{
			xmlNodePtr save = cur;
			cur = cur->xmlChildrenNode;

			while (cur != 0)
			{
				if (IsNode(cur, "type"))
				{
					if (GetVal(doc, cur) == "pptp")			conType = PPtP;
					else if (GetVal(doc, cur) == "pppoe")	conType = PPPoE;
					else throw Error("Invalid connection type");
				}

				if (IsNode(cur, "address"))		strIP = GetVal(doc, cur);
				if (IsNode(cur, "remotename"))	strRemotename = GetVal(doc, cur);
				if (IsNode(cur, "device"))
				{
					xmlNodePtr save2 = cur;
					cur = cur->xmlChildrenNode;

					while (cur != 0)
					{
						if (IsNode(cur, "address"))		ipInterface.strIP			= GetVal(doc, cur);
						if (IsNode(cur, "mask"))		ipInterface.strMask			= GetVal(doc, cur);
						if (IsNode(cur, "broadcast"))	ipInterface.strBroadcast	= GetVal(doc, cur);
						if (IsNode(cur, "gateway"))		ipInterface.strGateway		= GetVal(doc, cur);
						cur = cur->next;
					}

					cur = save2;
				}

				cur = cur->next;
			}
			
			cur = save;
		}

		cur = cur->next;
	}

	xmlFreeDoc(doc);

	xmlCleanupParser();
}



