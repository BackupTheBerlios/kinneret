/***************************************************************************
                          internet.h  -  description
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
#ifndef __INTERNET_INTERNET_H_
#define __INTERNET_INTERNET_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <typeinfo>
using namespace std;

#include <unistd.h>
#include <getopt.h>

#include <stdlib.h>

/////////////////////////////////
// Error hirarchy - for excetions
class Error
{
public:
	string	strMessage;

	Error(string msg) { strMessage = msg; }
	virtual ~Error() {}

	virtual string Msg() { return string("ERROR: ") + strMessage + string("\n"); }
};

// File not found :)
class Error404 : public Error
{
public:
	Error404(string file) : Error("Cannot find: " + file) {}
	virtual ~Error404() {}
};

// Invalid argument
class ErrorInvalidArg : public Error
{
public:
	ErrorInvalidArg(string str = string("")) : Error("Invalid argument") {}
	~ErrorInvalidArg() {}
};

// Missing argument
class ErrorMissingArg : public Error
{
public:
	ErrorMissingArg(string arg) : Error("You must supply: --" + arg + " in current mode") {}
	virtual ~ErrorMissingArg() {}
};

// Invalid argument value
class ErrorInvalidArgValue : public Error
{
public:
	vector<string> vList;
	
	ErrorInvalidArgValue(string arg, vector<string> list) : Error(arg) { vList = list; }
	virtual ~ErrorInvalidArgValue() {}

	virtual string Msg();	// implemented in error.cpp
};

// Memory Overflow
class ErrorOverflow : public Error
{
public:
	ErrorOverflow(string arg = string("")) : Error("Allocation failed, memory overflow") {}
	virtual ~ErrorOverflow() {}
};

class ErrorSystem : public Error
{
public:
	ErrorSystem(string arg = string("")) : Error("System call failed") {}
	virtual ~ErrorSystem() {}
};

/////////////////////
// Config File Parser
class ConfigFile
{
public:
	string		strDBPath;

	ConfigFile() {}
	~ConfigFile() {}

	void LoadConfig(string conf = string("/etc/internet.conf")) throw (Error);
};

///////////////
// Command Line
class CLPair	// Command Line Pair (bool, string)
{
public:
	bool	bIs;		// is given in command line
	string	strOpt;		// option attached

	CLPair(string s = "") : bIs(false), strOpt(s) {}
	virtual ~CLPair() {}
};

class CLFromList : public CLPair	// Command line pair, where the option must be one from a list
{
public:
	vector<string> vList;

	CLFromList() : CLPair() {}
	virtual ~CLFromList() {}

	// Is the argument is one from the list?
	bool Valid() const;		// implemented in cmdline.cpp
	inline void Add(string val) { vList.push_back(val); }
};

//////////////////////
// Command Line Parser
class CommandLine
{
public:
	// Modifiers
	bool		bHelp;
	bool		bVerbose;
	bool		bQuite;
	bool		bWizard;
	bool		bForce;

	// Create mode
	CLFromList	clDebian;
	CLPair		clISP;
	CLFromList	clMethod;
	CLPair		clModem;
	CLFromList	clIFace;
	CLPair		clDevice;
	CLPair		clUsername;
	CLPair		clServer;
	CLPair		clPasswd;
	CLPair		clName;

	CLPair		clLANIP;
	CLPair		clLANMask;
	CLPair		clLANBroadcast;
	CLPair		clLANGateway;

	// Info mode
	bool		bListISPs;
	bool		bListConnections;
	bool		bShowDefault;
	CLPair		clISPInfo;
	CLPair		clHWInfo;
	CLFromList	clListHWs;

	// Manage mode
	CLPair		clDelete;
	CLPair		clSetDefault;
	CLFromList	clExtract;

	// Use mode
	CLPair		clConnect;
	CLPair		clKill;
	CLPair		clInit;
	CLPair		clBoot;

	// What mode are we in?
	bool		bCreateMode;

	CommandLine();
	~CommandLine() {}

	void Parse(int argc, char *argv[]) throw (Error);
};

// Prototypes
class Authentication;
class Connection;
class Database;
class Dialer;
class Hardware;
class ISP;

// Enums
enum Language			// Database's language
{
	Hebrew,
	English
};

enum HardwareType		// Sub-directories
{
	Broadband,
	ISDN,
	Dialup
};

enum ConnectionMethod
{
	ADSL,
	Cable,
	LANSlave
};

enum SingleInterface
{
	interEthernet,
	interUSB
};

// Description - all the information needed to create a connection
// data must be valid.
struct Description
{
public:
	bool				bDebianBased;
	string				strISP;			// valid C name
	ConnectionMethod	conMethod;
	string				strModem;		// valid realy-realy-realy long name (TODO, make it short)
										// Please make sure you are not using a cable modem with
										// and ADSL connection or vise-versa... that would be funny...
	string				strEth;			// Thernet device in the form of ethn.
	SingleInterface		interInterface;	// If dual
	string				strUsername;
	string				strPasswd;
	string				strServer;		// for special cases, like huji
	string				strConnectionName;

	// LAN stuff
	string				strLANIP;
	string				strLANMask;
	string				strLANBroadcast;
	string				strLANGateway;
	bool				bLANDHCP;

	Description() {}
	~Description() {}
};

// Utilities
bool FileExists(string strFile);
void MakeFromDesc(const Description &desc, const Database &db, const ConfigFile &conf,
	const CommandLine &cmdline) throw (Error);
int DoWizard(const ConfigFile &conf, const CommandLine &cmdline) throw (Error);

// Info
void InfoListISPs(const Database &db) throw (Error);
void InfoListConnections(const ConfigFile &Conf);
void InfoISP(const Database &db, string strISP) throw (Error);
void InfoHW(const Database &db, string strHW) throw (Error);
void InfoListHWs(const Database &db, string strType) throw (Error);
void InfoShowDefault(const ConfigFile &conf) throw (Error);

// Manage
void ManageDelete(const ConfigFile &conf, const CommandLine &cmd, string strCon) throw (Error);
void ManageSetDefault(const ConfigFile &conf, const CommandLine &cmd, string strCon) throw (Error);
void ManageExtract(const ConfigFile &conf, const CommandLine &cmd,
	int argc, char *argv[], string strScript) throw (Error);

// Use - implemented in internet.cpp
void Use(const ConfigFile &conf, const CommandLine &cmd, string strScript, string strCon) throw (Error);

#endif

