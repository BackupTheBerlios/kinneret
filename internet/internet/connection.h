/***************************************************************************
                          connection.h  -  description
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
#ifndef INTERNET_CONNECTION_H_
#define INTERNET_CONNECTION_H_

#include <string>
using namespace std;

#include "hardware.h"
#include "isp.h"
#include "authentication.h"
#include "dialer.h"
#include "internet.h"

class Connection
{
private:
	Hardware		*pHardware;
	ISP				*pISP;
	Authentication	*pAuth;
	Dialer			*pDialer;

	string				strName;

	int					MakeConfigScript(string strFile) const;
	int					MakeBootScript(string strFile) const;
	int					MakeConnectScript(string strFile) const;
	int					MakeDisconnectScript(string strFile) const;
protected:
public:
	enum ScriptType
	{
		Init,				// One-time scripts (e.g. pap-secrets)
		Boot,				// Boot-time configuration (e.g. ifconfig eth0 up)
		Connect,
		Disconnect,
		Done
	};

	Connection(Hardware *hw, ISP *isp, Authentication *auth, Dialer *dial);
	~Connection() {}

	// Get/Set
	inline Hardware			*getHardware()	const	{ return pHardware;	}
	inline ISP				*getISP()		const	{ return pISP;		}
	inline Authentication	*getAuth()		const	{ return pAuth;		}
	inline Dialer			*getDialer()	const	{ return pDialer;	}
	inline string			 getName()		const	{ return strName;	}
	
	inline void			setHardware(Hardware *hw)		{ pHardware = hw;	}
	inline void			setISP(ISP *isp)				{ pISP = isp;		}
	inline void			setAuth(Authentication *auth)	{ pAuth = auth;		}
	inline void			setDialer(Dialer *dial)			{ pDialer = dial;	}
	inline void			setName(string name)			{ strName = name;	}

	void			MakeScript(ScriptType type) throw (Error);
	void			Make() throw (Error);			// creates the scripts, the tarball and the xml file
	void			Install() throw (Error);		// executes the init script and installs the boot script
};

#endif



