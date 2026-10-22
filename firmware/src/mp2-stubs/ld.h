#pragma once
#include "conf/ramdisk_conf.hh"
#include <cstddef>
#include <cstdint>

// MP2 version of src/ld.h (MP1's memory map, from its linker scripts): only what MP2 code uses.

// MP2's RamDisk is an ordinary object, sized by its conf
static constexpr uint32_t VIRTDRIVE_SZ = RamDiskSizeBytes;

// Linker script
extern char _sheap;
extern char _eheap;
static const uint32_t A7_HEAP_SZ = uint32_t(&_eheap - &_sheap);

// The table of symbols plugins can use (.symlist), filled in after linking (cmake/mp2.cmake)
extern char _A7_SYMS[];
extern char _A7_SYMS_END[];
static const uintptr_t A7_SYMS = reinterpret_cast<uintptr_t>(_A7_SYMS);
static const size_t A7_SYMS_SZ = size_t(_A7_SYMS_END - _A7_SYMS);
