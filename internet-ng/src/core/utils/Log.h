/***************************************************************************
 *   Copyright (C) 2005 by Itay 'z9u2K' Duvdevani                          *
 *   itay AT z9u2kHomelinuxCom                                             *
 *   (replace uppercase letters with '.' and lowercase letter)             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/utils/Log.h,v 1.2 2005/01/19 21:10:22 z9u2k Exp $

#ifndef CORE_UTILS_LOG
#define CORE_UTILS_LOG

#include <string>

namespace core {
    namespace utils {
        /**
         * Singleton logger.
         * 
         * @authro z9u2k
         */
        class Log {
        public:

            /* --- Public Static Methods --- */

            /**
             * Initializes the logger with a specifi log level.
             *
             * @param level Log level to initilize logger with.
             */
            static void create(int level);

            /**
             * Releases the logger;
             */
            static void release();

            /**
             * Logs a message at the bug level.
             *
             * @param msg Message.
             */
            static void bug(const std::string &msg);

            /**
             * Logs a message at the fatal level.
             *
             * @param msg Message.
             */
            static void fatal(const std::string &msg);
            
            /**
             * Logs a message at the error level.
             *
             * @param msg Message.
             */
            static void error(const std::string &msg);

            /**
             * Logs a message at the warning level.
             *
             * @param msg Message.
             */
            static void warning(const std::string &msg);
            
            /**
             * Logs a message at the info level.
             *
             * @param msg Message.
             */
            static void info(const std::string &msg);

            /**
             * Logs a message at the verbose level.
             *
             * @param msg Message.
             */
            static void verbose(const std::string &msg);

            /* --- Constants --- */

            /** Nothing */
            static const int NONE = 7;

            /** Bug level */
            static const int BUG = 6;

            /** Fatal log level */
            static const int FATAL = 5;

            /** Error log level */
            static const int ERROR = 4;

            /** Warning log level */
            static const int WARNING = 3;

            /** Info log level */
            static const int INFO = 2;

            /** Verbose (debug) log level */
            static const int VERBOSE = 1;

            /** Log all */
            static const int ALL = 0;

        private:

            /* --- Private Methods --- */

            /**
             * Logs <code>msg</code> with a specific log level.
             *
             * @param level Log level this message is logged at
             * @param msg Messages
             */
            void log(int level, const std::string &msg);

            /* --- Singleton --- */
            
            /**
             * Private constructor.
             *
             * @param level Log level this logger is at
             */
            Log(int level);

            /* --- Data Members --- */

            /** Current log level */
            int logLevel;

            /* --- Singeton instance --- */

            /** Thie singleton instance */
            static Log *instance;
        };
    }
}

#endif
