#include "core/resolvers/Resolver.h"
#include "core/xml/xml.h"
#include "core/utils/utils.h"
#include "core/utils/Log.h"
#include "core/utils/xts.h"

#include <string>
#include <vector>

#include <xalanc/XPath/XalanXPathException.hpp>

using namespace std;
using namespace xercesc;
using namespace xalanc;
using namespace core::resolvers;
using namespace core::exception;
using namespace core::utils;
using namespace core::xml;

core::resolvers::Resolver::Resolver(const string &resolverFile,
        const string &moduleFile)
        throw (XMLException, DOMException, FatalException) {
    Log::verbose("Loading " + resolverFile);
    Log::verbose("Validation will be made using " + getSchema(resolverFile));
    resolverDocument = loadXML(resolverFile, getSchema(resolverFile));
    Log::verbose("Successfully loaded and validated resolver.");

    Log::verbose("Loading " + moduleFile);
    Log::verbose("Validation will be made using " + getSchema(moduleFile));
    moduleDocument = loadXML(moduleFile, getSchema(moduleFile));
    Log::verbose("Successfully loaded and validated module.");

    // Get resolver name
    nameSpace = getAllTextNodes(
        resolverDocument->getElementsByTagName(xts("namespace"))->item(0));
    Log::verbose(string("Namespace: ") + nameSpace);
}

core::resolvers::Resolver::~Resolver() throw () {
}

bool core::resolvers::Resolver::canResolve(const string &param)
        const throw () {
    return (getParamNode(param) != 0);
}

string core::resolvers::Resolver::resolvParam(const string &param) const
        throw (core::exception::NoSuchParamemterExcpetion,
               core::exception::ParameterNotFoundException,
               xalanc::XalanXPathException) {
    DOMNode *node = getParamNode(param);
    if (node == 0) {
        throw NoSuchParamemterExcpetion("Parameter: " + param +
            " is invalid!");
    }

    // Get XPath attribute from element
    DOMNamedNodeMap *attributes = node->getAttributes();
    DOMNode *xpathNode = attributes->getNamedItem(xts("xpath"));

    // Evaluate XPath and get value
    Log::verbose(string("Evaluating: ") +
        xts(xpathNode->getTextContent()).asString());
    vector<DOMNode*> xpathResult = evalXPath(xts(xpathNode->getTextContent()),
        moduleDocument);

    // See the results
    if (xpathResult.size() == 0) {
        // Nothing found
        throw ParameterNotFoundException(param +
            " was not found at the module!");
    } else if (xpathResult.size() > 1) {
        // TODO: Choise
        return "TODO";
    } else {
        // Singe result, return its text.
        return getAllTextNodes(xpathResult[0]);
    }
}

/* --- Private Methods --- */

DOMNode *core::resolvers::Resolver::getParamNode(const string &param) const
        throw () {
    // Build XPath expression
    string xpath = "resolver/param[@name='" + param + "']";

    vector<DOMNode*> result;
    try {
        Log::verbose(string("Evaluating: ") + xpath);
        result = evalXPath(xpath, resolverDocument);
    } catch (const XalanXPathException &ex) {
        Log::bug("Bug in XPath! " + getExceptionString(ex));
        return 0;
    }

    if (result.size() == 0) {
        Log::verbose("Not found");
        return 0;
    } else if (result.size() > 1) {
        Log::warning("Multiple <param/> with the same name! "
            "Ignoring everything but first.");
    }

    return result[0];
}

