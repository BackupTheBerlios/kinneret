#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <string>
#include <exception>

/*
 * This file holds the exceptions namespace and all the exception might be
 * thrown from within the application.
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
             * @param what The reason for the exception.
             */
            Exception(const std::string &what) throw () :
                    exception(what.c_str()) {
                // Nothing to do
            }

            /**
             * Destructor.
             */
            virtual ~Exception() throw () {
                // Nothing to do
            }
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
    }
}

#endif
