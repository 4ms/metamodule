#pragma once
#include "conf/ramdisk_conf.hh"
#include <cstdint>

// MP2 version of src/ld.h (MP1's memory map, from its linker scripts): only what MP2 code uses.

// MP2's RamDisk is an ordinary object, sized by its conf
static constexpr uint32_t VIRTDRIVE_SZ = RamDiskSizeBytes;

// Linker script
extern char _sheap;
extern char _eheap;
static const uint32_t A7_HEAP_SZ = uint32_t(&_eheap - &_sheap);
