/***************************************************************************
                          authentication.cpp  -  description
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
#include "authentication.h"

void Authentication::MakeInit(ostream &stream)
{
	stream << "echo '\"" << getUsername() << "\" * \"" << getPasswd() << "\"' > /etc/ppp/pap-secrets" << endl;
	stream << "echo '\"" << getUsername() << "\" * \"" << getPasswd() << "\"' > /etc/ppp/chap-secrets" << endl;
}



