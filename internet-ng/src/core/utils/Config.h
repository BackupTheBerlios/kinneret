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
         * $Revision: 1.2 $
         */
        class Config {
        public:

            /* --- Managment --- */

            /**
             * Load constants from a file.
             *
             * @param file Path to config file
             *
             * @throw FileNotFoundException When <code>file</code> does not
             *        exists on the file system.
             * @throw IOException When reading from the configuration file
             *        is not possible.
             * @throw InvalidFormatException When the configuration file
             *        could not be parsed due to formatting errors.
             */
            static void create(const std::string &file)
                throw (core::exception::FileNotFoundException,
                       core::exception::IOException,
                       core::exception::InvalidFormatException);

            /**
             * Release constants repository at the end of usage.
             */
            static void release();

            /* --- Constants --- */

            /** @return Full path to the database's root */
            static std::string getDatabasePath();

            /** @return Name of the ISPs sub-directory. */
            static std::string getIspsDirectoryName();
            
            /** @return Name of the drivers sub-directory. */
            static std::string getDriversDirectoryName();
            
            /** @return Name of the XML Schema sub-directory. */
            static std::string getSchemasDirectoryName();
            
            /** @return Name of the connections sub-directory. */
            static std::string getConnectionsDirectoryName();
            
            /** @return Name of the scripts sub-directory. */
            static std::string getScriptsDirectoryName();
            
            /** @return Name of the resolvers sub-directory. */
            static std::string getResolversDirectoryName();

        private:

            /* --- Singleton --- */

            /**
             * Constructor. Loads the repository from the config file.
             *
             * @param file Path to config file.
             *
             * @throw FileNotFoundException When <code>file</code> does not
             *        exists on the file system.
             * @throw IOException When reading from the configuration file
             *        is not possible.
             * @throw InvalidFormatException When the configuration file
             *        could not be parsed due to formatting errors.
             */
            Config(const std::string &file)
                throw (core::exception::FileNotFoundException,
                       core::exception::IOException,
                       core::exception::InvalidFormatException);

            /* --- Private Methods --- */

            /**
             * Resolvs a single value from the map.
             *
             * @param key The key.
             *
             * @return The value pointed by <code>key</code>, or an empty
             *         string if the value was not in the map.
             */
            std::string get(const std::string &key) const;

            /**
             * Process a linge line from the file.
             *
             * @param line Singel line from the file.
             *
             * @throw InvalidFormatException If the line is of an invalid
             *        format.
             */
            void processLine(const std::string &line)
                throw (core::exception::InvalidFormatException);

            /* --- Static Members --- */

            /**
             * Removes all the whitespaces from the beginning of the string.
             *
             * @param line Line to clean
             * @return Clean line with no whitespaces at the beginning.
             */
            static std::string removeWhite(const std::string &line);
            
            /**
             * Parses the key from the line.
             * Note that the line must be clean and valid.
             *
             * @param line Line to parse.
             * @return The key (Left hand side).
             */
            static std::string getKey(const std::string &line);

            /**
             * Parses the value from the line.
             * Note that the line must be clean and valid.
             *
             * @param line Line to parse.
             * @return The value (Right hand side).
             */
            static std::string getValue(const std::string &line);

            /**
             * Validates a line. Throws <code>InvalidFormatException</code>
             * if the line isn't valid.
             *
             * @param line Line to validate.
             * 
             * @throw InvalidFormatException When the line isn't valid.
             */
            static void validate(const std::string &line)
                throw (core::exception::InvalidFormatException);

            /* --- Constants --- */

            /** The key to the database path */
            static const std::string DATABASE_PATH_NAME;
            
            /** The key to the ISPs name */
            static const std::string ISPS_DIR_NAME;
            
            /** The key to the drivers name */
            static const std::string DRIVERS_DIR_NAME;
            
            /** The key to the XML Schema name */
            static const std::string SCHEMAS_DIR_NAME;
            
            /** The key to the connections name */
            static const std::string CONNECTIONS_DIR_NAME;
            
            /** The key to the scripts name */
            static const std::string SCRIPTS_DIR_NAME;
            
            /** The key to the resolvers name */
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
