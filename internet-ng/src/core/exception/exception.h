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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/exception/exception.h,v 1.5 2005/01/19 21:10:22 z9u2k Exp $

#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <string>
#include <exception>

/*
 * This file holds the exceptions namespace and all the exception might be
 * thrown from within the application.
 */
#define MakeCoreException(name) \
class name : public Exception { \
public: \
    name(const std::string &what) throw () : Exception(what) { \
    } \
\
    virtual ~name() throw () { \
    } \
};

namespace core {
    namespace exception {
        /**
         * Generic excpetion.
         *
         * @author z9u2k
         */
        class Exception : public std::exception {
        public:

            /* --- Constructors --- */
            
            /**
             * Constructor.
             *
             * @param w The reason for the exception.
             */
            Exception(const std::string &w) throw () : exception() {
                reason = w;
            }

            /**
             * Destructor.
             */
            virtual ~Exception() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * @return Reson for the exception
             */
            virtual const char *what() const throw() {
                return reason.c_str();
            }

        private:

            /* --- Data Members --- */

            std::string reason;
        };

        MakeCoreException(NoSuchNamespaceException)
        MakeCoreException(ParameterNotFoundException)
        MakeCoreException(NoSuchParamemterExcpetion)
        MakeCoreException(AssertionFailedException)
        MakeCoreException(InvalidFormatException)
        MakeCoreException(FileNotFoundException)
        MakeCoreException(IOException)
        MakeCoreException(FatalException)
    }
}

#endif
