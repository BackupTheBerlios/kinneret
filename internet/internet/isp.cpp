/***************************************************************************
                          isp.cpp  -  description
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
#include <iostream>
using namespace std;

#include "isp.h"
#include "db.h"

#include "xml.h"

ISP::ISP(const Database *const db) : strName(""),
	strCName(""),
	strDNS1(""),
	strDNS2(""),
	strHomepage(""),
	strTech(""),
	strJoin(""),
	strProxyManual(""),
	strProxyAuto(""),
	strPOP3(""),
	strIMAP(""),
	strSMTP(""),
	strEMailSuffix(""),
	strCableGateway(""),
	strCableRemotename(""),
	strADSLSuffix(""),
	strCableSuffix(""),
	strSG(""),
	pDB(db)
{
}

void ISP::LoadISP(string name) throw (Error)
{
	xmlKeepBlanksDefault(0);

	xmlDocPtr doc;

	try
	{
		doc = xmlParseFile(pDB->getISPPath(name).c_str());
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
		throw Error("XML document is empty, invalid ISP file");
	}

	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "name"))	strName = GetVal(doc, cur);
		if (IsNode(cur, "cname"))	strCName = GetVal(doc, cur);
		if (IsNode(cur, "dns1"))	strDNS1 = GetVal(doc, cur);
		if (IsNode(cur, "dns2"))	strDNS2 = GetVal(doc, cur);
		
		if (IsNode(cur, "proxy"))		ParseProxy(doc, cur);
		if (IsNode(cur, "support"))		ParseSupport(doc, cur);
		if (IsNode(cur, "email"))		ParseEMail(doc, cur);
		if (IsNode(cur, "broadband"))	ParseBroadband(doc, cur);
		if (IsNode(cur, "isdn"))		ParseISDN(doc, cur);
		if (IsNode(cur, "dialup"))		ParseDialup(doc, cur);

		cur = cur->next;
	}

	xmlFreeDoc(doc);

	xmlCleanupParser();
}

void ISP::ParseSupport(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "homepage"))	strHomepage = GetVal(doc, cur);
		if (IsNode(cur, "tech"))		strTech = GetVal(doc, cur);
		if (IsNode(cur, "join"))		strJoin = GetVal(doc, cur);
		
		cur = cur->next;
	}
}
	
void ISP::ParseEMail(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "pop3"))		strPOP3 = GetVal(doc, cur);
		if (IsNode(cur, "imap"))		strIMAP = GetVal(doc, cur);
		if (IsNode(cur, "smtp"))		strSMTP = GetVal(doc, cur);
		if (IsNode(cur, "suffix"))		strEMailSuffix = GetVal(doc, cur);
		
		cur = cur->next;
	}
}
	
void ISP::ParseBroadband(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "gateway")) ParseBroadbandGateway(doc, cur);
		if (IsNode(cur, "usrsuffix") && IsProp(cur, "type", "adsl"))	strADSLSuffix = GetVal(doc, cur);
		if (IsNode(cur, "usrsuffix") && IsProp(cur, "type", "cable"))	strCableSuffix = GetVal(doc, cur);
		
		cur = cur->next;
	}
}
	
void ISP::ParseBroadbandGateway(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "cable"))
		{
			xmlNodePtr save = cur;
			cur = cur->xmlChildrenNode;

			while (cur != 0)
			{
				if (IsNode(cur, "remotename"))	strCableRemotename = GetVal(doc, cur);
				if (IsNode(cur, "ip"))			strCableGateway = GetVal(doc, cur);
				if (IsNode(cur, "searchgroup"))	strSG = GetVal(doc, cur);

				cur = cur->next;
			}

			cur = save;
		}
		
		cur = cur->next;
	}

	if (strCableGateway.empty())
		strCableGateway = strCableRemotename;
}

void ISP::ParseISDN(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "server")) mapISDN[GetProp(cur, "loc")] = GetVal(doc, cur);
		cur = cur->next;
	}
}

void ISP::ParseDialup(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "server")) mapDialup[GetProp(cur, "loc")] = GetVal(doc, cur);
		cur = cur->next;
	}
}

void ISP::ParseProxy(xmlDocPtr doc, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;
	while (cur != 0)
	{
		if (IsNode(cur, "manual"))	strProxyManual = GetVal(doc, cur);
		if (IsNode(cur, "auto"))	strProxyAuto = GetVal(doc, cur);
		cur = cur->next;
	}
}

void ISP::MakeInit(ostream &stream)
{
	stream << "# backup" << endl;
	stream << "cp /etc/resolv.conf /etc/resolv.conf.bak" << endl;

	stream << endl;
	
	if (!getSG().empty())
	{
		stream << "echo \"search " << getSG() << "\" > /etc/resolv.conf" << endl;
		stream << "echo \"nameserver " << getDNS1() << "\" >> /etc/resolv.conf" << endl;
	}

	else stream << "echo \"nameserver " << getDNS1() << "\" > /etc/resolv.conf" << endl;

	stream << "echo \"nameserver " << getDNS2() << "\" >> /etc/resolv.conf" << endl;
}



