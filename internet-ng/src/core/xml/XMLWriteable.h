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
             * @parm root Root elemnt of the document.
             */
            virtual void toXML(const DOMElement *const root) = 0;
        }
    }
}

#endif
