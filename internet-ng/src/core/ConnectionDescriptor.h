#ifndef CONNECTION_DESCRIPTOR
#define CONNECTION_DESCRIPTOR

#include <map>

#include "xml/XMLReadable.h"
#include "Resolver.h"
#include "exceptions/Exceptions.h"

namespace core {
    /**
     * This class hold every information needed by the
     * <code>ConnectionAssembler</code> to create a conection.
     *
     * @author z9u2k
     * $Revision: 1.2 $
     */
    class ConnectionDescriptor : public Resolver, XMLReadable {
    public:

        /* --- Constructors --- */

        ConnectionDescriptor(const std::string &name) throw () :
                Resolver(name) {
            // Nothing to do
        }
        
        virtual ~ConnectionDescriptor() throw () {
            // Nothing to do
        }

        /* --- Public Methods --- */

        /**
         * Adds a resolver for the specific namespace <code>ns</code>.
         *
         * @param ns The namespace this resolver can resolve.
         * @param resolver The resolver.
         */
        void addResolver(const std::string &ns, const Resolver *resolver)
            throw ();

        /**
         * Removes a resolver from the specifin namespace <code>ns</code>.
         *
         * @param ns The namespace that its resolver should be removed.
         *
         * @throws NoSuchNamespaceException When the namespace requested is
         *         not listed in this descriptor.
         */
        void removeResolver(const std::string &ns)
            throw (exceptions::NoSuchNamespaceException);

        /**
         * Verified that the descriptor is set and ready to be delivered to
         * the <code>ConnectionAssembler</code>.
         *
         * @throws AssertionFailedException When the descriptor is not ready.
         *         The reason for the exception should be listed in
         *         <code>what()</code>.
         */
        void assertDescriptor() const
            throw (exceptions::AssertionFailedException);

    private:

        /* --- Private Methods --- */

        /**
         * Extracts the namespace out of the parameter.
         *
         * @param param The full string of the parameter of the form:
         *        <code>[*namespace::param*]</code>
         * @return The namespace this parameter is at.
         *
         * @throws InvalidFormatException When the given string is of the
         *         wrong format and cannot be parsed.
         */
        const std::string getNamespace(const std::string &param) const
            throw (exceptions::InvalidFormatException);

        /**
         * Extracts the parameter out of the fully-qualified parameter.
         *
         * @param param The full string of the parameter of the form:
         *        <code>[*namespace::param*]</code>
         * @return The parameter.
         *
         * @throws InvalidFormatException When the given string is of the
         *         wrong format and cannot be parsed.
         */
        const std::string getParam(const std::string &param) const
            throw (exceptions::InvalidFormatException);

        /**
         * Returns the resolver that is able to resolve parameter of the
         * namespace <code>ns</code>.
         *
         * @param ns The namespace we wish to resolve parameters from.
         * @return <code>Resolver</code> that is able to resolve the
         *         requested namespace.
         *
         * @throws NoSuchNamespaceException When the namespace requested is
         *         not listed in this descriptor.
         */
        const Resolver *getResolver(const std::string &ns) const
            throw (exceptions::NoSuchNamespaceException);

        /* --- Data Members --- */

        /**
         * Holds the <code>Resolver</code>s. Maps between them and the
         * namespace they can resolve.
         */
        std::map<std::string, Resolver*> resolvers;
    };
}

#endif
