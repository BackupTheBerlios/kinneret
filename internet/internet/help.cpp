/***************************************************************************
                          help.cpp  -  description
                             -------------------
    begin                : Sat Jul 12 2003
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

void PrintHelp()
{
	cout <<
	"Usage: internet [options...]""\n"
	"\n"
	"Options list:"																	"\n"
	"Modifiers:"																	"\n"
	"--help (-h):				This help screen"									"\n"
	"--verbose (-v):				Be verbose"										"\n"
	"--quite (-q):				Be quite (no output)"								"\n"
	"--wizard (-w):				Starts in wizard mode"								"\n"
	"--force (-f)				Forces a delete (no questions)"						"\n"
	"\n"
	"Create:"																		"\n"
	"--debian=[yes|no] (-b):			'yes' if debian based, 'no' if not"			"\n"
	"--isp=[name] (-i):			The cname of the ISP"								"\n"
	"--method=[type] (-m):			Method, valid types are adsl, cable and lan"	"\n"
	"--modem=[name] (-M):			Modem's name"									"\n"
	"--iface=[type]				Modem's interface (in case of dual),"				"\n"
	"					Valids are 'usb' or 'eth'."									"\n"
	"--dev=[name] (-d):			Ethernet device, eth0, eth1 etc."					"\n"
	"--username=[name] (-u):			Username, without the suffix"				"\n"
	"--passwd=[passwrod] (-p):		Password"										"\n"
	"--server=[server]			Server (Apply to HUJI mainly)"						"\n"
	"--name=[name] (-n):			Name of the dialer"								"\n"
	"--ip=[ip/dhcp]:				Only valid in LAN connections, the IP address"	"\n"
	"					of the interface or the string 'dhcp' if server"			"\n"
	"					is using DHCP."												"\n"
	"--mask=[ip]				Network mask (default: 255.255.255.0)"				"\n"
	"--broadcast=[ip]			Broadcast address (default: 255.255.255.255)"		"\n"
	"--gateway=[ip]				Gateway (default: 192.168.0.1)"						"\n"
	"\n"
	"Information:"																	"\n"
	"--listisps (-l)				Lists known ISPs and quits"						"\n"
	"--listhws [type] (-H)			Lists known hardwares, valis types are:"		"\n"
	"\tbroadband				ADSL and Cable modems"								"\n"
	"\tisdn					ISDN modems"											"\n"
	"\tdialup					Dial-up modems"										"\n"
	"\n"
	"--listcons (-C)				Lists connections"								"\n"
	"--hwinfo [name]				Hardware's type"								"\n"
	"--ispinfo [name]				Lists information about the ISP"				"\n"
	"--defaultshow				Shows default connection"							"\n"
	"\n"
	"Managment:"																	"\n"
	"--delete [name]				Deletes a connection"							"\n"
	"--default=[name]			Sets default connection"							"\n"
	"--extract=[name] [con] [file]		Extracts the script [name] from"			"\n"
	"					the connection con to the file	'file',"					"\n"
	"					valid scripts are:"											"\n"
	"\tinit"																		"\n"
	"\tboot"																		"\n"
	"\tconnect"																		"\n"
	"\tdisconnect"																	"\n"
	"\n"
	"Use:"																			"\n"
	"--connect=<name> (-c)			Connects to <name>, if name not presented,"		"\n"
	"					connects to 'default'"										"\n"
	"--kill=<name> (-k)			Kills <name>, if name not presented,"				"\n"
	"					kills 'default'"											"\n"
	"--init=<name>				Initializes a connection, if name not"				"\n"
	"					presented, initializes 'default'"							"\n"
	"--boot=<name>				Executes the boot script of <name>,"				"\n"
	"					if name not presented, boots 'defaults'"					"\n"
	"\n";
}

