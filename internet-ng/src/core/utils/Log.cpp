#include <iostream>

#include "Log.h"

using namespace std;
using namespace core::utils;
//
// The instance
Log *Log::instance;

Log::Log(int level) {
    logLevel = level;
}

void Log::create(int level) {
    instance = new Log(level);
}

void Log::release() {
    delete instance;
}

void Log::log(int level, const std::string &msg) {
    if (level >= logLevel) {
        cerr << msg << endl;
    }
}

void Log::bug(const std::string &msg) {
    instance->log(BUG, "BUG > " + msg);
}

void Log::fatal(const std::string &msg) {
    instance->log(FATAL, "FATAL > " + msg);
}

void Log::error(const std::string &msg) {
    instance->log(ERROR, "ERROR > " + msg);
}

void Log::warning(const std::string &msg) {
    instance->log(WARNING, "WARNING > " + msg);
}

void Log::info(const std::string &msg) {
    instance->log(INFO, "INFO > " + msg);
}

void Log::verbose(const std::string &msg) {
    instance->log(VERBOSE, "VERBOSE > " + msg);
}
