#include <sstream>
#include <vector>
#include <string>

#include "core/xml/xml.h"
#include "core/exception/exception.h"
#include "core/xml/CoreErrorHandler.h"

#include "core/utils/xts.h"

#include <xalanc/XalanTransformer/XercesDOMWrapperParsedSource.hpp>
#include <xalanc/XercesParserLiaison/XercesDocumentWrapper.hpp>
#include <xalanc/XercesParserLiaison/XercesDOMSupport.hpp>
#include <xalanc/XPath/XObject.hpp>
#include <xalanc/XPath/NodeRefList.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XPath/XalanXPathException.hpp>

using namespace xercesc;
using namespace xalanc;
using namespace core::xml;
using namespace core::utils;
using namespace core::exception;
using namespace std;

XercesDOMParser  *core::xml::parser = 0;
CoreErrorHandler *core::xml::coreHandler = 0;
XercesDOMSupport  core::xml::theDOMSupport;
XPathEvaluator    core::xml::theEvaluator;

DOMDocument *core::xml::loadXML(const std::string &xml,
        const std::string &schema)
        throw (XMLException, DOMException, FatalException) {
    parser->setExternalNoNamespaceSchemaLocation(schema.c_str());
    parser->parse(xml.c_str());
    if (coreHandler->getErrorCount() != 0) {
        throw FatalException("Unable to load " + xml);
    }
    
    parser->getDocument()->normalize();
    return parser->getDocument();
}

void core::xml::initXML() throw (XMLException) {
    // Initialize Xerces
    XMLPlatformUtils::Initialize();
    // Initialize Xalan's XPath evaluator
    XPathEvaluator::initialize();
    parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);
    parser->setDoValidation(true);
    parser->setDoSchema(true);
    parser->setIncludeIgnorableWhitespace(false);

    coreHandler = new CoreErrorHandler();
    parser->setErrorHandler(coreHandler);
}

void core::xml::releaseXML() throw () {
    delete parser;
    delete coreHandler;
}

vector<DOMNode*> core::xml::evalXPath(const string &xpath,
        DOMDocument *const document) throw (XalanXPathException) {
    // Use Xalan for XPath
    XercesDocumentWrapper theWrapper(document, false, false, false);
    
    // Evaluate XPath
    NodeRefList resultNodeList = theEvaluator.selectNodeList(
        theDOMSupport,
        theWrapper.getDocumentElement()->getParentNode(),
        XalanDOMString(xpath.c_str()).c_str());

    vector<DOMNode*> result;
    const unsigned int length = resultNodeList.getLength();
    for (unsigned int i = 0 ; i < length ; i++) {
        DOMNode *node = (DOMNode*)(theWrapper.mapNode(resultNodeList.item(i)));
        if (node != 0) {
            result.push_back(node);
        }
    }

    return result;
}

string core::xml::getAllTextNodes(DOMNode *const node) throw () {
    stringstream result;

    DOMNodeList *children = node->getChildNodes();
    if (children->getLength() > 1) {
        for (unsigned int i = 0 ; i < children->getLength() ; i++) {
            result << getAllTextNodes(children->item(i));
        }
    } else {
        // Trim
        result << xts(node->getTextContent(), true).asString();
    }

    return result.str();
}

string core::xml::getExceptionString(const XMLException &ex) throw () {
    stringstream result;
    result << "XMLException: " << xts(ex.getMessage()) <<
        " (file: " << ex.getSrcFile() << ", line: " << ex.getSrcLine() <<
        ").";
    return result.str();
}

string core::xml::getExceptionString(const SAXParseException &ex) throw () {
    stringstream result;
    result << "SAXParseException: " << xts(ex.getMessage()) << " (line: "
        << ex.getLineNumber() << ", column: " << ex.getColumnNumber() <<
        ").";
    return result.str();
}

string core::xml::getExceptionString(const DOMException &ex) throw () {
    stringstream result;
    result << "DOMException: " << xts(ex.getMessage()) << ".";
    return result.str();
}

string core::xml::getExceptionString(const XalanXPathException &ex) throw () {
    stringstream result;
    // TODO: Use core::utils::xts when transcoding to local encoding.
    result << "XalanXPathException: " << ex.getMessage().transcode() << 
        " (line: " << ex.getLineNumber() << ", column: " <<
        ex.getColumnNumber() << ").";
    return result.str();
}
