/***************************************************************************
                          isp.h  -  description
                             -------------------
    begin                : Sat Jun 7 2003
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
#ifndef INTERNET_ISP_H_
#define INTERNET_ISP_H_

#include "internet.h"

#include "xml.h"

class Database;
class ISP
{
private:
	string					strName;		// isp::name
	string					strCName;		// isp::cname

	string					strDNS1;		// isp::dns1
	string					strDNS2;		// isp::dns2

	// support
	string					strHomepage;	// isp::homepage
	string					strTech;		// isp::tech
	string					strJoin;		// isp::join

	string					strProxyManual;	// isp::proxy::manual
	string					strProxyAuto;	// isp::proxy::auto

	// email
	string					strPOP3;		// isp::pop3
	string					strIMAP;		// isp::imap
	string					strSMTP;		// isp::smtp
	string					strEMailSuffix;	// isp::emailsuffix

	// Broadband
	string					strCableGateway;		// e.g. cable.netvision.net.il,		isp::cable::gateway
	string					strCableRemotename;		// e.g. cable.netvision.net.il,		isp::cable::remotename
	string					strADSLSuffix;			// isp::adsl::usrsuffix
	string					strCableSuffix;			// isp::cable::usersuffix

	string					strSG;					// Search Group, isp::sg

	map<string, string>		mapISDN;				// Location, Phone
	map<string, string>		mapDialup;				// Location, Phone

	const Database			*const pDB;

	void					ParseSupport(xmlDocPtr doc, xmlNodePtr cur);
	void					ParseEMail(xmlDocPtr doc, xmlNodePtr cur);
	void					ParseBroadband(xmlDocPtr doc, xmlNodePtr cur);
	void					ParseBroadbandGateway(xmlDocPtr doc, xmlNodePtr cur);
	void					ParseISDN(xmlDocPtr doc, xmlNodePtr cur);
	void					ParseDialup(xmlDocPtr doc, xmlNodePtr cur);
	void					ParseProxy(xmlDocPtr doc, xmlNodePtr cur);
protected:
public:

	ISP(const Database *const db);
	~ISP() {}

	inline string				getName()				const { return strName;				}
	inline string				getCName()				const { return strCName;			}
	inline string				getDNS1()				const { return strDNS1;				}
	inline string				getDNS2()				const { return strDNS2;				}
	inline string				getHomepage()			const { return strHomepage;			}
	inline string				getTech()				const { return strTech;				}
	inline string				getJoin()				const { return strJoin;				}
	inline string				getPOP3()				const { return strPOP3;				}
	inline string				getSMTP()				const { return strSMTP;				}
	inline string				getEMailSuffix()		const { return strEMailSuffix;		}
	inline string				getCableGateway()		const { return strCableGateway;		}
	inline string				getCableRemotename()	const { return strCableRemotename;	}
	inline string				getADSLSuffix()			const { return strADSLSuffix;		}
	inline string				getCableSuffix()		const { return strCableSuffix;		}
	inline map<string, string>	getISDNMap()			const { return mapISDN;				}
	inline map<string, string>	getDialupMap()			const { return mapDialup;			}
	inline string				getSG()					const { return strSG;				}
	inline string				getProxyAuto()			const { return strProxyAuto;		}
	inline string				getProxyManual()		const { return strProxyManual;		}
	inline string				getIMAP()				const { return strIMAP;				}

	void LoadISP(string name) throw (Error);
	void MakeInit(ostream &stream);
};

#endif




