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

#ifndef CORE_UTILS_XTS
#define CORE_UTILS_XTS

#include <string>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>

namespace core {
    namespace utils {
        /**
         * This class implicitly converts <code>XMLCh</code> strings to
         * <code>std::string</code> and vice-versa. It is also able to trim
         * XML strings.
         *
         * This class is a utility class meant to be used as a
         * function-object, where it is created, used and destroyed at the
         * same statement.
         *
         * Because of that, if this object is initialized with an XML string,
         * convertion to standart strings will be the only valid operation.
         * Trying to recover the <code>XMLCh*</code> given will result in
         * null. Likewise the other way around.
         *
         * Notice that when built from an XML string, this class <b>does
         * not</b> release it, leaving the user with the responsibility to do
         * so.
         *
         * @author z9u2k
         * $Revision: 1.2 $
         */
        class xts {
        public:

            /* --- Constructors --- */

            /**
             * Convers a standart <code>string</code> to <code>XMLCh*</code>.
             *
             * @param str String to convert to <code>CMLCh*</code> string.
             */
            xts(const std::string &str);

            /**
             * Convers an <code>XMLCh*</code> string buffer to standart
             * <code>string</code>. This constructor is also able to trim the
             * given string.
             *
             * @param str XML string to conver to standart
             *        <code>string</code>
             * @param trim Should the XML string should be stripped from
             *        whitespaces that are at the beginning and at the end.
             */
            xts(const XMLCh *str, bool trim = false);

            /**
             * Destructor. Releases any allocated strings.
             */
            virtual ~xts();

            /* --- Convertion --- */

            /**
             * @return Standart <code>string</code> representation of the
             *         <code>XMLCh*</code> given at the constructor. Notice that
             *         this method will return an empty string when called
             *         after the object was build of a standart string.
             */
            std::string asString() const;

            /**
             * Implicitly converts standart strings to XML string.
             *
             * @return An XML string representation of the standart string
             *         given at the constructor. Notice that this methos will
             *         return null when called after this object was build of
             *         an XML string.
             */
            operator XMLCh*() const {
                return xmlString;
            }

            /**
             * Implicitly converts XML strings to standart strings.
             *
             * @return Standart <code>string</code> representation of the
             *         <code>XMLCh*</code> given at the constructor. Notice that
             *         this method will return an empty string when called
             *         after the object was build of a standart string.
             */
            operator std::string() const {
                return asString();
            }

        private:

            /* --- Data Members --- */

            /**
             * An XML representation of the standart string given at the
             * constructor.
             */
            XMLCh *xmlString;

            /**
             * A standart string representation of the XML string given at
             * the constructor.
             */
            char *cString;
        };
    }
}

#endif
