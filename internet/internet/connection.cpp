/***************************************************************************
                          connection.cpp  -  description
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
#include <sstream>
#include <fstream>
using namespace std;

#include "connection.h"
#include "parse.h"

Connection::Connection(Hardware *hw, ISP *isp, Authentication *auth, Dialer *dial)
{
	pHardware = hw;
	pISP = isp;
	pAuth = auth;
	pDialer = dial;

	if (!pHardware)	cerr << "ERROR: Invalid hardware module!\n";
	if (!pISP)		cerr << "ERROR: Invalid ISP module!\n";
	if (!pAuth)		cerr << "ERROR: Invalid authentication module!\n";
	if (!pDialer)	cerr << "ERROR: Invalid dialer module!\n";
}

void Connection::MakeScript(ScriptType type) throw (Error)
{
	// Order of execution;
	// Hardware, ISP, Authentication and Dialer.
	ostringstream stream;
	string strName;

	switch (type)
	{
	case Init:
		strName = string("init");

		stream << "#!/bin/bash\n" << endl;

		stream << "### HARDWARE ###" << endl;
		pHardware->MakeInit(stream);
		stream << "### end of HARDWARE ###" << endl;

		stream << "### ISP ###" << endl;
		pISP->MakeInit(stream);
		stream << "### end of ISP ###" << endl;

		stream << "### AUTHENTICATION ###" << endl;
		pAuth->MakeInit(stream);
		stream << "### end of AUTHENTICATION ###" << endl;

		stream << "### DIALER ###" << endl;
		pDialer->MakeInit(stream);
		stream << "### end of DIALER ###" << endl;

		stream << "exit 0";
		break;

	case Boot:
		strName = string("boot");
		
		stream << "#!/bin/bash\n" << endl;

		stream << "### HARDWARE ###" << endl;
		pHardware->MakeBoot(stream);
		stream << "### end of HARDWARE ###" << endl;

		stream << "exit 0";
		break;

	case Connect:
		strName = string("connect");
		
		stream << "#!/bin/bash\n" << endl;

		stream << "### DIALER ###" << endl;
		pDialer->MakeConnect(stream);
		stream << "### end of DIALER ###" << endl;

		stream << "exit 0";
		break;

	case Disconnect:
		strName = string("disconnect");
		
		stream << "#!/bin/bash\n" << endl;

		stream << "### DIALER ###" << endl;
		pDialer->MakeDisconnect(stream);
		stream << "### end of DIALER ###" << endl;

		stream << "exit 0";
		break;
	}

	// Parse stream
	string strScript = Parse(stream.str(), pISP, pAuth, pHardware, pDialer);
	string strCmd;

	if(system("mkdir -p /tmp/iwiz/ > /dev/null") != 0) throw ErrorSystem();
	if (system((string("rm -f /tmp/iwiz/") + strName + string(".sh > /dev/null")).c_str()) != 0)
		throw ErrorSystem();
		
	ofstream script((string("/tmp/iwiz/") + strName + string(".sh")).c_str());
	if (!script) throw Error404(string("/tmp/iwiz/") + strName + string(".sh"));

	script.write(strScript.c_str(), strScript.length());
}

void Connection::Make() throw (Error)
{
	try
	{
		MakeScript(Init);
		MakeScript(Boot);
		MakeScript(Connect);
		MakeScript(Disconnect);
	}

	catch (...)
	{
		throw;
	}
}

void Connection::Install() throw (Error)
{
	ofstream xml("/tmp/iwiz/desc.xml", ios::trunc);
	if (!xml) throw Error404("/tmp/iwiz/desc.xml");

	xml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	xml << "<connection>" << endl;
	xml << "\t" << "<name>" << strName << "</name>" << endl;
	xml << "</connection>" << endl;

	xml.close();

	// compress to tarball and place at <path>/connections/
	string strTar("tar -C /tmp/iwiz/ -czf '");
	strTar += pDialer->getDatabase()->getPath() + string("connections/") + strName + string(".tar.gz' . > /dev/null");
	if (system(strTar.c_str()) != 0) throw ErrorSystem();
}



