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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/utils/Log.cpp,v 1.3 2005/01/19 21:30:50 z9u2k Exp $

#include <iostream>

#include "Log.h"

using namespace std;
using namespace core::utils;

// The instance
Log *Log::instance;

Log::Log(int level) {
    logLevel = level;
}

void Log::create(int level) {
    instance = new Log(level);
}

void Log::release() {
    delete instance;
}

void Log::log(int level, const std::string &msg) {
    if (level >= logLevel) {
        cerr << msg << endl;
    }
}

void Log::bug(const std::string &msg) {
    instance->log(BUG, "BUG > " + msg);
}

void Log::fatal(const std::string &msg) {
    instance->log(FATAL, "FATAL > " + msg);
}

void Log::error(const std::string &msg) {
    instance->log(ERROR, "ERROR > " + msg);
}

void Log::warning(const std::string &msg) {
    instance->log(WARNING, "WARNING > " + msg);
}

void Log::info(const std::string &msg) {
    instance->log(INFO, "INFO > " + msg);
}

void Log::verbose(const std::string &msg) {
    instance->log(VERBOSE, "VERBOSE > " + msg);
}
