#ifndef CORE_XM_CORE_ERROR_HANDLER
#define CORE_XM_CORE_ERROR_HANDLER

#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>

namespace core {
    namespace xml {
        /**
         * Handles parsing errors.
         *
         * @author z9u2k
         * $Revision: 1.1 $
         */
        class CoreErrorHandler : public xercesc::ErrorHandler {
        public:

            /* --- Constructor --- */

            /**
             * Constructor.
             */
            CoreErrorHandler();

            /**
             * Destructor
             */
            virtual ~CoreErrorHandler();

            /* --- Inherited from ErrorHandler --- */

            /**
             * Resets internal error state.
             */
            void resetErrors();

            /**
             * An error occured.
             *
             * @param ex The exception causing the error.
             */
            void error(const xercesc::SAXParseException &ex);

            /**
             * A warning occured.
             *
             * @param ex The exception causing the error.
             */
            void warning(const xercesc::SAXParseException &ex);

            /**
             * A fatal error occured.
             *
             * @param ex The exception causing the error.
             */
            void fatalError(const xercesc::SAXParseException &ex);

            /* --- Public Methods --- */

            /** @return Number of errors encountered */
            int getErrorCount() const throw () {
                return errorCount;
            }

        private:

            /* --- Data Members --- */

            /** Number of errors encountered */
            int errorCount;
        };
    }
}

#endif
