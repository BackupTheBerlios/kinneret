#include "core/resolvers/Resolver.h"
#include "core/utils/Log.h"
#include "core/utils/Config.h"

using namespace core::resolvers;
using namespace core::utils;

void testConstructor() {
    Resolver *resolver = 0;

    resolver = new Resolver();
}

int main() {
    Log::create(DEBUG);
    try {
        testConstructor();
    } catch (...) {
    }
    Log::release();

    return 0;
}
