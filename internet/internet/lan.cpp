/***************************************************************************
                          lan.cpp  -  description
                             -------------------
    begin                : Wed Aug 20 2003
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

void LAN::MakeInit(ostream &stream) const { stream << endl; }
void LAN::MakeBoot(ostream &stream) const
{
	if (!bDHCP && (!getIP().empty() || !getMask().empty() || !getBroadcast().empty() || !getGateway().empty()))
	{
		stream << "# bring up interface and set addresses" << endl;
		stream << "ifconfig " << strEth << " ";

		if (!getIP().empty())			stream << getIP() << " ";
		if (!getMask().empty())			stream << "netmask " << getMask() << " ";
		if (!getBroadcast().empty())	stream << "broadcast " << getBroadcast() << " ";
		if (!getGateway().empty())
		{
			stream << endl;
			stream << endl << "# set default route's gateway" << endl;
			stream << "route del default" << endl;
			stream << "route add default gw " << getGateway() << endl;
		}
	}

	else if (bDHCP)
	{
		stream << "ifconfig " << strEth << " up\n";
#warning Add support for more clients
		stream << "dhclient\n";
	}
	
	stream << endl;
}

void LAN::MakeConnect(ostream &stream)		const { stream << endl; }
void LAN::MakeDisconnect(ostream &stream)	const { stream << endl; }
void LAN::MakeDone(ostream &stream)			const { stream << endl; }

