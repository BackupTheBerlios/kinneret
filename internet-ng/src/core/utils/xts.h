#ifndef CORE_UTILS_XTS
#define CORE_UTILS_XTS

#include <xercesc/util/XercesDefs.hpp>

namespace core {
    namespace utils {
        /**
         *
         */
        class xts {

        public:

            xts(const std::string &str) {
                xmlString = xercesc::XMLString::transcode(str.c_str());
                cString = 0;
            }

            xts(const XMLCh *str, bool trim = false) {
                if (trim) {
                    XMLCh *replicate = xercesc::XMLString::replicate(str);
                    xercesc::XMLString::trim(replicate);
                    cString = xercesc::XMLString::transcode(replicate);
                    xercesc::XMLString::release(&replicate);
                } else {
                    cString = xercesc::XMLString::transcode(str);
                }
                
                xmlString = 0;
            }
            
            virtual ~xts() {
                if (xmlString != 0) {
                    xercesc::XMLString::release(&xmlString);
                }

                if (cString != 0) {
                    xercesc::XMLString::release(&cString);
                }
            }

            std::string asString() const {
                return std::string(cString);
            }

            operator XMLCh*() const {
                return xmlString;
            }

            /*
            operator char*() const {
                return cString;
            }
            */

            operator std::string() const {
                return asString();
            }

        private:

            XMLCh *xmlString;
            char *cString;
        };
    }
}

#endif
