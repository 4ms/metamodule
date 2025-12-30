#pragma once
#include <stdint.h>

// Defined in linker scripts:

extern uint32_t _TTB[];
extern uint32_t _TTB_SZ[];
extern uint32_t _TTB_END[];

extern uint32_t _A35_SYMS[];
extern uint32_t _A35_SYMS_SZ[];
extern uint32_t _A35_SYMS_END[];

// SO
extern uint32_t _M33_RODATA[];
extern uint32_t _M33_RODATA_SZ[];
extern uint32_t _M33_RODATA_END[];

// N
extern uint32_t _A35_CODE[];
extern uint32_t _A35_CODE_SZ[];
extern uint32_t _A35_CODE_END[];

//N-RW
extern uint32_t _A35_RAM[];
extern uint32_t _A35_RAM_SZ[];
extern uint32_t _A35_RAM_END[];

//SO
extern uint32_t _M33_HEAP[];
extern uint32_t _M33_HEAP_SZ[];
extern uint32_t _M33_HEAP_END[];

//SO
extern uint32_t _VIRTDRIVE[];
extern uint32_t _VIRTDRIVE_SZ[];
extern uint32_t _VIRTDRIVE_END[];
extern uint32_t _CONSOLEBUF[];
extern uint32_t _CONSOLEBUF_SZ[];
extern uint32_t _CONSOLEBUF_END[];
extern uint32_t _FWBUFFER[];
extern uint32_t _FWBUFFER_SZ[];
extern uint32_t _FWBUFFER_END[];

//N-RW
extern uint32_t _A35_HEAP[];
extern uint32_t _A35_HEAP_SZ[];
extern uint32_t _A35_HEAP_END[];

//SO
extern uint32_t _DMABUF[];
extern uint32_t _DMABUF_SZ[];
extern uint32_t _DMABUF_END[];

//SRAM1-3: Device-RW
extern uint32_t _M33_CODE[];
extern uint32_t _M33_CODE_A35[];
extern uint32_t _M33_CODE_SZ[];
extern uint32_t _M33_CODE_END[];

// RETRAM
extern uint32_t _M33_VECT[];
extern uint32_t _M33_VECT_A35[];
extern uint32_t _M33_VECT_SZ[];
extern uint32_t _M33_VECT_END[];

extern uint32_t _M33_STACK[];
extern uint32_t _M33_STACK_SZ[];
extern uint32_t _M33_STACK_END[];

//SRAM33: Device-RW
extern uint32_t _M33_SHARED_LIST[];
extern uint32_t _A35_SHARED_LIST[];
extern uint32_t _SHARED_LIST_SZ[];
extern uint32_t _M33_SHARED_LIST_END[];

//Not listed:
//SYSRAM is SO

static const uint32_t TTB = (uint32_t)_TTB;
static const uint32_t TTB_END = (uint32_t)_TTB_END;

static const uint32_t M33_RODATA = (uint32_t)_M33_RODATA;
static const uint32_t M33_RODATA_SZ = (uint32_t)_M33_RODATA_SZ;

static const uint32_t A35_CODE = (uint32_t)_A35_CODE;
static const uint32_t A35_CODE_SZ = (uint32_t)_A35_CODE_SZ;
static const uint32_t A35_CODE_END = (uint32_t)_A35_CODE_END;

static const uint32_t A35_RAM = (uint32_t)_A35_RAM;
static const uint32_t A35_RAM_SZ = (uint32_t)_A35_RAM_SZ;

static const uint32_t M33_HEAP = (uint32_t)_M33_HEAP;
static const uint32_t M33_HEAP_SZ = (uint32_t)_M33_HEAP_SZ;

static const uint32_t VIRTDRIVE = (uint32_t)_VIRTDRIVE;
static const uint32_t VIRTDRIVE_SZ = (uint32_t)_VIRTDRIVE_SZ;

static const uint32_t CONSOLEBUF = (uint32_t)_CONSOLEBUF;
static const uint32_t CONSOLEBUF_SZ = (uint32_t)_CONSOLEBUF_SZ;

static const uint32_t FWBUFFER = (uint32_t)_FWBUFFER;
static const uint32_t FWBUFFER_SZ = (uint32_t)_FWBUFFER_SZ;

static const uint32_t A35_HEAP = (uint32_t)_A35_HEAP;
static const uint32_t A35_HEAP_SZ = (uint32_t)_A35_HEAP_SZ;
// Legacy alias:
static const uint32_t A7_HEAP_SZ = (uint32_t)_A35_HEAP_SZ;

static const uint32_t DMABUF = (uint32_t)_DMABUF;
static const uint32_t DMABUF_SZ = (uint32_t)_DMABUF_SZ;

static const uint32_t M33_VECT = (uint32_t)_M33_VECT;
static const uint32_t M33_VECT_A35 = (uint32_t)_M33_VECT_A35;
static const uint32_t M33_VECT_SZ = (uint32_t)_M33_VECT_SZ;
static const uint32_t M33_VECT_END = (uint32_t)_M33_VECT_END;

static const uint32_t M33_CODE = (uint32_t)_M33_CODE;
static const uint32_t M33_CODE_A35 = (uint32_t)_M33_CODE_A35;
static const uint32_t M33_CODE_SZ = (uint32_t)_M33_CODE_SZ;
static const uint32_t M33_CODE_END = (uint32_t)_M33_CODE_END;

static const uint32_t A35_SYMS = (uint32_t)_A35_SYMS;
static const uint32_t A35_SYMS_SZ = (uint32_t)_A35_SYMS_SZ;
static const uint32_t A35_SYMS_END = (uint32_t)_A35_SYMS_END;
