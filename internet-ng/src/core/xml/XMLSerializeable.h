#ifndef XML_SERIALIZEABLE
#define XML_SERIALIZEABLE

#include "XMLReadable.h"
#include "XMLWriteable.h"

namespace core {
    namespace xml {
        /**
         * This interface allows the implementing class to be serialized to
         * and from an XML DOM tree.
         *
         * @author z9u2k
         */
        class XMLSerializeable : public XMLReadable, XMLWriteable {
        public:

            /* --- Constuctors --- */

            XMLSerializeable() throw () : XMLReadable(), XMLWriteable() {
                // Nothing to do
            }

            virtual ~XMLSerializeable() throw () {
                // Nothing to do
            }
        }
    }
}

#endif
