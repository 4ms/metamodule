#pragma once
#include <stdint.h>

// Defined in linker scripts:

extern uint32_t _UNUSED0[];
extern uint32_t _UNUSED0_SZ[];
extern uint32_t _UNUSED0_END[];

extern uint32_t _TTB[];
extern uint32_t _TTB_SZ[];
extern uint32_t _TTB_END[];

//not used
extern uint32_t _M4_EXTCODE[];
extern uint32_t _M4_EXTCODE_SZ[];
extern uint32_t _M4_EXTCODE_END[];

//SO
extern uint32_t _M4_EXTDATA[];
extern uint32_t _M4_EXTDATA_SZ[];
extern uint32_t _M4_EXTDATA_END[];

//N
extern uint32_t _A7_CODE[];
extern uint32_t _A7_CODE_SZ[];
extern uint32_t _A7_CODE_END[];

//N-RW
extern uint32_t _A7_RAM[];
extern uint32_t _A7_RAM_SZ[];
extern uint32_t _A7_RAM_END[];

//SO
extern uint32_t _M4_HEAP[];
extern uint32_t _M4_HEAP_SZ[];
extern uint32_t _M4_HEAP_END[];

//SO
extern uint32_t _VIRTDRIVE[];
extern uint32_t _VIRTDRIVE_SZ[];
extern uint32_t _VIRTDRIVE_END[];

//N-RW
extern uint32_t _A7_HEAP[];
extern uint32_t _A7_HEAP_SZ[];
extern uint32_t _A7_HEAP_END[];

//SO
extern uint32_t _DMABUF[];
extern uint32_t _DMABUF_SZ[];
extern uint32_t _DMABUF_END[];

//SRAM1-3: Device-RW
extern uint32_t _M4_CODE[];
extern uint32_t _M4_CODE_SZ[];
extern uint32_t _M4_CODE_END[];

//SRAM4: Device-RW
extern uint32_t _M4_STACK[];
extern uint32_t _M4_STACK_SZ[];
extern uint32_t _M4_STACK_END[];

//SRAM4: Device-RW
extern uint32_t _M4_SHARED_LIST[];
extern uint32_t _A7_SHARED_LIST[];
extern uint32_t _SHARED_LIST_SZ[];
extern uint32_t _M4_SHARED_LIST_END[];

//Not listed:
//SYSRAM is SO

// as uint32_t's:
// (some are commented to prevent unused-variable warnings)

// static uint32_t UNUSED0 = (uint32_t)_UNUSED0;
// static uint32_t UNUSED0_SZ = (uint32_t)_UNUSED0_SZ;
// static uint32_t UNUSED0_END = (uint32_t)_UNUSED0_END;

static uint32_t TTB = (uint32_t)_TTB;
// static uint32_t TTB_SZ = (uint32_t)_TTB_SZ;
// static uint32_t TTB_END = (uint32_t)_TTB_END;

// static uint32_t M4_EXTCODE = (uint32_t)_M4_EXTCODE;
// static uint32_t M4_EXTCODE_SZ = (uint32_t)_M4_EXTCODE_SZ;
// static uint32_t M4_EXTCODE_END = (uint32_t)_M4_EXTCODE_END;

static uint32_t M4_EXTDATA = (uint32_t)_M4_EXTDATA;
static uint32_t M4_EXTDATA_SZ = (uint32_t)_M4_EXTDATA_SZ;
// static uint32_t M4_EXTDATA_END = (uint32_t)_M4_EXTDATA_END;

static uint32_t A7_CODE = (uint32_t)_A7_CODE;
static uint32_t A7_CODE_SZ = (uint32_t)_A7_CODE_SZ;
// static uint32_t A7_CODE_END = (uint32_t)_A7_CODE_END;

static uint32_t A7_RAM = (uint32_t)_A7_RAM;
static uint32_t A7_RAM_SZ = (uint32_t)_A7_RAM_SZ;
// static uint32_t A7_RAM_END = (uint32_t)_A7_RAM_END;

static uint32_t M4_HEAP = (uint32_t)_M4_HEAP;
static uint32_t M4_HEAP_SZ = (uint32_t)_M4_HEAP_SZ;
// static uint32_t M4_HEAP_END = (uint32_t)_M4_HEAP_END;

static uint32_t VIRTDRIVE = (uint32_t)_VIRTDRIVE;
static uint32_t VIRTDRIVE_SZ = (uint32_t)_VIRTDRIVE_SZ;
// static uint32_t VIRTDRIVE_END = (uint32_t)_VIRTDRIVE_END;

static uint32_t A7_HEAP = (uint32_t)_A7_HEAP;
static uint32_t A7_HEAP_SZ = (uint32_t)_A7_HEAP_SZ;
// static uint32_t A7_HEAP_END = (uint32_t)_A7_HEAP_END;

static uint32_t DMABUF = (uint32_t)_DMABUF;
static uint32_t DMABUF_SZ = (uint32_t)_DMABUF_SZ;
// static uint32_t DMABUF_END = (uint32_t)_DMABUF_END;

// static uint32_t M4_CODE = (uint32_t)_M4_CODE;
// static uint32_t M4_CODE_SZ = (uint32_t)_M4_CODE_SZ;
// static uint32_t M4_CODE_END = (uint32_t)_M4_CODE_END;

// static uint32_t M4_STACK = (uint32_t)_M4_STACK;
// static uint32_t M4_STACK_SZ = (uint32_t)_M4_STACK_SZ;
// static uint32_t M4_STACK_END = (uint32_t)_M4_STACK_END;

// static uint32_t M4_SHARED_LIST = (uint32_t)_M4_SHARED_LIST;
// static uint32_t A7_SHARED_LIST = (uint32_t)_A7_SHARED_LIST;
// static uint32_t SHARED_LIST_SZ = (uint32_t)_SHARED_LIST_SZ;
// static uint32_t M4_SHARED_LIST_END = (uint32_t)_M4_SHARED_LIST_END;
