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

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/resolvers/Resolver.cpp,v 1.5 2005/01/19 21:30:50 z9u2k Exp $

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
    Log::verbose(string("Evaluating XPath: ") +
        xts(xpathNode->getTextContent()).asString());

    vector<DOMNode*> xpathResult = evalXPath(xts(xpathNode->getTextContent()),
        moduleDocument);

    // See the results
    if (xpathResult.size() == 0) {
        // Nothing found
        throw ParameterNotFoundException(param + " was not found at the "
            "module!");
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
        Log::verbose(string("Evaluating XPath: ") + xpath);
        result = evalXPath(xpath, resolverDocument);
    } catch (const XalanXPathException &ex) {
        Log::bug("Bug in XPath syntax! " + getExceptionString(ex));
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

