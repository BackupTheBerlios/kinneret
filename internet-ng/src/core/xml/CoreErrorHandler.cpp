#include "core/xml/CoreErrorHandler.h"
#include "core/utils/Log.h"
#include "core/xml/xml.h"

using namespace xercesc;
using namespace core::utils;
using namespace core::xml;

core::xml::CoreErrorHandler::CoreErrorHandler() : ErrorHandler() {
    resetErrors();
}

core::xml::CoreErrorHandler::~CoreErrorHandler() {
}

void core::xml::CoreErrorHandler::resetErrors() {
    errorCount = 0;
}

void core::xml::CoreErrorHandler::error(const SAXParseException &ex) {
    Log::error(getExceptionString(ex));
    errorCount++;
}

void core::xml::CoreErrorHandler::warning(const SAXParseException &ex) {
    Log::warning(getExceptionString(ex));
    errorCount++;
}

void core::xml::CoreErrorHandler::fatalError(const SAXParseException &ex) {
    Log::fatal(getExceptionString(ex));
    errorCount++;
}
