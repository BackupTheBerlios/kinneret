/***************************************************************************
                          dialer.cpp  -  description
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
#include "internet.h"

#include "dialer.h"

void Dialer::LoadDialer(string strName) throw (Error)
{
	ifstream dialer;
	try
	{
		dialer.open(pDB->getDialerPath(strName).c_str());
	}

	catch (...)
	{
		throw;
	}
	
	if (!dialer) throw Error("Cannot load dialer");

	// copy file's content to string
	char *szDialer = 0;

	// read first line
	string iface;
	dialer >> iface;		// #!ppp0 || #!ippp0
	strIFace = iface.substr(2, iface.length() - 2);

	// get file size for buffer allocation
	dialer.seekg(0, ios_base::end);
	long lSize = dialer.tellg();
	dialer.seekg(0, ios_base::beg);

	// allocate buffer and read it (the #!ppp0 will be in the final script, we can live with that).
	try
	{
		szDialer = new char[lSize + 1];
	}

	catch (bad_alloc)
	{
		dialer.close();
		throw ErrorOverflow();
	}

	dialer.read(szDialer, lSize);
	dialer.close();

	szDialer[lSize] = 0;

	// Clean the string
	long len = lSize - 1;
	while (!isalnum(szDialer[len]))
	{
		szDialer[len] = 0;
		len--;
	}

	strConnect = string(szDialer);
	if (szDialer)
	{
		delete[] szDialer;
		szDialer = 0;
	}

	// Disconnect
	try
	{
		dialer.open((pDB->getDialerPath(strName) + string(".dis")).c_str());
	}

	catch (...)
	{
		throw;
	}
	
	if (!dialer) throw Error("Cannot load dialer");

	// get file size for buffer allocation
	dialer.seekg(0, ios_base::end);
	lSize = dialer.tellg();
	dialer.seekg(0, ios_base::beg);

	// allocate buffer and read it (the #!ppp0 this will be in the final script, we can live with that).
	try
	{
		szDialer = new char[lSize + 1];
	}
	
	catch (bad_alloc)
	{
		dialer.close();
		throw ErrorOverflow();
	}

	dialer.read(szDialer, lSize);
	dialer.close();

	szDialer[lSize] = 0;

	// Clean the string
	len = lSize - 1;
	while (!isalnum(szDialer[len]))
	{
		szDialer[len] = 0;
		len--;
	}

	strDisconnect = string(szDialer);
	if (szDialer)
	{
		delete[] szDialer;
		szDialer = 0;
	}

	// Init
	if (FileExists(pDB->getDialerPath(strName) + string(".init")))
	{
		try
		{
			dialer.open((pDB->getDialerPath(strName) + string(".init")).c_str());
		}

		catch (...)
		{
			throw;
		}

		if (!dialer) throw Error("Cannot load dialer");

		// get file size for buffer allocation
		dialer.seekg(0, ios_base::end);
		lSize = dialer.tellg();
		dialer.seekg(0, ios_base::beg);

		// allocate buffer and read it (the #!ppp0 this will be in the final script, we can live with that).
		try
		{
			szDialer = new char[lSize + 1];
		}

		catch (bad_alloc)
		{
			dialer.close();
			throw ErrorOverflow();
		}

		dialer.read(szDialer, lSize);
		dialer.close();

		szDialer[lSize] = 0;

		// Clean the string
		len = lSize - 1;
		while (!isalnum(szDialer[len]))
		{
			szDialer[len] = 0;
			len--;
		}

		strInit = string(szDialer);
		if (szDialer)
		{
			delete[] szDialer;
			szDialer = 0;
		}
	}

	// Done
	if (FileExists(pDB->getDialerPath(strName) + string(".done")))
	{
		try
		{
			dialer.open((pDB->getDialerPath(strName) + string(".done")).c_str());
		}

		catch (...)
		{
			throw;
		}

		if (!dialer) throw Error("Cannot load dialer");

		// get file size for buffer allocation
		dialer.seekg(0, ios_base::end);
		lSize = dialer.tellg();
		dialer.seekg(0, ios_base::beg);

		// allocate buffer and read it (the #!ppp0 this will be in the final script, we can live with that).
		try
		{
			szDialer = new char[lSize + 1];
		}

		catch (bad_alloc)
		{
			dialer.close();
			throw ErrorOverflow();
		}

		dialer.read(szDialer, lSize);
		dialer.close();

		szDialer[lSize] = 0;

		// Clean the string
		len = lSize - 1;
		while (!isalnum(szDialer[len]))
		{
			szDialer[len] = 0;
			len--;
		}

		strDone = string(szDialer);
		if (szDialer)
		{
			delete[] szDialer;
			szDialer = 0;
		}
	}
}

void Dialer::MakeConnect(ostream &stream) const
{
	string strCode = strConnect;
	
	// Parse string for debian/non-debian
	while (strCode.find("{*") != string::npos)
	{
		string::size_type st = strCode.find("{*");
		string::size_type en = strCode.find("*}");

		string block = strCode.substr(st + 2, en - st - 2);
	
		string code;
		string strBlock = bDebian ? "%debian%" : "%non_debian%";

		string::size_type debian_block = block.find(strBlock);
		string strDebianBlock = block.substr(debian_block);

		string::size_type dst = strDebianBlock.find("{");
		string::size_type den = strDebianBlock.find("};");

		code  = strDebianBlock.substr(dst + 1, den - dst - 1);

		strCode.replace(st, en - st + 2, code);
	}

	// Out parsed stream
	stream << strCode << endl;
}

void Dialer::MakeDisconnect(ostream &stream) const
{
	string strCode = strDisconnect;

	// Parse string for debian/non-debian
	while (strCode.find("{*") != string::npos)
	{
		string::size_type st = strCode.find("{*");
		string::size_type en = strCode.find("*}");

		string block = strCode.substr(st + 2, en - st - 2);

		string code;
		string strBlock = bDebian ? "%debian%" : "%non_debian%";

		string::size_type debian_block = block.find(strBlock);
		string strDebianBlock = block.substr(debian_block);

		string::size_type dst = strDebianBlock.find("{");
		string::size_type den = strDebianBlock.find("};");

		code  = strDebianBlock.substr(dst + 1, den - dst - 1);

		strCode.replace(st, en - st + 2, code);
	}

	// Out parsed stream
	stream << strCode << endl;
}

void Dialer::MakeInit(ostream &stream) const
{
	string strCode = strInit;

	// Parse string for debian/non-debian
	while (strCode.find("{*") != string::npos)
	{
		string::size_type st = strCode.find("{*");
		string::size_type en = strCode.find("*}");

		string block = strCode.substr(st + 2, en - st - 2);

		string code;
		string strBlock = bDebian ? "%debian%" : "%non_debian%";

		string::size_type debian_block = block.find(strBlock);
		string strDebianBlock = block.substr(debian_block);

		string::size_type dst = strDebianBlock.find("{");
		string::size_type den = strDebianBlock.find("};");

		code  = strDebianBlock.substr(dst + 1, den - dst - 1);

		strCode.replace(st, en - st + 2, code);
	}

	// Out parsed stream
	stream << strCode << endl;
}

void Dialer::MakeBoot(ostream &stream) const { stream << endl; }
void Dialer::MakeDone(ostream &stream) const
{
	string strCode = strDone;

	// Parse string for debian/non-debian
	while (strCode.find("{*") != string::npos)
	{
		string::size_type st = strCode.find("{*");
		string::size_type en = strCode.find("*}");

		string block = strCode.substr(st + 2, en - st - 2);

		string code;
		string strBlock = bDebian ? "%debian%" : "%non_debian%";

		string::size_type debian_block = block.find(strBlock);
		string strDebianBlock = block.substr(debian_block);

		string::size_type dst = strDebianBlock.find("{");
		string::size_type den = strDebianBlock.find("};");

		code  = strDebianBlock.substr(dst + 1, den - dst - 1);

		strCode.replace(st, en - st + 2, code);
	}

	// Out parsed stream
	stream << strCode << endl;
}



