#ifndef CUSTOMMAPPER_H
#define CUSTOMMAPPER_H

#include "runtime/globals.hpp"

    extern void * beforeAddr;
    extern void * afterAddr;
    extern void * afterEndAddr;
    extern void * beforeEndAddr;

class SanitizerGCMapper {
public:
    static const void* mapNewAddrToOriginalAddr(const void* newAddr);
    static void testPrint(void* newAddr);
    template <typename T> static inline void remapAddress(T &addr) {
      if (SanitizeGC) {
        addr = reinterpret_cast<T>(mapNewAddrToOriginalAddr(addr));
      }
    }
};

#endif //CUSTOMMAPPER_H
