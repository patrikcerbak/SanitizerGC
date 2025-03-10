#ifndef CUSTOMMAPPER_H
#define CUSTOMMAPPER_H

#include "runtime/globals.hpp"

class SanitizerGCMapper {
private:
    static const void* originalRegionStart;
    static const void* movedRegionStart;
    static const void* movedRegionEnd;

public:
    static void initializeMapping(const void* originalRegionStart,
            const void* movedRegionStart, const void* movedRegionEnd);
    static const void* mapNewAddrToOriginalAddr(const void* newAddr);
    static void testPrint(void* newAddr);
    template <typename T> static inline void remapAddress(T &addr) {
      if (SanitizeGC) {
        addr = (T) mapNewAddrToOriginalAddr(addr);
      }
    }
};

#endif //CUSTOMMAPPER_H
