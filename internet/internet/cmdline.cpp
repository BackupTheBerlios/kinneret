/***************************************************************************
                          cmdline.cpp  -  description
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
#include "help.h"

bool CLFromList::Valid() const
{
	vector<string>::const_iterator iter;
	for (iter = vList.begin() ; iter != vList.end() ; iter++)
		if (strOpt == *iter) return true;
	
	return false;
}

CommandLine::CommandLine() :
	bHelp(false),
	bVerbose(false),
	bQuite(false),
	bWizard(false),
	bForce(false),
	clDebian(),
	clISP(),
	clMethod(),
	clModem(),
	clIFace(),
	clDevice(),
	clUsername(),
	clServer(),
	clPasswd(),
	clName(),
	clLANIP(),
	clLANMask("255.255.255.0"),
	clLANBroadcast("255.255.255.255"),
	clLANGateway("192.168.0.1"),
	clMyArea(),
	clPhoneNumber(),
	bListISPs(false),
	bListConnections(false),
	bShowDefault(false),
	clISPInfo(),
	clHWInfo(),
	clListHWs(),
	clDelete(),
	clSetDefault(),
	clExtract(),
	clConnect(),
	clKill(),
	clInit(),
	clBoot()
{
	clDebian.Add("yes");
	clDebian.Add("no");

	clMethod.Add("adsl");
	clMethod.Add("cable");
	clMethod.Add("lan");
	clMethod.Add("dialup");

	clIFace.Add("eth");
	clIFace.Add("usb");

	clListHWs.Add("broadband");
	clListHWs.Add("isdn");
	clListHWs.Add("dialup");

	clExtract.Add("init");
	clExtract.Add("boot");
	clExtract.Add("connect");
	clExtract.Add("disconnect");

	clMyArea.Add("02");
	clMyArea.Add("03");
	clMyArea.Add("04");
	clMyArea.Add("06");
	clMyArea.Add("07");
	clMyArea.Add("08");
	clMyArea.Add("09");
}

void CommandLine::Parse(int argc, char *argv[]) throw (Error)
{
	const option long_options[] =
	{
		// NOTE: the numbers are not by order bacause I forst
		// wrote all the options, then grouped them...
		
		// Modifiers
		{ "help",			0, 0, 'h'  },
		{ "version",		0, 0, 'V'  },
		{ "verbose",		0, 0, 'v'  },
		{ "quite",			0, 0, 'q'  },
		{ "wizard",			0, 0, 'w'  },
		{ "force",			0, 0, 'f'  },

		// Create a connection
		{ "debian",			1, 0, 'b'  },
		{ "isp",			1, 0, 'i'  },
		{ "method",			1, 0, 'm'  },
		{ "dialer",			1, 0, 'a'  },
		{ "modem",			1, 0, 'M'  },
		{ "iface",			1, 0, 0x09 },
		{ "dev",			1, 0, 'd'  },
		{ "username",		1, 0, 'u'  },
		{ "server",			1, 0, 0x0C },
		{ "passwd",			1, 0, 'p'  },
		{ "name",			1, 0, 'n'  },

		{ "ip",				1, 0, 0x0D },
		{ "mask",			1, 0, 0x0E },
		{ "broadcast",		1, 0, 0x0F },
		{ "gateway",		1, 0, 0x10 },

		{ "myarea",			1, 0, 0x11 },
		{ "phonenumber",	1, 0, 0x12 },

		// Get information
		{ "listisps",		0, 0, 'l'  },
		{ "listcons",		0, 0, 'C'  },
		{ "listhws",		1, 0, 'H'  },
		{ "hwinfo",			1, 0, 0x0A },
		{ "ispinfo",		1, 0, 0x0B },

		// Manage connections
		{ "defaultshow",	0, 0, 0x03 },
		{ "delete",			1, 0, 0x01 },
		{ "default",		1, 0, 0x02 },
		{ "extract",		1, 0, 0x08 },

		// Use connections
		{ "connect",		2, 0, 0x04 },
		{ "kill",			2, 0, 0x05 },
		{ "init",			2, 0, 0x06 },
		{ "boot",			2, 0, 0x07 },

		// Terminate
		{ 0,				0, 0,  0   }
	};
	const char *short_options = "hVvqwb:i:m:a:M:d:u:p:n:lH:Cc::k::f";

	// Let's parse the command line!
	int next_opt;
	do
	{
		next_opt = getopt_long(argc, argv, short_options, long_options, 0);
		switch (next_opt)
		{
		case '?':
		case 'h':	// help
			PrintHelp();
			exit(0);
			break;	// we don't really need this break... but what heck :)

		// So this way of writing switch statement is non-standart,
		// but it makes the code look much better ;)
		case 'V':
			cout << "Israeli Internet Tool " << VERSION << "." << endl;
			break;
			
		case 'v':  bVerbose				= true;										break;
		case 'q':  bQuite				= true;										break;
		case 'w':  bWizard				= true;										break;
		case 'b':  clDebian.bIs			= true; clDebian.strOpt			= optarg;	break;
		case 'i':  clISP.bIs			= true; clISP.strOpt			= optarg;	break;
		case 'm':  clMethod.bIs			= true; clMethod.strOpt			= optarg;	break;
		case 'M':  clModem.bIs			= true; clModem.strOpt			= optarg;	break;
		case 'd':  clDevice.bIs			= true; clDevice.strOpt			= optarg;	break;
		case 'u':  clUsername.bIs		= true; clUsername.strOpt		= optarg;	break;
		case 0x0C: clServer.bIs			= true; clServer.strOpt			= optarg;	break;
		case 'p':  clPasswd.bIs			= true; clPasswd.strOpt			= optarg;	break;
		case 'n':  clName.bIs			= true; clName.strOpt			= optarg;	break;

		case 0x0D: clLANIP.bIs			= true; clLANIP.strOpt			= optarg;	break;
		case 0x0E: clLANMask.bIs		= true; clLANMask.strOpt		= optarg;	break;
		case 0x0F: clLANBroadcast.bIs	= true; clLANBroadcast.strOpt	= optarg;	break;
		case 0x10: clLANGateway.bIs		= true; clLANGateway.strOpt		= optarg;	break;

		case 0x11: clMyArea.bIs			= true; clMyArea.strOpt			= optarg;	break;
		case 0x12: clPhoneNumber.bIs	= true; clPhoneNumber.strOpt	= optarg;	break;
		
		case 'l':  bListISPs			= true;										break;
		case 'H':  clListHWs.bIs		= true; clListHWs.strOpt		= optarg;	break;
		case 'C':  bListConnections		= true;										break;
		case 'f':  bForce				= true;										break;
		case 0x08: clExtract.bIs		= true; clExtract.strOpt		= optarg;	break;
		case 0x01: clDelete.bIs			= true; clDelete.strOpt			= optarg;	break;
		case 0x02: clSetDefault.bIs		= true; clSetDefault.strOpt		= optarg;	break;
		case 0x03: bShowDefault			= true;										break;
		case 0x09: clIFace.bIs			= true; clIFace.strOpt			= optarg;	break;
		case 0x0A: clHWInfo.bIs			= true; clHWInfo.strOpt			= optarg;	break;
		case 0x0B: clISPInfo.bIs		= true; clISPInfo.strOpt		= optarg;	break;

		// Special cases, optarg can be null, set to default
		case 0x04: clConnect.bIs	= true; clConnect.strOpt	= optarg ? optarg : string("default"); break;
		case 0x05: clKill.bIs		= true; clKill.strOpt		= optarg ? optarg : string("default"); break;
		case 0x06: clInit.bIs		= true; clInit.strOpt		= optarg ? optarg : string("default"); break;
		case 0x07: clBoot.bIs		= true; clBoot.strOpt		= optarg ? optarg : string("default"); break;

		case -1:
			break;

		default:
			// If we get here, something is REALLY wrong...
			throw Error("Command line parsing failed, aborting");
			break;
		}
	}
	while (next_opt != -1);

	// Now, validate command line

	// we can't be verbose and quite at the same time... quite wins!
	// (that's because that in quite mode less code gets exectued => less
	// chances for someone to catch on of my really stupid bugs :)
	if (bQuite) bVerbose = false;

	// Create mode is not any-other-mode, meaning, if we are in create mode,
	// we must supply all required arguments and a connection will be created,
	// that's means we are not in manage mode, or info mode.
	bCreateMode = true;

	if (bWizard) bCreateMode = false;

	// Info mode
	if (bListISPs || bListConnections) bCreateMode = false;
	if (clISPInfo.bIs || clHWInfo.bIs) bCreateMode = false;
	if (clListHWs.bIs)
	{
		bCreateMode = false;
		if (!clListHWs.Valid()) throw ErrorInvalidArgValue("listhws", clListHWs.vList);
	}

	// Manage mode
	if (bShowDefault) bCreateMode = false;
	if (clDelete.bIs || clSetDefault.bIs) bCreateMode = false;
	if (clExtract.bIs)
	{
		bCreateMode = false;
		if (!clExtract.Valid()) throw ErrorInvalidArgValue("extract", clExtract.vList);
	}

	// Use mode
	if (clConnect.bIs || clKill.bIs || clInit.bIs || clBoot.bIs) bCreateMode = false;

	// Create mode
	if (bCreateMode)
	{
		if (!clMethod.Valid())	throw ErrorInvalidArgValue("method", clMethod.vList);
		if (!clDebian.Valid())	throw ErrorInvalidArgValue("debian", clDebian.vList);
		if (!clName.bIs)		throw ErrorMissingArg("name");
		
		if (clMethod.strOpt == string("adsl") || clMethod.strOpt == string("cable"))
		{
			// Validate lists if we are not in any mode
			if (!clISP.bIs)			throw ErrorMissingArg("isp");
			if (!clModem.bIs)		throw ErrorMissingArg("modem");
			if (!clDevice.bIs)		throw ErrorMissingArg("dev");
			if (!clUsername.bIs)	throw ErrorMissingArg("username");
			if (!clPasswd.bIs)		throw ErrorMissingArg("passwd");
			
			if (clIFace.bIs && !clIFace.Valid())
				throw ErrorInvalidArgValue("iface", clIFace.vList);
		}

		else if (clMethod.strOpt == string("lan"))
		{
			// Validate lists if we are not in any mode
			if (!clLANIP.bIs)		throw ErrorMissingArg("ip");
			if (!clISP.bIs)			throw ErrorMissingArg("isp");
			if (!clDevice.bIs)		throw ErrorMissingArg("dev");
		}

		else if (clMethod.strOpt == string("dialup"))
		{
			// Validate lists if we are not in any mode
			if (!clMyArea.bIs)		throw ErrorMissingArg("myarea");
			if (!clPhoneNumber.bIs)	throw ErrorMissingArg("phonenumber");
			if (!clUsername.bIs)	throw ErrorMissingArg("username");
			if (!clPasswd.bIs)		throw ErrorMissingArg("passwd");

			if (!clMyArea.Valid()) throw ErrorInvalidArgValue("myarea", clMyArea.vList);

			// Validate phone number
			// 0-1: digit
			// 2: '-'
			// 3-9: digit
			if (clPhoneNumber.strOpt.length() != 10 ||
				!isdigit(clPhoneNumber.strOpt[0]) || !isdigit(clPhoneNumber.strOpt[1]) ||
				clPhoneNumber.strOpt[2] != '-' ||
				!isdigit(clPhoneNumber.strOpt[3]) || !isdigit(clPhoneNumber.strOpt[4]) ||
				!isdigit(clPhoneNumber.strOpt[5]) || !isdigit(clPhoneNumber.strOpt[6]) ||
				!isdigit(clPhoneNumber.strOpt[7]) || !isdigit(clPhoneNumber.strOpt[8]) ||
				!isdigit(clPhoneNumber.strOpt[9])) throw Error("--phonenumber must be of the form: nn-nnnnnnn");
		}
	}
}

