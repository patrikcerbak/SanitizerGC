#ifndef CUSTOMMAPPER_H
#define CUSTOMMAPPER_H

    extern void * beforeAddr;
    extern void * afterAddr;
    extern void * afterEndAddr;
    extern void * beforeEndAddr;

class SanitizerGCMapper {
public:
    static void* mapNewAddrToOriginalAddr(void* newAddr);
    static void testPrint(void* newAddr);
};

#endif //CUSTOMMAPPER_H
