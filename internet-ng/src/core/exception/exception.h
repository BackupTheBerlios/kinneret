#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <string>
#include <exception>

/*
 * This file holds the exceptions namespace and all the exception might be
 * thrown from within the application.
 *
 * $Revision: 1.3 $
 */
namespace core {
    namespace exception {
        /**
         * Generic excpetion.
         *
         * @author z9u2k
         */
        class Exception : public std::exception {
        public:

            /* --- Constructors --- */
            
            /**
             * Constructor.
             *
             * @param w The reason for the exception.
             */
            Exception(const std::string &w) throw () : exception() {
                reason = w;
            }

            /**
             * Destructor.
             */
            virtual ~Exception() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * @return Reson for the exception
             */
            virtual const char *what() const throw() {
                return reason.c_str();
            }

        private:

            /* --- Data Members --- */

            std::string reason;
        };

        /**
         * Thrown when the requested namespace is not available.
         *
         * @author z9u2k
         */
        class NoSuchNamespaceException : public Exception {
        public:
            
            /* --- Constructors --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            NoSuchNamespaceException(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~NoSuchNamespaceException() throw () {
                // Nothing to do
            }
        };

        /**
         * Thrown when the requested parameter is valid, but no value could
         * be found.
         *
         * @author z9u2k
         */
        class ParameterNotFoundException : public Exception {
        public:
            
            /* --- Constructors --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            ParameterNotFoundException(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~ParameterNotFoundException() throw () {
                // Nothing to do
            }
        };

        /**
         * Thrown when the requested parameter is invalid.
         *
         * @author z9u2k
         */
        class NoSuchParamemterExcpetion : public Exception {
        public:
            
            /* --- Constructors --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            NoSuchParamemterExcpetion(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~NoSuchParamemterExcpetion() throw () {
                // Nothing to do
            }
        };

        /**
         * Thrown when a certain seertion failed.
         *
         * @author z9u2k
         */
        class AssertionFailedException : public Exception {
        public:

            /* --- Constructors --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            AssertionFailedException(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~AssertionFailedException() throw () {
                // Nothing to do
            }
        };

        /**
         * Thrown when the requested string cannot be parsed because of a
         * format error.
         *
         * @author z9u2k
         */
        class InvalidFormatException : public Exception {
        public:

            /* --- Constructos --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            InvalidFormatException(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~InvalidFormatException() throw () {
                // Nothing to do
            }
        };

        /**
         * Thrown when a file requested could not be found.
         *
         * @author z9u2k
         */
        class FileNotFoundException : public Exception {
        public:

            /* --- Constructos --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            FileNotFoundException(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~FileNotFoundException() throw () {
                // Nothing to do
            }
        };

        /**
         * Thrown when a generic I/O error was encountered.
         *
         * @author z9u2k
         */
        class IOException : public Exception {
        public:

            /* --- Constructos --- */
            
            /**
             * Constructor.
             *
             * @param what The reason for the exception.
             */
            IOException(const std::string &what) throw () :
                    Exception(what) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~IOException() throw () {
                // Nothing to do
            }
        };
    }
}

#endif
