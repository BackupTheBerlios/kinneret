/***************************************************************************
 *   Copyright (C) 2005 by Itay 'z9u2K' Duvdevani                          *
 *   itay AT z9u2kHomelinuxCom                                             *
 *   (replace uppercase letters with '.' and lowercase letter)             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/kinneret/Repository/internet-ng/src/core/ConnectionDescriptor.h,v 1.3 2005/01/19 21:10:22 z9u2k Exp $

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
