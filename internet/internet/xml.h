/***************************************************************************
                          xml.h  -  description
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
#ifndef INTERNET_XML_SMALLLIB
#define INTERNET_XML_SMALLLIB

#include <string>
using namespace std;

#include <libxml/parser.h>

extern bool				IsNode(xmlNodePtr cur, string name);
extern string			GetVal(xmlDocPtr doc, xmlNodePtr cur);
extern bool				IsProp(xmlNodePtr cur, string name, string val);
extern string			GetProp(xmlNodePtr cur, string name);

#endif



