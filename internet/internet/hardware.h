/***************************************************************************
                          hardware.h  -  description
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
#ifndef INTERNET_HARDWARE_H_
#define INTERNET_HARDWARE_H_

#include <iostream>
#include <string>
using namespace std;

#include "isp.h"
#include "db.h"

class Database;
class Hardware
{
private:
protected:
	string			strName;
	const Database	*const pDB;

	ConnectionMethod	moType;	
public:
	// Major type: BB, ISDN || Diaul,
	// Minor type: interface, driver etc
	enum MinorType
	{
		// BroadBand
		BBEth,
		BBUSB,
		BBDual,

		// ISDN
		ISDN,
		
		// Dialup
		Dialup,

		// Unknown
		Unknown
	};
	
	Hardware(const Database *const db) throw (Error) : strName(""), pDB(db) {}
	virtual ~Hardware() {}

	virtual void MakeInit(ostream &stream) const = 0;
	virtual void MakeBoot(ostream &stream) const = 0;

	virtual void Load(string strName) throw (Error) = 0;

	virtual string getName()				const { return strName; }
	inline ConnectionMethod getModemType()	const { return moType;  }
};

Hardware::MinorType getHardwareType(string name, HardwareType ht, const Database *const pDB) throw (Error);

class Ethernet : public Hardware
{
public:
	enum TunnelingType
	{
		PPtP,
		PPPoE
	};

	struct AddressMethod
	{
		string		strIP;
		string		strMask;
		string		strBroadcast;
		string		strGateway;

		AddressMethod() : strIP(""), strMask(""), strBroadcast(""), strGateway("") {}
		~AddressMethod() {}
	};
	
private:
protected:
	string				strEth;		// "eth0", "eth1" etc.
	TunnelingType		conType;
	AddressMethod		ipInterface;

	string				strIP;
	string				strRemotename;
	
public:
	Ethernet(const Database *const db) throw (Error) :
		Hardware(db),
		strEth(""),
		ipInterface(),
		strIP(""),
		strRemotename("") {}
	virtual ~Ethernet() {}

	virtual void MakeInit(ostream &stream) const;
	virtual void MakeBoot(ostream &stream) const;

	virtual void Load(string name) throw (Error);

	inline string getEth() const { return strEth; }
	inline void setEth(const string &e) { strEth = e; }

	inline TunnelingType getVPNType()		const { return conType;						}
	inline string getIfaceIP()				const { return ipInterface.strIP;			}
	inline string getIfaceMask()			const { return ipInterface.strMask;			}
	inline string getIfaceBroadcast()		const { return ipInterface.strBroadcast;	}
	inline string getIfaceGateway()			const { return ipInterface.strGateway;		}
	inline string getIP()					const { return strIP;						}
	inline string getRemotename()			const { return strRemotename;				}
};

class USB : public Ethernet
{
private:
	string	strDriver;		// module name to probe
protected:
public:

	USB(const Database *const db) throw (Error) : Ethernet(db), strDriver("") {}
	virtual ~USB() {}

	virtual void MakeInit(ostream &stream) const;
	virtual void MakeBoot(ostream &stream) const;

	virtual void Load(string strName) throw (Error);

	inline string getDriver() const { return strDriver; }
};

class LAN : public Hardware
{
public:
private:
protected:
	bool						bDHCP;
	string						strEth;		// "eth0", "eth1" etc.
	Ethernet::AddressMethod		ifaceIP;

public:
	LAN(const Database *const db) throw (Error) :
		Hardware(db),
		bDHCP(false),
		strEth(""),
		ifaceIP() {}
	virtual ~LAN() {}

	virtual void MakeInit(ostream &stream) const;
	virtual void MakeBoot(ostream &stream) const;

	virtual void Load(string strName) throw (Error) { if (0) { cout << strName; } }

	inline string getEth() const { return strEth; }
	inline void setEth(const string &e) { strEth = e; }

	inline bool getDHCP() const { return bDHCP; }
	inline void setDHCP(const bool &d) { bDHCP = d; }

	inline string getIP()				const { return ifaceIP.strIP;			}
	inline string getMask()				const { return ifaceIP.strMask;			}
	inline string getBroadcast()		const { return ifaceIP.strBroadcast;	}
	inline string getGateway()			const { return ifaceIP.strGateway;		}

	inline void setIP(const string &s)			{ ifaceIP.strIP			= s; }
	inline void setMask(const string &s)		{ ifaceIP.strMask		= s; }
	inline void setBroadcast(const string &s)	{ ifaceIP.strBroadcast	= s; }
	inline void setGateway(const string &s)		{ ifaceIP.strGateway	= s; }
};

#endif



