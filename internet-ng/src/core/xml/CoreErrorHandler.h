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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/xml/CoreErrorHandler.h,v 1.2 2005/01/19 21:10:22 z9u2k Exp $

#ifndef CORE_XM_CORE_ERROR_HANDLER
#define CORE_XM_CORE_ERROR_HANDLER

#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>

namespace core {
    namespace xml {
        /**
         * Handles parsing errors.
         *
         * @author z9u2k
         */
        class CoreErrorHandler : public xercesc::ErrorHandler {
        public:

            /* --- Constructor --- */

            /**
             * Constructor.
             */
            CoreErrorHandler();

            /**
             * Destructor
             */
            virtual ~CoreErrorHandler();

            /* --- Inherited from ErrorHandler --- */

            /**
             * Resets internal error state.
             */
            void resetErrors();

            /**
             * An error occured.
             *
             * @param ex The exception causing the error.
             */
            void error(const xercesc::SAXParseException &ex);

            /**
             * A warning occured.
             *
             * @param ex The exception causing the error.
             */
            void warning(const xercesc::SAXParseException &ex);

            /**
             * A fatal error occured.
             *
             * @param ex The exception causing the error.
             */
            void fatalError(const xercesc::SAXParseException &ex);

            /* --- Public Methods --- */

            /** @return Number of errors encountered */
            int getErrorCount() const throw () {
                return errorCount;
            }

        private:

            /* --- Data Members --- */

            /** Number of errors encountered */
            int errorCount;
        };
    }
}

#endif
