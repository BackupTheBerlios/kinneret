/***************************************************************************
                          authentication.h  -  description
                             -------------------
    begin                : Thu Jun 12 2003
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
#ifndef INTERNET_AUTH_H_
#define INTERNET_AUTH_H_

#include <iostream>
#include <string>
using namespace std;

class Authentication
{
private:
	string		strUsername;		// auth::usr
	string		strPasswd;			// auth::passwd
protected:
public:

	Authentication() {}
	Authentication(string usr, string passwd)
	{
		strUsername = usr;
		strPasswd = passwd;
	}
	~Authentication() {}

	string getUsername()	const { return strUsername;	}
	string getPasswd()		const { return strPasswd;	}

	void MakeInit(ostream &stream);
};

#endif



