#include "core/resolvers/Resolver.h"
#include "core/utils/Log.h"
#include "core/utils/Config.h"
#include "core/utils/utils.h"
#include "core/exception/exception.h"
#include "core/xml/xml.h"

#include <string>

using namespace core::exception;
using namespace core::resolvers;
using namespace core::utils;
using namespace core::xml;
using namespace xercesc;
using namespace std;

void testResolver() {
    Resolver *resolver = 0;
    // Load test resolver
    resolver = new Resolver(
        Config::getDatabasePath() +
            Config::getResolversDirectoryName() + "/driver.xml",
        Config::getDatabasePath() +
            Config::getDriversDirectoryName() + "/generic-pptp-cable.xml");

    Log::info("Attempting to resolve valid param...");
    if (resolver->canResolve("name")) {
        Log::info("Resolveable");
    } else {
        Log::info("Unresolveable");
        throw FatalException("Failure in loading resolver!");
    }

    Log::info("name = " + resolver->resolvParam("name"));

    Log::info("Attempting to resolve invalid param...");
    if (resolver->canResolve("__name")) {
        Log::info("Resolveable");
        throw FatalException("Failure in loading resolver!");
    } else {
        Log::info("Unresolveable");
    }

    delete resolver;
}

int main() {
    // Initialize logger
    Log::create(Log::VERBOSE);
    initXML();
    

    // Load config
    try {
        Config::create("database/test.conf");
    } catch (const FileNotFoundException &ex) {
        Log::fatal(ex.what());
        return -1;
    } catch (const IOException &ex) {
        Log::fatal(ex.what());
        return -1;
    } catch (const InvalidFormatException &ex) {
        Log::fatal(ex.what());
        return -1;
    }

    int rc = 0;

    // Do test
    try {
        testResolver();
    } catch (const XMLException &ex) {
        Log::fatal(getExceptionString(ex));
        rc = -1;
    } catch (const DOMException &ex) {
        Log::fatal(getExceptionString(ex));
        rc = -1;
    } catch (const FatalException &ex) {
        Log::fatal(string("FatalException: ") + ex.what());    
        rc = -1;
    } catch (...) {
        Log::fatal("Unknown exception");
        rc = -1;
    }

    Config::release();
    releaseXML();
    Log::release();

    return rc;
}
