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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/xml/CoreErrorHandler.cpp,v 1.2 2005/01/19 21:10:22 z9u2k Exp $

#include "core/xml/CoreErrorHandler.h"
#include "core/utils/Log.h"
#include "core/xml/xml.h"

using namespace xercesc;
using namespace core::utils;
using namespace core::xml;

core::xml::CoreErrorHandler::CoreErrorHandler() : ErrorHandler() {
    resetErrors();
}

core::xml::CoreErrorHandler::~CoreErrorHandler() {
}

void core::xml::CoreErrorHandler::resetErrors() {
    errorCount = 0;
}

void core::xml::CoreErrorHandler::error(const SAXParseException &ex) {
    Log::error(getExceptionString(ex));
    errorCount++;
}

void core::xml::CoreErrorHandler::warning(const SAXParseException &ex) {
    Log::warning(getExceptionString(ex));
    errorCount++;
}

void core::xml::CoreErrorHandler::fatalError(const SAXParseException &ex) {
    Log::fatal(getExceptionString(ex));
    errorCount++;
}
