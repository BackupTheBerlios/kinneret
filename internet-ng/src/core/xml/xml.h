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

/*
 * Author: z9u2k
 * $Revision: 1.1 $
 */

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
         * @param element Element to look under
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
