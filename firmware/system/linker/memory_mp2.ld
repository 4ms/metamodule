/* MP2's memory map: the one place its fixed addresses are set (MP1's is memory.ld). The linker
   scripts (stm32mp2xx_ca35.ld, stm32mp2xx_cm33.ld) INCLUDE it, and src/mp2-stubs/ld.h brings it into
   C and C++.

   DDR: the devboard has 2GB, 0x80000000-0xFFFFFFFF. TF-A's DDR firewall (RISAF4) opens only
   0x80000000-0x9FFFFFFF to secure masters. Accesses outside the regions opened in RISAF4 are
   silently blocked (reads return 0). TF-A BL31 and OP-TEE use 0x81FC0000-0x83FFFFFF. */

_TFA_DDR		= 0x80000000;
_TFA_DDR_END	= 0xA0000000;

/* The A35 image. TF-A BL2 loads it here (set by the TF-A build), after its 0x40-byte header */
_A35_CODE		= 0x88000040;
_A35_CODE_SZ	= 16M - 0x40;
_A35_CODE_END	= 0x89000000;

/* Size of .symlist, the table of symbols plugins can use, in the A35 image (src/dynload/host_sym_list.hh) */
_A35_SYMS_SZ	= 1M;

/* The M33's memory: code, data, heap, stack, and its DMA memory at the top. The A35 loads the M33
   image to the start, and opens the region to the M33 in RISAF4 (src/core_a35/main.cc).
   (The M33 can also run from SRAM2: 0x0E060000, size 0x1F000, its secure instruction-fetch alias.) */
_M33_REGION		= 0x8C000000;
_M33_REGION_SZ	= 32M;
_M33_REGION_END	= 0x8E000000;

/* The A35's data, bss and stacks. The rest of it is the heap if the A35 can't open its own (see
   _A35_HEAP) */
_A35_RAM		= 0x90000000;
_A35_RAM_SZ		= 128M;
_A35_RAM_END	= 0x98000000;

/* Display framebuffers (LTDC) */
_FRAMEBUF		= 0x98000000;
_FRAMEBUF_SZ	= 32M;
_FRAMEBUF_END	= 0x9A000000;

/* Memory shared by the A35 and M33: non-cacheable on both, opened to both cores in RISAF4.
   Starts with .sharedmemindex (the pointers to the shared objects, at a fixed address both cores
   link), followed by .sharedmem (the objects). Every buffer the A35 asks the M33 to read a file into
   (or write one from) must be in here. */
_SHAREDMEM		= 0x9A000000;
_SHAREDMEM_SZ	= 32M;
_SHAREDMEM_END	= 0x9C000000;

/* Non-cacheable memory for DMA buffers (audio). A35 only. (MP1 uses SYSRAM for this) */
_DMABUF			= 0x9C000000;
_DMABUF_SZ		= 2M;
_DMABUF_END		= 0x9C200000;

/* The A35's heap: DDR above TF-A's window, which the A35 opens to itself in RISAF4 at startup
   (system/sbrk_ca35.cc). It ends below 0xE0000000, where the M33's address map has its private
   peripheral bus: the M33 reads and writes the top of the heap while serving the developer drive. */
_A35_HEAP		= 0xA0000000;
_A35_HEAP_SZ	= 1024M;
_A35_HEAP_END	= 0xE0000000;


ASSERT(_A35_CODE + _A35_CODE_SZ == _A35_CODE_END, "_A35_CODE + _A35_CODE_SZ != _A35_CODE_END")
ASSERT(_M33_REGION + _M33_REGION_SZ == _M33_REGION_END, "_M33_REGION + _M33_REGION_SZ != _M33_REGION_END")
ASSERT(_A35_RAM + _A35_RAM_SZ == _A35_RAM_END, "_A35_RAM + _A35_RAM_SZ != _A35_RAM_END")
ASSERT(_FRAMEBUF + _FRAMEBUF_SZ == _FRAMEBUF_END, "_FRAMEBUF + _FRAMEBUF_SZ != _FRAMEBUF_END")
ASSERT(_SHAREDMEM + _SHAREDMEM_SZ == _SHAREDMEM_END, "_SHAREDMEM + _SHAREDMEM_SZ != _SHAREDMEM_END")
ASSERT(_DMABUF + _DMABUF_SZ == _DMABUF_END, "_DMABUF + _DMABUF_SZ != _DMABUF_END")
ASSERT(_A35_HEAP + _A35_HEAP_SZ == _A35_HEAP_END, "_A35_HEAP + _A35_HEAP_SZ != _A35_HEAP_END")

ASSERT(_A35_CODE_END <= _M33_REGION && _M33_REGION_END <= _A35_RAM && _A35_RAM_END <= _FRAMEBUF &&
	   _FRAMEBUF_END <= _SHAREDMEM && _SHAREDMEM_END <= _DMABUF && _DMABUF_END <= _TFA_DDR_END &&
	   _TFA_DDR_END <= _A35_HEAP, "MP2 memory regions overlap, or leave TF-A's DDR window")
ASSERT(_A35_HEAP_END <= 0xE0000000, "The A35 heap must end below the M33's private peripheral bus")

/* The A35 MMU maps these in 2MB blocks (system/mmu_ca35.cc) */
ASSERT(_SHAREDMEM % 2M == 0 && _SHAREDMEM_SZ % 2M == 0, "_SHAREDMEM must be whole 2MB blocks")
ASSERT(_DMABUF % 2M == 0 && _DMABUF_SZ % 2M == 0, "_DMABUF must be whole 2MB blocks")

/* VTOR */
ASSERT(_M33_REGION % 2K == 0, "_M33_REGION must be 2kB-aligned")
