#include "core/utils/utils.h"
#include "core/utils/Config.h"

using namespace core::utils;
using namespace std;

string core::utils::getSchema(const string &xml) {
    // Get the driectory this file is in
    string::size_type lastSlash;
    string::size_type slashBeforeLastSlash;

    lastSlash = xml.rfind("/");
    slashBeforeLastSlash = xml.rfind("/", lastSlash - 1);

    string schmaName = xml.substr(slashBeforeLastSlash,
        lastSlash - slashBeforeLastSlash) + ".xsd";
    return Config::getDatabasePath() + Config::getSchemasDirectoryName() +
        schmaName;
}
