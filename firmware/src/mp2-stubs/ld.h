#pragma once
#include "conf/ramdisk_conf.hh"
#include <cstddef>
#include <cstdint>

// MP2 version of src/ld.h: the memory map, from system/linker/memory_mp2.ld (for the A35 and the
// M33), and the MP1 names that shared code uses.

// Defined in linker scripts:

extern char _A35_CODE[];
extern char _A35_CODE_SZ[];
extern char _A35_CODE_END[];

extern char _M33_REGION[];
extern char _M33_REGION_SZ[];
extern char _M33_REGION_END[];

extern char _A35_RAM[];
extern char _A35_RAM_SZ[];
extern char _A35_RAM_END[];

extern char _FRAMEBUF[];
extern char _FRAMEBUF_SZ[];
extern char _FRAMEBUF_END[];

extern char _SHAREDMEM[];
extern char _SHAREDMEM_SZ[];
extern char _SHAREDMEM_END[];

extern char _DMABUF[];
extern char _DMABUF_SZ[];
extern char _DMABUF_END[];

extern char _A35_HEAP[];
extern char _A35_HEAP_SZ[];
extern char _A35_HEAP_END[];

static const uintptr_t A35_CODE = (uintptr_t)_A35_CODE;
static const size_t A35_CODE_SZ = (size_t)_A35_CODE_SZ;

static const uintptr_t M33_REGION = (uintptr_t)_M33_REGION;
static const size_t M33_REGION_SZ = (size_t)_M33_REGION_SZ;
static const uintptr_t M33_REGION_END = (uintptr_t)_M33_REGION_END;

static const uintptr_t A35_RAM = (uintptr_t)_A35_RAM;
static const size_t A35_RAM_SZ = (size_t)_A35_RAM_SZ;

static const uintptr_t FRAMEBUF = (uintptr_t)_FRAMEBUF;
static const size_t FRAMEBUF_SZ = (size_t)_FRAMEBUF_SZ;

static const uintptr_t SHAREDMEM = (uintptr_t)_SHAREDMEM;
static const size_t SHAREDMEM_SZ = (size_t)_SHAREDMEM_SZ;

static const uintptr_t DMABUF = (uintptr_t)_DMABUF;
static const size_t DMABUF_SZ = (size_t)_DMABUF_SZ;

static const uintptr_t A35_HEAP = (uintptr_t)_A35_HEAP;
static const size_t A35_HEAP_SZ = (size_t)_A35_HEAP_SZ;

// MP1 names, for shared code:

// MP2's RamDisk is an ordinary object, sized by its conf
static constexpr uint32_t VIRTDRIVE_SZ = RamDiskSizeBytes;

// The heap region (system/sbrk_ca35.cc), which is chosen at startup
size_t heap_region_size();
#define A7_HEAP_SZ heap_region_size()

// The table of symbols plugins can use (.symlist), filled in after linking (cmake/mp2.cmake)
extern char _A7_SYMS[];
extern char _A7_SYMS_END[];
static const uintptr_t A7_SYMS = reinterpret_cast<uintptr_t>(_A7_SYMS);
static const size_t A7_SYMS_SZ = size_t(_A7_SYMS_END - _A7_SYMS);
