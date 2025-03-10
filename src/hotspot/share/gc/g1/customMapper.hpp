#ifndef CUSTOMMAPPER_H
#define CUSTOMMAPPER_H

#include "runtime/globals.hpp"

class SanitizerGCMapper {
private:
    static const void* beforeAddr;
    static const void* afterAddr;
    static const void* afterEndAddr;

public:
    static void initializeMapping(const void* beforeAddr,
            const void* afterAddr, const void* afterEndAddr);
    static const void* mapNewAddrToOriginalAddr(const void* newAddr);
    static void testPrint(void* newAddr);
    template <typename T> static inline void remapAddress(T &addr) {
      if (SanitizeGC) {
        addr = (T) mapNewAddrToOriginalAddr(addr);
      }
    }
};

#endif //CUSTOMMAPPER_H
