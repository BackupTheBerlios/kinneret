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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/xml/xml.h,v 1.3 2005/01/19 21:40:40 z9u2k Exp $

#ifndef CORE_XML_XML
#define CORE_XML_XML

#include <string>
#include <vector>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include <xalanc/XercesParserLiaison/XercesDOMSupport.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XPath/XalanXPathException.hpp>

#include "core/exception/exception.h"

namespace core {
    namespace xml {

        /* --- Prototypes --- */

        class CoreErrorHandler;

        /* --- Methods --- */
        
        /**
         * Loads an XML file and validates it using a schema.
         *
         * @param xml Path to XML file to load
         * @param schema Path to schema file
         * @return DOM document of the file
         *
         * @throw XMLException If the was a problem parsing the file
         * @throw DOMException If there was a problem creating the DOM tree.
         */
        xercesc::DOMDocument *loadXML(const std::string &xml,
            const std::string &schema)
            throw (xercesc::XMLException, xercesc::DOMException,
                   core::exception::FatalException);

        /**
         * Initializes XML parsing engine.
         *
         * @throw XMLException When the enginewas unable to initialize.
         */
        void initXML() throw (xercesc::XMLException);

        /**
         * Releases XML parsing engine.
         */
        void releaseXML() throw ();

        /**
         * Evaluates an XPath expression using Xalan and returns a list of
         * matching nodes.
         *
         * @param xpath The XPath expression
         * @param document Document to evaluate
         * @return <code>std::vector</code> full of matching
         *         <code>DOMNode*</code>s (or empty).
         */
        std::vector<xercesc::DOMNode*> evalXPath(
            const std::string &xpath, xercesc::DOMDocument *const document)
            throw (xalanc::XalanXPathException);

        /**
         * This method finds all the text nodex it can find under
         * <code>element</code>, concats them together, and returns.
         *
         * @param node Element to look under
         * @return The concatenation of all the text nodes under
         *         <code>element</code>.
         */
        std::string getAllTextNodes(xercesc::DOMNode *const node)
            throw ();

        /**
         * Transforms the exception to readable text.
         *
         * @param ex Exception
         * @return The exception as a readable string.
         */
        std::string getExceptionString(const xercesc::XMLException &ex)
            throw ();

        /**
         * Transforms the exception to readable text.
         *
         * @param ex Exception
         * @return The exception as a readable string.
         */
        std::string getExceptionString(const xercesc::SAXParseException &ex)
            throw ();

        /**
         * Transforms the exception to readable text.
         *
         * @param ex Exception
         * @return The exception as a readable string.
         */
        std::string getExceptionString(const xercesc::DOMException &ex)
            throw ();

        /**
         * Transforms the exception to readable text.
         *
         * @param ex Exception
         * @return The exception as a readable string.
         */
        std::string getExceptionString(const xalanc::XalanXPathException &ex)
            throw ();

        /* --- Objects --- */

        /** The XML parser and validator */
        extern xercesc::XercesDOMParser *parser;

        /** The default error handelr */
        extern CoreErrorHandler *coreHandler;

        /** XercesDOM support for Xalan */
        extern xalanc::XercesDOMSupport theDOMSupport;

        /** Xalan's XPath evaluator */
        extern xalanc::XPathEvaluator theEvaluator;
    }
}

#endif
