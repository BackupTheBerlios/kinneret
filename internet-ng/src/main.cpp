#include "core/utils/Log.h"

using namespace core::utils;

int main() {
    Log::create(Log::INFO);
    Log::info("internet-ng");
    Log::release();
    return 0;
}
