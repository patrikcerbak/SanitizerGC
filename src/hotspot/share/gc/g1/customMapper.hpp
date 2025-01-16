#ifndef CUSTOMMAPPER_H
#define CUSTOMMAPPER_H

    extern void * beforeAddr;
    extern void * afterAddr;

class SanitizerGCMapper {
public:
  static void* mapNewAddrToOriginalAddr(void* newAddr);
};

#endif //CUSTOMMAPPER_H
