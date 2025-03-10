#include "customMapper.hpp"

#include <cstdint>
#include <cstdio>

const void* SanitizerGCMapper::beforeAddr = nullptr;
const void* SanitizerGCMapper::afterAddr = nullptr;
const void* SanitizerGCMapper::afterEndAddr = nullptr;

void SanitizerGCMapper::initializeMapping(const void* beforeAddr,
        const void* afterAddr, const void* afterEndAddr) {
    SanitizerGCMapper::beforeAddr = beforeAddr;
    SanitizerGCMapper::afterAddr = afterAddr;
    SanitizerGCMapper::afterEndAddr = afterEndAddr;
}

const void* SanitizerGCMapper::mapNewAddrToOriginalAddr(const void* newAddr) {
    if (afterAddr != nullptr && newAddr >= afterAddr && newAddr < afterEndAddr) {
        const intptr_t difference = static_cast<const char*>(newAddr) - static_cast<const char*>(afterAddr);
        newAddr = static_cast<const char*>(beforeAddr) + difference;
    }

    return newAddr;
}

void SanitizerGCMapper::testPrint(void* newAddr) {
    printf("---+++%p\n", newAddr);
}
