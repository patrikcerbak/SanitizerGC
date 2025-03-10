#ifndef CUSTOMMAPPER_H
#define CUSTOMMAPPER_H

#include "runtime/globals.hpp"

    extern void * beforeAddr;
    extern void * afterAddr;
    extern void * afterEndAddr;

class SanitizerGCMapper {
public:
    static const void* mapNewAddrToOriginalAddr(const void* newAddr);
    static void testPrint(void* newAddr);
    template <typename T> static inline void remapAddress(T &addr) {
      if (SanitizeGC) {
        addr = (T) mapNewAddrToOriginalAddr(addr);
      }
    }
};

#endif //CUSTOMMAPPER_H
