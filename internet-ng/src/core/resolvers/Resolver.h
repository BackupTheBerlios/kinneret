#ifndef RESOLVER
#define RESOLVER

#include <string>
#include <map>

#include "../exception/exception.h"
#include "../xml/XMLReadable.h"

namespace core {
    namespace resolvers {
        /**
         * @author z9u2k
         * $Revision: 1.1 $
         */
        class Resolver : public core::xml::XMLReadable {
        public:

            /* --- Constructor --- */

            /**
             * Constructor.
             *
             * @param resolverFile Path to resolver XML.
             * @param moduleFile Path to module XML.
             */
            Resolver(const std::string &resolverFile,
                const std::string &moduleFile)
                throw (xercesc::XMLException, xercesc::DOMException);

            /**
             * Destructor. Does nothing.
             */
            virtual ~Resolver() throw ();

            /* --- Attributes --- */

            /** @return Resolver's name */
            const std::string getNamespace() const throw () {
                return nameSpace;
            }

            /* --- Public Methods --- */

            /**
             * This method resolvs choises in the module.
             *
             * @param xpath XPath to the conflict
             * @param name The 'name' attribute of the chosen parameter.
             */
            void choose(const std::string &xpath, const std::string &name);

            /**
             * Checks whether the given parameter is resolvable by this
             * resolver.
             *
             * Note that <code>param</code> should be the name of the
             * parameter, without the namespace qualifier.
             * 
             * @return <code>true</code> if the parameter <code>param</code>
             *         is resolvable by this resolver, <code>false</code>
             *         otherwise.
             */
            bool canResolve(const std::string &param) const;

            /**
             * Resolvs values.
             *
             * @param param Parameter to resolv (unqualified).
             * 
             * @return The value of the parameter.
             * @throws NoSuchParamemterExcpetion When the parameter given is
             *         invalid.
             * @throws ParameterNotFoundException When the requested
             *         parameter is valid, but could not be resolved.
             */
            const std::string resolvParam(const std::string &param) const
                throw (core::exception::NoSuchParamemterExcpetion,
                    core::exception::ParameterNotFoundException);

            void fromXML(const xercesc::DOMElement *const root)
                throw(core::exception::InvalidFormatException);

        private:

            /* --- Data Members --- */

            /** Resolver's namesapce */
            std::string nameSpace;

            /** Maps between parameter name and XPaths */
            std::map<std::string, std::string> paramsXPath;

            /** DOM document with module's data */
            xercesc::DOMDocument *document;
        };
    }
}

#endif
