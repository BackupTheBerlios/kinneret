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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/xml/XMLWriteable.h,v 1.5 2005/01/19 21:10:22 z9u2k Exp $

#ifndef XML_WRITEABLE
#define XML_WRITEABLE

#include <xercesc/dom/DOM.hpp>

namespace core {
    namespace xml {
        /**
         * This interface allows the implementing class to be saved to an
         * XML DOM tree.
         *
         * @author z9u2k
         */
        class XMLWriteable {
        public:

            /* --- Constuctors --- */

            XMLWriteable() throw () {
                // Nothing to do
            }

            virtual ~XMLWriteable() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * Saves to a DOM tree.
             *
             * @parm document Document to create elements with.
             * @return Root element of serialization.
             */
            virtual DOMElement *toXML(xercesc::DOMDocument *const document) = 0;
        }
    }
}

#endif
