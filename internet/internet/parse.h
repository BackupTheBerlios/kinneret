/***************************************************************************
                          parse.h  -  description
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
#ifndef INTERNET_PARSE_H_
#define INTERNET_PARSE_H_

#include <string>
using namespace std;

#include "isp.h"
#include "hardware.h"
#include "authentication.h"
#include "dialer.h"

string Parse(string str, ISP *isp, Authentication *auth, Hardware *hw, Dialer *dial);

#endif



