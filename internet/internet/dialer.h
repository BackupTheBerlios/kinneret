/***************************************************************************
                          dialer.h  -  description
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
#ifndef INTERNET_DIALER_H_
#define INTERNET_DIALER_H_

#include "internet.h"

#include "isp.h"
#include "authentication.h"
#include "hardware.h"
#include "db.h"

class Dialer
{
private:
	const Database	*const pDB;
	
	string		strConnect;
	string		strDisconnect;
	string		strInit;
	string		strIFace;		// ppp0 || ippp0 (from the dialer's first line), dialer::iface
	
	bool		bDebian;
protected:
public:
	Dialer(const Database *const db) : pDB(db), bDebian(true) {}
	~Dialer() {}

	void LoadDialer(string strName) throw (Error);

	inline const Database *const getDatabase() { return pDB; }
	inline string getIFace() const { return strIFace; }
	inline bool getDebian() const { return bDebian; }
	inline void setDebian(const bool &d) { bDebian = d; }

	void MakeInit(ostream &stream) const;
	void MakeConnect(ostream &stream) const;
	void MakeDisconnect(ostream &stream) const;
};

#endif



