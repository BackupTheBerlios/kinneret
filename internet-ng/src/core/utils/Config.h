#ifndef CORE_UTILS_CONFIG
#define CORE_UTILS_CONFIG

#include <string>
#include <map>

#include "core/exception/exception.h"

namespace core {
    namespace utils {
        /**
         * Singleton constants repository. Built from a configuration file
         * and can provide application-wide constants.
         *
         * @author z9u2k
         * $Revision: 1.1 $
         */
        class Config {
        public:

            /* --- Managment --- */

            /**
             * Load constants from a file.
             *
             * @param file Path to config file
             */
            static void create(const std::string &file)
                throw (core::exception::InvalidStateException);

            /**
             * Release constants repository at the end of usage.
             */
            static void release();

            /* --- Constants --- */

            static std::string getDatabasePath();
            static std::string getIspsDirectoryName();
            static std::string getDriversDirectoryName();
            static std::string getSchemasDirectoryName();
            static std::string getConnectionsDirectoryName();
            static std::string getScriptsDirectoryName();
            static std::string getResolversDirectoryName();

        private:

            /* --- Singleton --- */

            Config(const std::string &file)
                throw (core::exception::FileNotFoundException,
                       core::exception::IOException,
                       core::exception::InvalidFormatException);

            /* --- Private Methods --- */

            std::string get(const std::string &key) const;

            /* --- Constants --- */

            static const std::string DATABASE_PATH_NAME;
            static const std::string ISPS_DIR_NAME;
            static const std::string DRIVERS_DIR_NAME;
            static const std::string SCHEMAS_DIR_NAME;
            static const std::string CONNECTIONS_DIR_NAME;
            static const std::string SCRIPTS_DIR_NAME;
            static const std::string RESOLVERS_DIR_NAME;

            /* --- Data Members --- */

            /** Maps between constants names and values */
            std::map<std::string, std::string> constants;

            /* --- Singleton instance --- */

            /** Singleton instance */
            static Config *instance;
        };
    }
}

#endif
