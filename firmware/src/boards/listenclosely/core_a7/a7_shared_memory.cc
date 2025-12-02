#include "a7_shared_memory.hh"

__attribute__((section(".sharedmemindex"))) MetaModule::A7SharedMemoryS::Ptrs MetaModule::A7SharedMemoryS::ptrs;
