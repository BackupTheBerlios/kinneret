#ifndef CORE_MODULE
#define CORE_MODULE

#include "../xml/XMLReadable.h"

namespace core {
    namespace modules {
        /**
         * This abstract class represents a module that is loadable from an XML
         * file.
         * 
         * @author: z9u2k
         * $Revision: 1.1 $
         */
        class Module : public XMLReadable {
        public:

            /* --- Constructors --- */

            Module() throw () {
                // Nothing to do
            }

            virtual ~Module() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * @return The DOM document of this module.
             */
            DOMDocument *getDocument() const = 0;

        protected:

            /* --- Data Members --- */

            /** The document */
            DOMDocument *document;
        }
    }
}

#endif
