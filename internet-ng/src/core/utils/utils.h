#ifndef CORE_UTILS_UTILS
#define CORE_UTILS_UTILS

#include <string>

/*
 * Author: z9u2k
 * $Revision: 1.1 $
 */

namespace core {
    namespace utils {
        /**
         * Resolvs the path to the schema file of the XML in question.
         * It strips down the XML file from the <b>full path</b> given, and
         * uses the directory it is in as the name of the schema.
         *
         * @param xml Full path to the file in question. The file must be in
         *        the database.
         * @return Full path to the validating schema for that file.
         */
        std::string getSchema(const std::string &xml);
    }
}

#endif
