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

void Authentication::MakeInit(ostream &stream) const
{
	stream << "# backup" << endl;
	stream << "cp /etc/ppp/pap-secrets /etc/ppp/pap-secrets.bak" << endl;
	stream << "cp /etc/ppp/chap-secrets /etc/ppp/chap-secrets.bak" << endl;

	stream << "echo '\"" << getUsername() << "\" * \"" << getPasswd() << "\"' > /etc/ppp/pap-secrets" << endl;
	stream << "echo '\"" << getUsername() << "\" * \"" << getPasswd() << "\"' > /etc/ppp/chap-secrets" << endl;
}

void Authentication::MakeBoot(ostream &stream) const { stream << endl; }
void Authentication::MakeConnect(ostream &stream) const { stream << endl; }

void Authentication::MakeDisconnect(ostream &stream) const
{
	stream << "# restore" << endl;
	stream << "cp /etc/ppp/pap-secrets.bak /etc/ppp/pap-secrets" << endl;
	stream << "cp /etc/ppp/chap-secrets.bak /etc/ppp/chap-secrets" << endl;
}

void Authentication::MakeDone(ostream &stream) const { stream << endl; }



