/***************************************************************************
                          db.h  -  description
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
#ifndef INTERNET_DB_H_
#define INTERNET_DB_H_

#include "internet.h"

class Database
{
private:
	Language		nLang;
	
protected:
public:
	static string	strPath;

	Database(string path, Language lang = English)
	{
		strPath = path;
		nLang = lang;
	}
	
	~Database() {}

	string getISPPath(string strName) const throw (Error);
	string getHWPath(string strName, HardwareType type) const throw (Error);
	string getDialerPath(string strName) const throw (Error);

	vector<string> ListISPs(bool bCNames = false) const throw (Error);
	vector<string> ListHWs(HardwareType ht) const throw (Error);
	vector<string> ListDialers() const throw (Error);

	string getModemByName(string name, HardwareType ht) const throw (Error);
	string ResolveDialer(ISP *isp, Hardware *hw, HardwareType ht) const throw (Error);

	inline Language getLang() const { return nLang;   }
	static string getPath();

	inline void setLang(const Language &lang)	{ nLang = lang;		}
	inline void setPath(const string &path)		{ strPath = path;	}
};

#endif



