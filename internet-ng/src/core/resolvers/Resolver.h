#ifndef RESOLVER
#define RESOLVER

#include <string>
#include <map>

#include "core/exception/exception.h"

#include <xercesc/dom/DOM.hpp>

#include <xalanc/XPath/XalanXPathException.hpp>

namespace core {
    namespace resolvers {
        /**
         * @author z9u2k
         * $Revision: 1.2 $
         */
        class Resolver {
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
                throw (xercesc::XMLException, xercesc::DOMException,
                       core::exception::FatalException);

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
            void choose(const std::string &xpath, const std::string &name)
                throw ();

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
            bool canResolve(const std::string &param) const throw ();

            /**
             * Resolvs values.
             *
             * @param param Parameter to resolve (unqualified).
             * 
             * @return The value of the parameter.
             * @throw NoSuchParamemterExcpetion When the parameter given is
             *        invalid.
             * @throw ParameterNotFoundException When the requested
             *        parameter is valid, but could not be resolved.
             * @throw XalanXPathException When the XPath supplied in the
             *        resolver is invalid.
             */
            std::string resolvParam(const std::string &param) const
                throw (core::exception::NoSuchParamemterExcpetion,
                       core::exception::ParameterNotFoundException,
                       xalanc::XalanXPathException);
        private:

            /**
             * Finds the node that holds information regarding the parameter.
             * If the method finds multiple parameters that answers the
             * query, it generates a warning and ignores everything but the
             * first node returned.
             *
             * @param param Parameter's name
             * @return The node that describes that parameter, of
             *         <code>null</code> if the parameter could not be
             *         found.
             */
            xercesc::DOMNode *getParamNode(const std::string &param)
                const throw ();

            /* --- Data Members --- */

            /** Resolver's namesapce */
            std::string nameSpace;

            /** DOM document with module's data */
            xercesc::DOMDocument *moduleDocument;

            /** DOM document with resolver's data */
            xercesc::DOMDocument *resolverDocument;
        };
    }
}

#endif
