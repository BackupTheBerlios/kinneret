#ifndef CORE_MODULE
#define CORE_MODULE

#include "Module.h"

namespace core {
    namespace modules {
        /**
         * 
         * @author: z9u2k
         * $Revision: 1.1 $
         */
        class ISP : public Module {
        public:

            /* --- Constructors --- */

            ISP() throw () {
                // Nothing to do
            }

            virtual ~ISP() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * @return The DOM document of this module.
             */
            DOMDocument *getDocument() const {
                return document;
            }

        protected:

            /* --- Data Members --- */

            /** The document */
            DOMDocument *document;
        }
    }
}

#endif
