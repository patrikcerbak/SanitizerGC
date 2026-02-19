#ifndef SHARE_GC_G1_SANITIZEADDRESSMAPPER_HPP
#define SHARE_GC_G1_SANITIZEADDRESSMAPPER_HPP

class SanitizeGCMapper {
public:

    static const void* mapNewAddrToOriginalAddrImpl(const void* newAddr);
    static const void* mapNewEdgeAddrToOriginalAddrImpl(const void* newAddr);
    static const void* mapOriginalAddrToNewAddrImpl(const void *newAddr);
    static const void* mapOriginalEdgeAddrToNewAddrImpl(const void* newAddr);

    template <typename T> static inline void mapNewAddrToOriginalAddr(T &addr) {
      addr = (T) mapNewAddrToOriginalAddrImpl(addr);
    }
    template <typename T> static inline void mapNewEdgeAddrToOriginalAddr(T &addr) {
      addr = (T) mapNewEdgeAddrToOriginalAddrImpl(addr);
    }
    template <typename T> static inline void mapOriginalAddrToNewAddr(T &addr) {
      addr = (T) mapOriginalAddrToNewAddrImpl(addr);
    }
    template <typename T> static inline void mapOriginalEdgeAddrToNewAddr(T &addr) {
      addr = (T) mapOriginalEdgeAddrToNewAddrImpl(addr);
    }
};

#define MacroAssemblerMapNewAddrToOriginalAddr(addr) do {                                               \
  if (SanitizeGC) {                                                                                     \
    RegSet exclude_set = RegSet::of((addr));                                                            \
    __ push_call_clobbered_registers_except(exclude_set);                                               \
    __ call_VM_leaf(CAST_FROM_FN_PTR(address, SanitizeGCMapper::mapNewAddrToOriginalAddrImpl), (addr)); \
    __ movptr((addr), rax);                                                                             \
    __ pop_call_clobbered_registers_except(exclude_set);                                                \
  }                                                                                                     \
} while(0)

#endif // SHARE_GC_G1_SANITIZEADDRESSMAPPER_HPP
