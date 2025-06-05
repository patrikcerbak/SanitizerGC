#include "customMapper.hpp"

ptrdiff_t SanitizerGCMapper::movedRegionOffset = 0;
const void* SanitizerGCMapper::movedRegionStart = nullptr;
const void* SanitizerGCMapper::movedRegionEnd = nullptr;
const void* SanitizerGCMapper::originalRegionStart = nullptr;
const void* SanitizerGCMapper::originalRegionEnd = nullptr;

// Since we can't use void* for pointer arithmetic, we need another pointer
// type, whose base element size is the unit for movedRegionOffset. We must use
// the same pointer type when computing movedRegionOffset as when applying it,
// so we define it here to ensure it is the same at both places. We choose char*
// which makes movedRegionOffset unit to be bytes.
using byte_ptr = const char*;

void SanitizerGCMapper::initializeMapping(const void* originalRegionStart,
        const void* originalRegionEnd, const void* movedRegionStart, const void* movedRegionEnd) {
    SanitizerGCMapper::movedRegionOffset =
            static_cast<byte_ptr>(originalRegionStart) -
            static_cast<byte_ptr>(movedRegionStart);
    SanitizerGCMapper::movedRegionStart = movedRegionStart;
    SanitizerGCMapper::movedRegionEnd = movedRegionEnd;
    SanitizerGCMapper::originalRegionStart = originalRegionStart;
    SanitizerGCMapper::originalRegionEnd = originalRegionEnd;
}

const void* SanitizerGCMapper::mapNewAddrToOriginalAddr(const void* newAddr) {
    if (movedRegionOffset != 0 &&
            newAddr >= movedRegionStart && newAddr <= movedRegionEnd) { // TODO
        return static_cast<byte_ptr>(newAddr) + movedRegionOffset;
    }

    return newAddr;
}

const void* SanitizerGCMapper::mapOriginalAddrToNewAddr(const void* originalAddr) {
    if (movedRegionOffset != 0 &&
            originalAddr >= originalRegionStart && originalAddr <= originalRegionEnd) {
        return static_cast<byte_ptr>(originalAddr) - movedRegionOffset;
            }

    return originalAddr;
}

void SanitizerGCMapper::testPrint(void* address, uintptr_t value) {
    if (address >= movedRegionStart && address <= movedRegionEnd &&
        (void*)value >= movedRegionStart && (void*)value <= movedRegionEnd) {
            // printf("+SANITIZE (moved dst+val):   DST:%p  VAL:%p\n", address, (void*)value);
    } else if (address >= movedRegionStart && address <= movedRegionEnd) {
        // printf("+SANITIZE (moved dst):   DST:%p  VAL:%p\n", address, (void*)value);
    } else if ((void*)value >= movedRegionStart && (void*)value <= movedRegionEnd) {
        // printf("+SANITIZE (moved val):   DST:%p  VAL:%p\n", address, (void*)value);
    } else if (address >= originalRegionStart && address <= originalRegionEnd &&
        (void*)value >= originalRegionStart && (void*)value <= originalRegionEnd) {
            // printf("+SANITIZE (original dst+val):   DST:%p  VAL:%p\n", address, (void*)value);
    } else if (address >= originalRegionStart && address <= originalRegionEnd) {
            // printf("+SANITIZE (original dst):   DST:%p  VAL:%p\n", address, (void*)value);
    } else if ((void*)value >= originalRegionStart && (void*)value <= originalRegionEnd) {
        // printf("+SANITIZE (original val):   DST:%p  VAL:%p\n", address, (void*)value);
    } else {
        // printf("+SANITIZE (other):   DST:%p  VAL:%p\n", address, (void*)value);
    }

    fflush(stdout);
}
