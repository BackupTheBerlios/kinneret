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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/xml/XMLReadable.h,v 1.3 2005/01/19 21:10:22 z9u2k Exp $

#ifndef XML_READABLE
#define XML_READABLE

#include <xercesc/dom/DOM.hpp>

#include "../exception/exception.h"

namespace core {
    namespace xml {
        /**
         * This interface allows the implementing class to be loaded from an
         * XML DOM tree.
         *
         * @author z9u2k
         */
        class XMLReadable {
        public:

            /* --- Constuctors --- */

            XMLReadable() throw () {
                // Nothing to do
            }

            virtual ~XMLReadable() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * Loads from a DOM tree.
             *
             * @parm root Root elemnt of the document.
             * @throws InvalidFormatException When the XML is of an invalid
             *         format and the class cannot load from it.
             */
            virtual void fromXML(const xercesc::DOMElement *const root)
                throw (exception::InvalidFormatException) = 0;
        };
    }
}

#endif
