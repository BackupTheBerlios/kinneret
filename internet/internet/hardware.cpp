/***************************************************************************
                          hardware.cpp  -  description
                             -------------------
    begin                : Wed Jul 16 2003
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
Hardware::MinorType getHardwareType(string name, HardwareType ht, const Database *const pDB) throw (Error)
{
	xmlKeepBlanksDefault(0);

	xmlDocPtr doc;
	try
	{
		doc = xmlParseFile(pDB->getHWPath(name, ht).c_str());
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

	string strIFace("NA");
	bool bFound = false;

	cur = cur->xmlChildrenNode;
	while (cur != 0 && !bFound)
	{
		if (IsNode(cur, "hardware"))
		{
			xmlNodePtr save = cur;
			cur = cur->xmlChildrenNode;
			while (cur != 0)
			{
				if (IsNode(cur, "interface"))
				{
					strIFace = GetVal(doc, cur);
					bFound = true;

					break;
				}
				cur = cur->next;
			}
			cur = save;
		}

		cur = cur->next;
	}
	
	xmlFreeDoc(doc);
	xmlCleanupParser();

	if (strIFace == "ethernet")			return Hardware::BBEth;
	if (strIFace == "usb")				return Hardware::BBUSB;
	if (strIFace == "usb||ethernet")	return Hardware::BBDual;

	return Hardware::Unknown;
}

