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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/resolvers/Resolver.h,v 1.4 2005/01/19 21:10:22 z9u2k Exp $

#ifndef RESOLVER
#define RESOLVER

#include <string>
#include <map>

#include "core/exception/exception.h"

#include <xercesc/dom/DOM.hpp>

#include <xalanc/XPath/XalanXPathException.hpp>

namespace core {
    namespace resolvers {
        /**
         * This abstract class represent a generic resolver. It can load
         * modules, and resolve simple qureies. Resolving complex queries
         * (i.e. choices) is up to the implementing class.
         * 
         * @author z9u2k
         */
        class Resolver {
        public:

            /* --- Constructor --- */

            /**
             * Constructor.
             *
             * @param resolverFile Path to resolver XML.
             * @param moduleFile Path to module XML.
             */
            Resolver(const std::string &resolverFile,
                const std::string &moduleFile)
                throw (xercesc::XMLException, xercesc::DOMException,
                       core::exception::FatalException);

            /**
             * Destructor. Does nothing.
             */
            virtual ~Resolver() throw ();

            /* --- Attributes --- */

            /** @return Resolver's name */
            const std::string getNamespace() const throw () {
                return nameSpace;
            }

            /* --- Public Methods --- */

            /**
             * This abstract method resolvs choises in the module.
             *
             * @param xpath XPath to the conflict
             * @param name The 'name' attribute of the chosen parameter.
             */
            virtual void choose(const std::string &xpath,
                const std::string &name) throw () = 0;

            /**
             * Checks whether the given parameter is resolvable by this
             * resolver.
             *
             * Note that <code>param</code> should be the name of the
             * parameter, without the namespace qualifier.
             * 
             * @return <code>true</code> if the parameter <code>param</code>
             *         is resolvable by this resolver, <code>false</code>
             *         otherwise.
             */
            bool canResolve(const std::string &param) const throw ();

            /**
             * Resolvs values.
             *
             * @param param Parameter to resolve (unqualified).
             * 
             * @return The value of the parameter.
             * @throw NoSuchParamemterExcpetion When the parameter given is
             *        invalid.
             * @throw ParameterNotFoundException When the requested
             *        parameter is valid, but could not be resolved.
             * @throw XalanXPathException When the XPath supplied in the
             *        resolver is invalid.
             */
            std::string resolvParam(const std::string &param) const
                throw (core::exception::NoSuchParamemterExcpetion,
                       core::exception::ParameterNotFoundException,
                       xalanc::XalanXPathException);
        protected:

            /* --- Protected Methods --- */

            /**
             *
             */
            virtual std::string resolvComplex(const std::string &param,
                const std::string &xpath, const std::string &multi,
                const std::vector<xercesc::DOMNode*> &xpathResult) const = 0;
            
        private:

            /**
             * Finds the node that holds information regarding the parameter.
             * If the method finds multiple parameters that answers the
             * query, it generates a warning and ignores everything but the
             * first node returned.
             *
             * @param param Parameter's name
             * @return The node that describes that parameter, of
             *         <code>null</code> if the parameter could not be
             *         found.
             */
            xercesc::DOMNode *getParamNode(const std::string &param)
                const throw ();

            /**
             * Resolves multiple values with the 'lang' attribute. It first
             * tries to resolve the current locale (the one in the
             * configuration), it it fails, it looks from the 'en' locale. If
             * that fails, it selects the first locale available.
             *
             * @param xpathResult The nodes we should choose from.
             * @return The content of the chosen element in the chosen
             *         language, at the chosen locale (see
             *         <code>Config::getEncoding()</code>);
             */
            std::string resolvLang(
                const std::vector<xercesc::DOMNode*> &xpathResult) const;

            /* --- Data Members --- */

            /** Resolver's namesapce */
            std::string nameSpace;

            /** DOM document with module's data */
            xercesc::DOMDocument *moduleDocument;

            /** DOM document with resolver's data */
            xercesc::DOMDocument *resolverDocument;
        };
    }
}

#endif
