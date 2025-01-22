#include "customMapper.hpp"

#include <cstdio>

void * beforeAddr = nullptr;
void * afterAddr = nullptr;
void * afterEndAddr = nullptr;
void * beforeEndAddr = nullptr;

void* SanitizerGCMapper::mapNewAddrToOriginalAddr(void* newAddr) {
    if (afterAddr != nullptr && newAddr >= afterAddr && newAddr <= afterEndAddr) {
        const long difference = static_cast<char*>(newAddr) - static_cast<const char*>(afterAddr);
        newAddr = static_cast<char*>(beforeAddr) + difference;
    }

    return newAddr;
}

void SanitizerGCMapper::testPrint(void* newAddr) {
    printf("---+++%p\n", newAddr);
}
