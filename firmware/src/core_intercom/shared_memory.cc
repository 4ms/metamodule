#include "shared_memory.hh"

__attribute__((section(".sharedmemindex"))) MetaModule::SharedMemoryS::Ptrs MetaModule::SharedMemoryS::ptrs;
