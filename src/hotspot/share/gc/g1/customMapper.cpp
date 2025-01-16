#include "customMapper.hpp"

void * beforeAddr = nullptr;
void * afterAddr = nullptr;

void* SanitizerGCMapper::mapNewAddrToOriginalAddr(void* newAddr) {
    volatile int a = 1;
    return nullptr;
}
