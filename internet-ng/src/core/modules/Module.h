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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/modules/Module.h,v 1.3 2005/01/19 21:30:50 z9u2k Exp $

#ifndef CORE_MODULE
#define CORE_MODULE

#include "xml/XMLReadable.h"

namespace core {
    namespace modules {
        /**
         * This abstract class represents a module that is loadable from an XML
         * file.
         * 
         * @author: z9u2k
         */
        class Module : public XMLReadable {
        public:

            /* --- Constructors --- */

            /**
             * TODO: JavaDocs!
             */
            Module() throw () {
                // Nothing to do
            }

            /**
             * TODO: JavaDocs!
             */
            virtual ~Module() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * @return The DOM document of this module.
             */
            DOMDocument *getDocument() const = 0;

        protected:

            /* --- Data Members --- */

            /** The document */
            DOMDocument *document;
        }
    }
}

#endif
