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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/utils/utils.h,v 1.2 2005/01/19 21:10:22 z9u2k Exp $

#ifndef CORE_UTILS_UTILS
#define CORE_UTILS_UTILS

#include <string>

namespace core {
    namespace utils {
        /**
         * Resolvs the path to the schema file of the XML in question.
         * It strips down the XML file from the <b>full path</b> given, and
         * uses the directory it is in as the name of the schema.
         *
         * @param xml Full path to the file in question. The file must be in
         *        the database.
         * @return Full path to the validating schema for that file.
         */
        std::string getSchema(const std::string &xml);
    }
}

#endif
