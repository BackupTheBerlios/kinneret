/***************************************************************************
                          xml.cpp  -  description
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
#include "xml.h"

bool IsNode(xmlNodePtr cur, string name)
{
	return !xmlStrcmp(cur->name, reinterpret_cast<const xmlChar*>(name.c_str()));
}

string GetVal(xmlDocPtr doc, xmlNodePtr cur)
{
	return string(reinterpret_cast<char*>(xmlNodeListGetString(doc, cur->xmlChildrenNode, 1)));
}

bool IsProp(xmlNodePtr cur, string name, string val)
{
	return !xmlStrcmp(xmlGetProp(cur, reinterpret_cast<const xmlChar*>(name.c_str())),
		reinterpret_cast<const xmlChar*>(val.c_str()));
}

string GetProp(xmlNodePtr cur, string name)
{
	return string(reinterpret_cast<char*>(xmlGetProp(cur, reinterpret_cast<const xmlChar*>(name.c_str()))));
}



