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
#include "db.h"

Connection::Connection(Hardware *hw, ISP *isp, Authentication *auth, Dialer *dial)
{
	pHardware = hw;
	pISP = isp;
	pAuth = auth;
	pDialer = dial;
}

void Connection::MakeScript(ScriptType type) throw (Error)
{
	// Order of execution;
	// Hardware, ISP, Authentication and Dialer.
	ostringstream stream;
	string strName;

	const int nModules = 4;
	const Module *pModules[] =
	{
		pHardware, pISP, pAuth, pDialer
	};

	const char *Names[] =
	{
		"Hardware", "ISP", "Authentication", "Dialer"
	};

	switch (type)
	{
	case Init:
		strName = string("init");

		stream << "#!/bin/bash" << endl;
		break;

	case Boot:
		strName = string("boot");

		stream << "#!/bin/bash" << endl;
		break;

	case Connect:
		strName = string("connect");
		
		stream << "#!/bin/bash\n" << endl;

		stream << "### init ###" << endl;
		for (int i = 0 ; i < nModules ; i++)
		{
			if (pModules[i])
			{
				stream << "### " << Names[i] << " (init) ###" << endl;
				pModules[i]->MakeInit(stream);
				stream << "### end of " << Names[i] << " ###\n" << endl;
			}
			else stream << "### Skipping " << Names[i] << " (init) ###\n" << endl;
		}

		stream << "### boot ###" << endl;
		for (int i = 0 ; i < nModules ; i++)
		{
			if (pModules[i])
			{
				stream << "### " << Names[i] << " (boot) ###" << endl;
				pModules[i]->MakeBoot(stream);
				stream << "### end of " << Names[i] << " ###\n" << endl;
			}
			else stream << "### Skipping " << Names[i] << " (boot) ###\n" << endl;
		}

		stream << "### connect ###" << endl;
		for (int i = 0 ; i < nModules ; i++)
		{
			if (pModules[i])
			{
				stream << "### " << Names[i] << " (connect) ###" << endl;
				pModules[i]->MakeConnect(stream);
				stream << "### end of " << Names[i] << " ###\n" << endl;
			}
			else stream << "### Skipping " << Names[i] << " (connect) ###\n" << endl;
		}

		break;

	case Disconnect:
		strName = string("disconnect");

		stream << "#!/bin/bash\n" << endl;

		stream << "### disconnect ###" << endl;
		for (int i = 0 ; i < nModules ; i++)
		{
			if (pModules[i])
			{
				stream << "### " << Names[i] << " (disconnect) ###" << endl;
				pModules[i]->MakeDisconnect(stream);
				stream << "### end of " << Names[i] << " ###\n" << endl;
			}
			else stream << "### Skipping " << Names[i] << " (disconnect) ###\n" << endl;
		}

		stream << "### done ###" << endl;
		for (int i = 0 ; i < nModules ; i++)
		{
			if (pModules[i])
			{
				stream << "### " << Names[i] << " (done) ###" << endl;
				pModules[i]->MakeDone(stream);
				stream << "### end of " << Names[i] << " ###\n" << endl;
			}
			else stream << "### Skipping " << Names[i] << " (done) ###\n" << endl;
		}
		break;
		
	case Done:
		strName = string("done");

		stream << "#!/bin/bash\n" << endl;
		break;
	}

	stream << "exit 0";

	// Parse stream
	string strScript = Parse(stream.str(), pISP, pAuth, pHardware, pDialer);
	string strCmd;

	if(system("mkdir -p /tmp/iwiz/ > /dev/null") != 0) throw ErrorSystem();
	if (system((string("rm -f /tmp/iwiz/") + strName + string(".sh > /dev/null")).c_str()) != 0)
		throw ErrorSystem();
		
	ofstream script((string("/tmp/iwiz/") + strName + string(".sh")).c_str());
	if (!script) throw Error404(string("/tmp/iwiz/") + strName + string(".sh"));

	script.write(strScript.c_str(), strScript.length());

	strCmd = "chmod +x /tmp/iwiz/" + strName + ".sh";
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();
}

void Connection::Make() throw (Error)
{
	try
	{
		MakeScript(Init);
		MakeScript(Boot);
		MakeScript(Connect);
		MakeScript(Disconnect);
//		MakeScript(Done);
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
	strTar += Database::getPath() + string("connections/") + strName + string(".tar.gz' . > /dev/null");
	if (system(strTar.c_str()) != 0) throw ErrorSystem();
}



