#ifndef XML_WRITEABLE
#define XML_WRITEABLE

#include <xercesc/dom/DOM.hpp>

namespace core {
    namespace xml {
        /**
         * This interface allows the implementing class to be saved to an
         * XML DOM tree.
         *
         * @author z9u2k
         */
        class XMLWriteable {
        public:

            /* --- Constuctors --- */

            XMLWriteable() throw () {
                // Nothing to do
            }

            virtual ~XMLWriteable() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * Saves to a DOM tree.
             *
             * @parm document Document to write to.
             */
            virtual void toXML(DOMDocument *const document) = 0;
        }
    }
}

#endif
