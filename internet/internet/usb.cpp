/***************************************************************************
                          usb.cpp  -  description
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
#include "hardware.h"
#include "db.h"

#include "xml.h"

void USB::MakeInit(ostream &stream) const
{
	Ethernet::MakeInit(stream);
}

void USB::MakeBoot(ostream &stream) const
{
	stream << "# Load module" << endl;
	stream << "modprobe " << strDriver << endl;
	stream << endl;
	
	Ethernet::MakeBoot(stream);
}

void USB::Load(string name) throw (Error)
{
	xmlKeepBlanksDefault(0);
	xmlDocPtr doc;

	try
	{
		Ethernet::Load(name);
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
		if (IsNode(cur, "module")) strDriver = GetVal(doc, cur);
		cur = cur->next;
	}

	xmlFreeDoc(doc);
	xmlCleanupParser();
}



