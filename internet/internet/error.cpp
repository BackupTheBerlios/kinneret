/***************************************************************************
                          error.cpp  -  description
                             -------------------
    begin                : Sat Jul 19 2003
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
#include "internet.h"

string ErrorInvalidArgValue::Msg()
{
	string ret = string("ERROR: Argument --" + strMessage + " must be one of these:\n");
	vector<string>::iterator iter;

	for (iter = vList.begin() ; iter != vList.end() ; iter++)
		ret += *iter + string("\n");
	
	return ret;
}

