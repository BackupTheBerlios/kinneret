/***************************************************************************
 *   Copyright (C) 2005 by Itay 'z9u2K' Duvdevani                          *
 *   itay AT z9u2kHomelinuxCom                                             *
 *   (replace uppercase letters with '.' and lowercase letter)             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/utils/utils.cpp,v 1.2 2005/01/19 21:10:22 z9u2k Exp $

#include "core/utils/utils.h"
#include "core/utils/Config.h"

using namespace core::utils;
using namespace std;

string core::utils::getSchema(const string &xml) {
    // Get the driectory this file is in
    string::size_type lastSlash;
    string::size_type slashBeforeLastSlash;

    lastSlash = xml.rfind("/");
    slashBeforeLastSlash = xml.rfind("/", lastSlash - 1);

    string schmaName = xml.substr(slashBeforeLastSlash,
        lastSlash - slashBeforeLastSlash) + ".xsd";
    return Config::getDatabasePath() + Config::getSchemasDirectoryName() +
        schmaName;
}
