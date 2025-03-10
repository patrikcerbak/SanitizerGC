#include "customMapper.hpp"

#include <cstdint>
#include <cstdio>

void * beforeAddr = nullptr;
void * afterAddr = nullptr;
void * afterEndAddr = nullptr;

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
