#ifndef RESOLVER
#define RESOLVER

#include <string>

#include "exceptions/Exceptions.h"

namespace core {
    /**
     * This abstract class can resolve constants from a script template
     * (constants donated by the <code>[*namespace::param*]</code> notation).
     *
     * @author z9u2k
     */
    class Resolver {
    public:

        /* --- Constructor --- */

        /**
         * Constructor.
         *
         * @param name Resolver's name (usually the namespace this resolver
         *             can resolve).
         */
        Resolver(const std::string &name) throw () {
            this->name = name;
        }
        
        /**
         * Destructor. Does nothing.
         */
        virtual ~Resolver() throw () {
            // Nothing to destroy
        }

        /* --- Attributes --- */

        /** @return Resolver's name */
        const std::string getName() const throw () {
            return name;
        }

        /**
         * Resolvs values.
         *
         * @param param Parameter to resolv, of the form:
         *        <code>[*namespace::param*]</code>.
         * 
         * @return The value of the parameter. Parameters are given at the
         *         form they are written in the templates.
         *
         * @throws NoSuchParamemterExcpetion When the parameter given is
         *         invalid.
         */
        const std::string getParam(const std::string &param) const
            throw (exceptions::NoSuchParamemterExcpetion);

    private:

        /* --- Data Members --- */

        /** Resolver's name */
        std::string name;
    };
}

#endif
