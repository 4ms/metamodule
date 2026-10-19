/* Linker script template for STM32MP2 CA35 apps loaded by TF-A BL2 at 0x88000040.
   Copy into your project and adjust memory regions/heap/stack sizes.
   From 4ms/stm32mp2-baremetal multicore_smp/linkscript.ld (includes the cpu1 stack
   region needed by boot/aux_core_startup.s; harmless for single-core apps). */

OUTPUT_FORMAT(elf64-littleaarch64)
OUTPUT_ARCH(aarch64)

ENTRY(_Reset)

/* All regions must stay inside the DDR that TF-A's RISAF4 opens to secure masters:
   0x80000000 - 0x9FFFFFFF (the `ddrram` node in the TF-A dts). Outside it, CPU and DMA
   (e.g. LTDC) accesses are silently blocked. TF-A BL31 context + OP-TEE use 0x81FC0000 - 0x83FFFFFF. */
MEMORY
{
    ROM (rx)       : ORIGIN = 0x88000040, LENGTH = 16M - 0x40
    RAM (rwx)      : ORIGIN = 0x90000000, LENGTH = 128M
    FRAMEBUF (rw)  : ORIGIN = 0x98000000, LENGTH = 32M
}

__HEAP_SIZE = 0x40000;

SECTIONS
{
    .text : {
        *(.vector_table)
        *(.text)
        *(.text*)
					/* Todo: check if we need the next 3 lines */
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */
		*(.eh_frame)

		KEEP (*(.init)) /* libc ctors */
		KEEP (*(.fini)) /* libc dtors */

        . = ALIGN(8);
     } > ROM

	/* .rodata sections (constants, strings, etc.) */
	.rodata :
	{
		. = ALIGN(8);
		*(.rodata)         
		*(.rodata*) 
		. = ALIGN(8);
	} > ROM

	/* used for unwinding (probably not used, but is ignored if your app doens't use exceptions */
	.ARM.extab	 : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >ROM
	.ARM : {
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	} >ROM

	.preinit_array :
	{
		. = ALIGN(8);
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		. = ALIGN(8);
	} > ROM

	.init_array :
	{
		. = ALIGN(8);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
		. = ALIGN(8);
	} > ROM

	.fini_array :
	{
		. = ALIGN(8);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
		. = ALIGN(8);
	} > ROM


    _text_end = .;

    /* .data : AT(ADDR(.text) + SIZEOF(.text)) */
    .data : /*AT(_text_end)*/
    {
        . = ALIGN(8);
        _data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(8);
        _data_end = .;
    } > RAM

    .bss : {
        _bss_start = .;
        *(.bss)
        *(.bss*)   /* required for some malloc calls */
		*(COMMON)  /* required for libc, such as __lock___atexit_recursive_mutex */
        . = ALIGN(8);
        _bss_end = .;
    } > RAM

	.heap (NOLOAD):
	{
		. = ALIGN(16);
		_sheap = .;
		. += __HEAP_SIZE;
		_eheap = .;
	} > RAM

	/* Stacks: in a NOLOAD section so the linker checks they fit in RAM */
	.stacks (NOLOAD):
	{
		. = ALIGN(16);
		_fiq_stack_start = .;
		. += 16K;
		_fiq_stack_end = .;

		_irq_stack_start = .;
		. += 16K;
		_irq_stack_end = .;

		_stack_start = .;
		. += 64K;
		_stack_end = .;

		_cpu1_stack_start = .;
		. += 64K;
		_cpu1_stack_end = .;
	} > RAM

	_irq_stack_size = _irq_stack_end - _irq_stack_start;
	_fiq_stack_size = _fiq_stack_end - _fiq_stack_start;

	/* Memory shared with the M33, at SHAREDMEM_ADDR/SIZE (from CMake). Non-cacheable (mmu_ca35.cc),
	   opened to the M33 in RISAF4. Not zeroed at startup: the A35 initializes what it puts here.
	   .sharedmemindex: pointers to the shared objects, at a fixed address the M33 links too. */
	.sharedmemindex SHAREDMEM_ADDR (NOLOAD) :
	{
		KEEP(*(.sharedmemindex))
		KEEP(*(.sharedmemindex*))
	}
	ASSERT(SIZEOF(.sharedmemindex) <= 0x1000, ".sharedmemindex is bigger than 4kB")

	.sharedmem (SHAREDMEM_ADDR + 0x1000) (NOLOAD) :
	{
		. = ALIGN(64);
		*(.sharedmem)
		*(.sharedmem*)
	}
	ASSERT(ADDR(.sharedmem) + SIZEOF(.sharedmem) <= SHAREDMEM_ADDR + SHAREDMEM_SIZE, ".sharedmem doesn't fit in SHAREDMEM_SIZE")

	/* Display framebuffers (LTDC scans these out). Not zeroed at startup. */
	.framebuffers (NOLOAD):
	{
		. = ALIGN(4096);
		*(.framebuffers)
		*(.framebuffers*)
	} > FRAMEBUF

	/*
	.dma_buffer (NOLOAD) :
	{
		. = ALIGN(8);
		*(.dma_buffer)
		*(.dma_buffer*)
		. = ALIGN(8);
	} > SRAM3
	*/
	

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
