#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <string>
#include <exception>

/*
 * This file holds the exceptions namespace and all the exception might be
 * thrown from within the application.
 *
 * $Revision: 1.4 $
 */

#define MakeCoreException(name) \
class name : public Exception { \
public: \
    name(const std::string &what) throw () : Exception(what) { \
    } \
\
    virtual ~name() throw () { \
    } \
};

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

        MakeCoreException(NoSuchNamespaceException)
        MakeCoreException(ParameterNotFoundException)
        MakeCoreException(NoSuchParamemterExcpetion)
        MakeCoreException(AssertionFailedException)
        MakeCoreException(InvalidFormatException)
        MakeCoreException(FileNotFoundException)
        MakeCoreException(IOException)
        MakeCoreException(FatalException)
    }
}

#endif
