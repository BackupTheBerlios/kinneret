#include "Resolver.h"

using namespace std;
using namespace xercesc;
using namespace core::resolvers;
using namespace core::exception;

Resolver::Resolver(const string &resolverFile, const string &moduleFile)
        throw (XMLException, DOMException) {
    // TODO
}

Resolver::~Resolver() throw () {
    // TODO
}

void Resolver::choose(const string &xpath, const string &name) {
    // TODO
}

bool Resolver::canResolve(const string &param) const {
    // TODO
}

const string Resolver::resolvParam(const string &param) const
        throw (NoSuchParamemterExcpetion, ParameterNotFoundException) {
    // TODO
}

void Resolver::fromXML(const DOMElement *const root)
        throw (InvalidFormatException) {
    // TODO
}
