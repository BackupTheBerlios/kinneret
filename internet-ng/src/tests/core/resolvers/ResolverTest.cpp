#include "core/resolvers/Resolver.h"
#include "core/utils/Log.h"
#include "core/utils/Config.h"
#include "core/exception/exception.h"

using namespace core::exception;
using namespace core::resolvers;
using namespace core::utils;
/*
void testConstructor() {
    Resolver *resolver = 0;

    resolver = new Resolver();
}
*/
int main() {
    Log::create(Log::VERBOSE);

    try {
        Config::create("/home/z9u2k/projects/internet-ng/database/test.conf");
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
    /*
    try {
        testConstructor();
    } catch (...) {
    }
    */
    Config::release();
    Log::release();

    return 0;
}
