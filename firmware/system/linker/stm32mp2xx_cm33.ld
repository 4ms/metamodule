/* Cortex-M33 (CPU2) firmware, embedded in the A35 image and copied to M33_LOAD_ADDR by the A35.
 *
 * The whole image (vectors, code, rodata, data) is one contiguous block, so the A35 can copy
 * it as a flat binary. .bss is NOLOAD (not in the binary); heap and stack are just the space
 * above it, up to the end of the region.
 *
 * M33_LOAD_ADDR and M33_REGION_SIZE come from CMake (-Wl,--defsym), the same values the A35 uses.
 * In SRAM2, the address is the M33's secure instruction-fetch alias (0x0E060000), which the
 * A35 also has mapped.
 */
ENTRY(Reset_Handler)

_Min_Stack_Size = 0x10000; /* MP1's M4 has 48kB: PatchStorage, FatFS, and LittleFS use a lot of stack */
_DMA_NC_Size = 0x100000;	/* A whole 1MB, so the MPU region boundaries stay simple */
_sdma_nc = M33_LOAD_ADDR + M33_REGION_SIZE - _DMA_NC_Size;

SECTIONS
{
	.isr_vector M33_LOAD_ADDR :
	{
		KEEP(*(.isr_vector))
	}

	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text*)
		*(.glue_7)
		*(.glue_7t)
		*(.eh_frame)
		KEEP (*(.init))
		KEEP (*(.fini))
		. = ALIGN(4);
	}

	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	}

	.ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) }
	.ARM : {
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	}

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	}
	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	}
	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
	}

	/* .data is part of the flat image (LMA == VMA), so startup's copy is a no-op */
	.data :
	{
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	}
	_sidata = LOADADDR(.data);
	_image_end = .;

	.bss (NOLOAD) :
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	}

	/* Not zeroed at startup: keeps its contents when the A35 restarts the M33 */
	.noinit (NOLOAD) :
	{
		. = ALIGN(4);
		*(.noinit)
		*(.noinit*)
		. = ALIGN(4);
		_enoinit = .;
	}

	/* Non-cacheable memory for DMA (the USB controller's event buffers, TRBs, and data buffers),
	   at the top of the region. system_init() zeroes it and makes it non-cacheable in the MPU. */
	.dma_nc _sdma_nc (NOLOAD) :
	{
		*(.dma_nc)
		*(.dma_nc*)
		_edma_nc = .;
	}

	/* Heap: from the end of .noinit up to the stack. Stack: below the DMA memory. */
	_sheap = ALIGN(_enoinit, 8);
	end = _sheap;
	_estack = _sdma_nc;
	_eheap = _estack - _Min_Stack_Size;

	/* Memory shared with the A35 (see the A35 linker script): only the index of pointers is
	   linked here, at the same fixed address as on the A35. */
	.sharedmemindex SHAREDMEM_ADDR (NOLOAD) :
	{
		KEEP(*(.sharedmemindex))
		KEEP(*(.sharedmemindex*))
	}

	.ARM.attributes 0 : { *(.ARM.attributes) }
}

ASSERT(_sheap <= _eheap, "M33 image + .bss + stack don't fit in M33_REGION_SIZE")
ASSERT(_edma_nc <= M33_LOAD_ADDR + M33_REGION_SIZE, ".dma_nc is bigger than _DMA_NC_Size")
ASSERT((M33_LOAD_ADDR & 0x7FF) == 0, "M33_LOAD_ADDR must be 2kB-aligned (VTOR)")
