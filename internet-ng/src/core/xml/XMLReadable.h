#ifndef XML_READABLE
#define XML_READABLE

#include <xercesc/dom/DOM.hpp>

#include "../exceptions/Exceptions.h"

namespace core {
    namespace xml {
        /**
         * This interface allows the implementing class to be loaded from an
         * XML DOM tree.
         *
         * @author z9u2k
         */
        class XMLReadable {
        public:

            /* --- Constuctors --- */

            XMLReadable() throw () {
                // Nothing to do
            }

            virtual ~XMLReadable() throw () {
                // Nothing to do
            }

            /* --- Public Methods --- */

            /**
             * Loads from a DOM tree.
             *
             * @parm root Root elemnt of the document.
             * @throws InvalidFormatException When the XML is of an invalid
             *         format and the class cannot load from it.
             */
            virtual void fromXML(const DOMElement *const root)
                throw (InvalidFormatException) = 0;
        }
    }
}

#endif
