#include "core/exception/exception.h"
#include "core/utils/Config.h"
#include "core/utils/Log.h"

#include <fstream>
#include <string>
#include <sstream>
#include <limits>

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

/* --- Member functions --- */

Config::Config(const std::string &file) throw (FileNotFoundException,
        IOException, InvalidFormatException) {
    ifstream infile(file.c_str());
    if (!infile.is_open()) {
        throw FileNotFoundException("File: " + file + " could not be found!");
    }

    // Process one line at a time
    char line[1000];
    while (!infile.eof()) {
        infile.getline(line, 1000, '\n');
        if (strlen(line) > 0) {
            processLine(string(line));
        }
    }

    infile.close();
}

void Config::release() {
    delete instance;
    instance = 0;
}

void Config::processLine(const string &line) throw (InvalidFormatException) {
    // Remove the whitesapces from the begining
    string parsed = removeWhite(line);
    if (parsed[0] == '#') {
        // Comment
        return;
    }

    // Non-comment
    validate(parsed);
    string key = getKey(parsed);
    string value = getValue(parsed);

    constants[key] = value;
    Log::verbose(key + " => " + value);
}

void Config::validate(const std::string &line) 
        throw(InvalidFormatException) {
    string::size_type equals = line.find("=");
    if (equals == string::npos) {
        throw InvalidFormatException("Line does not cantain the "
            "equals sign: " + line);
    } else if (equals == 0) {
        throw InvalidFormatException("Equals sign should not be the "
            "first character: " + line);
    } else if (equals == line.length()) {
        throw InvalidFormatException("Equals sign should not be the "
            "last character: " + line);
    }
}

string Config::getKey(const string &line) {
    int lastAlnum;
    for (lastAlnum = 0 ; isalnum(line[lastAlnum]) ; lastAlnum++);
    return line.substr(0, lastAlnum);
}

string Config::getValue(const string &line) {
    // Find the equals sign, get sub-string, and remove whitespaces.
    string::size_type equals = line.find('=');
    return removeWhite(line.substr(equals + 1, line.length() - equals));
}

string Config::removeWhite(const string &line) {
    int firstAlnum;
    for (firstAlnum = 0 ; isspace(line[firstAlnum]) ; firstAlnum++);
    return line.substr(firstAlnum, line.length() - firstAlnum);
}

string Config::get(const string &key) const {
    map<string, string>::const_iterator iter = constants.find(key);

    if (iter == constants.end()) {
        return "";
    } else {
        return iter->second;
    }
}

/* --- Static Methods --- */

void Config::create(const string &file)
        throw (FileNotFoundException, IOException, InvalidFormatException) {
    // Make sure it is the first time
    if (instance != 0) {
        Log::warning("Tried to initialize constants repository " 
            "without releasing first!");
        return;
    }
    
    instance = new Config(file);
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

