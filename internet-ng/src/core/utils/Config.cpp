#include "core/exception/exception.h"
#include "core/utils/Config.h"
#include "core/utils/Log.h"

using namespace core::exception;
using namespace core::utils;
using namespace std;

/* --- Static Fields --- */

Config *Config::instance                  = 0;
const string Config::DATABASE_PATH_NAME   = "database";
const string Config::ISPS_DIR_NAME        = "isps";
const string Config::DRIVERS_DIR_NAME     = "drivers";
const string Config::SCHEMAS_DIR_NAME     = "schemas";
const string Config::CONNECTIONS_DIR_NAME = "connections";
const string Config::SCRIPTS_DIR_NAME     = "scripts";
const string Config::RESOLVERS_DIR_NAME   = "resolvers";

/* --- Implementation --- */

void Config::create(const string &file) {
    // Make sure it is the first time
    if (instance != 0) {
        Log::bug("Tried to initialize constants repository " 
            "without releasing first!");
        return;
    }
    
    try {
        instance = new Config(file);
    } catch (const FileNotFoundException &ex) {
        // TODO
    } catch (const IOException &ex) {
        // TODO
    } catch (const InvalidFormatException &ex) {
        // TODO
    }
}

void Config::release() {
    delete instance;
    instance = 0;
}

string Config::get(const string &key) const {
    map<string, string>::const_iterator iter = constants.find(key);

    if (iter == constants.end()) {
        return "";
    } else {
        return iter->second;
    }
}

string Config::getDatabasePath() {
    return instance->get(DATABASE_PATH_NAME);
}

string Config::getIspsDirectoryName() {
    return instance->get(ISPS_DIR_NAME);
}

string Config::getDriversDirectoryName() {
    return instance->get(DRIVERS_DIR_NAME);
}

string Config::getSchemasDirectoryName() {
    return instance->get(SCHEMAS_DIR_NAME);
}

string Config::getConnectionsDirectoryName() {
    return instance->get(CONNECTIONS_DIR_NAME);
}

string Config::getScriptsDirectoryName() {
    return instance->get(SCRIPTS_DIR_NAME);
}

string Config::getResolversDirectoryName() {
    return instance->get(RESOLVERS_DIR_NAME);
}

