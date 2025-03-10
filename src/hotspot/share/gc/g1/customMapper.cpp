#include "customMapper.hpp"

#include <cstdint>
#include <cstdio>

const void* SanitizerGCMapper::originalRegionStart = nullptr;
const void* SanitizerGCMapper::movedRegionStart = nullptr;
const void* SanitizerGCMapper::movedRegionEnd = nullptr;

void SanitizerGCMapper::initializeMapping(const void* originalRegionStart,
        const void* movedRegionStart, const void* movedRegionEnd) {
    SanitizerGCMapper::originalRegionStart = originalRegionStart;
    SanitizerGCMapper::movedRegionStart = movedRegionStart;
    SanitizerGCMapper::movedRegionEnd = movedRegionEnd;
}

const void* SanitizerGCMapper::mapNewAddrToOriginalAddr(const void* newAddr) {
    if (movedRegionStart != nullptr &&
            newAddr >= movedRegionStart && newAddr < movedRegionEnd) {
        const intptr_t difference = static_cast<const char*>(newAddr) - static_cast<const char*>(movedRegionStart);
        newAddr = static_cast<const char*>(originalRegionStart) + difference;
    }

    return newAddr;
}

void SanitizerGCMapper::testPrint(void* newAddr) {
    printf("---+++%p\n", newAddr);
}
