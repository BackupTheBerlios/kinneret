/***************************************************************************
                          manage.cpp  -  description
                             -------------------
    begin                : Sun Jul 20 2003
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

void ManageDelete(const ConfigFile &conf, const CommandLine &cmd, string strCon) throw (Error)
{
	if (strCon == "default") throw Error("You cannot delete 'default'");

	string file = conf.strDBPath + "connections/" + strCon + ".tar.gz";
	if (!FileExists(file)) throw Error("Invalid connection. use -C to list connections");

	if (!cmd.bForce)
	{
		char ans;
		do
		{
			cout << "Are you sure you want to delete " << strCon << " [yn]? ";
			cin >> ans;
			if (ans == 'n' || ans == 'N') return;
		} while (ans != 'y' && ans != 'Y');
	}

	string strCmd = "rm -f '" + conf.strDBPath + "connections/" + strCon + ".tar.gz'";
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	// see if we've deleted the default connection
	file = conf.strDBPath + "connections/default.tar.gz";
	if (!FileExists(file))
	{
		if (!cmd.bQuite) cout << "WARNING: You have deleted the 'default' connection.\n";
		strCmd = "rm -f '" + conf.strDBPath + "connections/default.tar.gz'";
		if (system(strCmd.c_str()) != 0) throw ErrorSystem();
	}
}

void ManageSetDefault(const ConfigFile &conf, const CommandLine &cmd, string strCon) throw (Error)
{
	// make sure connection exists
	string file = conf.strDBPath + "connections/" + strCon + ".tar.gz";
	if (!FileExists(file)) throw Error404(file);

	string c;

	// delete default
	if (FileExists(conf.strDBPath + "connections/default.tar.gz"))
	{
		if (cmd.bVerbose) cout << "Deleting old 'default'...\n";
		c = "rm -f '" + conf.strDBPath + "connections/default.tar.gz'";
		if (system(c.c_str()) != 0) throw ErrorSystem();
	}

	// re-create
	if (cmd.bVerbose) cout << "(Re)Creating 'default'...\n";
	c = "ln -s '" + conf.strDBPath + "connections/" + strCon + ".tar.gz' '" + conf.strDBPath + "connections/default.tar.gz'";
	if (system(c.c_str()) != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "'default' connection set to " << strCon << endl;

	cout << endl;
}

void ManageClearCurrent(const ConfigFile &conf, const CommandLine &cmd) throw (Error) {
    // remove 'current'
    if (cmd.bVerbose) cout << "Removing 'current'...\n";
    string file = conf.strDBPath + "connections/current.tar.gz";
    string strCmd = "unlink " + file;
    if (system(strCmd.c_str()) != 0) throw ErrorSystem();
}

void ManageSetCurrent(const ConfigFile &conf, const CommandLine &cmd, string strCon) throw (Error)
{
	// make sure connection exists
	string file = conf.strDBPath + "connections/" + strCon + ".tar.gz";
	if (!FileExists(file)) throw Error404(file);

	string c;

	// delete default
	if (FileExists(conf.strDBPath + "connections/current.tar.gz"))
	{
		if (cmd.bVerbose) cout << "Deleting old 'current'...\n";
		c = "rm -f '" + conf.strDBPath + "connections/current.tar.gz'";
		if (system(c.c_str()) != 0) throw ErrorSystem();
	}

	// re-create
	if (cmd.bVerbose) cout << "(Re)Creating 'current'...\n";
	c = "ln -s '" + conf.strDBPath + "connections/" + strCon + ".tar.gz' '" + conf.strDBPath + "connections/current.tar.gz'";
	if (system(c.c_str()) != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "'current' connection set to " << strCon << endl;

	cout << endl;
}

void ManageExtract(const ConfigFile &conf, const CommandLine &cmd,
	int argc, char *argv[], string strScript) throw (Error)
{
	string strCon(""), strFile("");
	// `thou shalt not parse the command line by yourself`,
	// forgive me father, for I sined...
	for (int j = 1 ; j < argc ; j++)
	{
		if (strstr(argv[j], "--extract="))
		{
			// argv[j] = --extract=type
			// argv[j + 1] = script
			// argv[j + 2] = file
			strCon = string(argv[j + 1]);
			strFile = string(argv[j + 2]);
		}

		else if (strstr(argv[j], "--extract"))
		{
			// argv[j] = --extract
			// argv[j + 1] = type
			// argv[j + 2] = script
			// argv[j + 3] = file
			strCon = string(argv[j + 2]);
			strFile = string(argv[j + 3]);
		}
	}

	if (strCon.empty() || strFile.empty())
	{
		PrintHelp();
		throw Error("Cannot resolve connection name or file name");
	}

	if (cmd.bVerbose) cout << "Extracting " << strScript << ".sh from " << strCon << " to " << strFile << endl;

	// Verify connection's name
	if (cmd.bVerbose) cout << "Making sure connection exists...\n";
	string file = conf.strDBPath + "connections/" + strCon + ".tar.gz";
	if (!FileExists(file)) throw Error("No such connection, use -C to list connections.");

	if (cmd.bVerbose) cout << "Cleaning and re-creating /tmp/iwiz/...\n";
	if (system("rm -fr /tmp/iwiz/ 2>&1 > /dev/null") != 0) throw ErrorSystem();
	if (system("mkdir -p /tmp/iwiz/ 2>&1 > /dev/null") != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "Extracting script to /tmp/iwiz/...\n";
	string strCmd = "tar -C /tmp/iwiz/ -xzf '" + file + "' ./" + strScript + ".sh";
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "Copying script...\n";
	strCmd = "cp /tmp/iwiz/" + strScript + ".sh " + strFile;
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	if (cmd.bVerbose) cout << "Changing premission...\n";
	strCmd = "chmod +x '" + strFile + "'";
	if (system(strCmd.c_str()) != 0) throw ErrorSystem();

	cout << endl;
}

