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

#include "core/utils/xts.h"

using namespace std;
using namespace xercesc;

core::utils::xts::xts(const string &str) {
    xmlString = XMLString::transcode(str.c_str());
    cString = 0;
}

core::utils::xts::xts(const XMLCh *str, bool trim) {
    if (trim) {
        XMLCh *replicate = XMLString::replicate(str);
        XMLString::trim(replicate);
        cString = XMLString::transcode(replicate);
        XMLString::release(&replicate);
    } else {
        cString = XMLString::transcode(str);
    }

    xmlString = 0;
}
            
core::utils::xts::~xts() {
    if (xmlString != 0) {
        XMLString::release(&xmlString);
    }

    if (cString != 0) {
        XMLString::release(&cString);
    }
}

string core::utils::xts::asString() const {
    return string(cString);
}

