/* The A35 app (MP2). The addresses are in memory_mp2.ld.
   From 4ms/stm32mp2-baremetal multicore_smp/linkscript.ld (includes the cpu1 stack
   region needed by boot/aux_core_startup.s). */

OUTPUT_FORMAT(elf64-littleaarch64)
OUTPUT_ARCH(aarch64)

ENTRY(_Reset)

INCLUDE system/linker/memory_mp2.ld

MEMORY
{
    ROM (rx)       : ORIGIN = _A35_CODE,	LENGTH = _A35_CODE_SZ
    RAM (rwx)      : ORIGIN = _A35_RAM,		LENGTH = _A35_RAM_SZ
    FRAMEBUF (rw)  : ORIGIN = _FRAMEBUF,	LENGTH = _FRAMEBUF_SZ
}

SECTIONS
{
    .text : {
        *(.vector_table)
        *(.text)
        *(.text*)

		/* Keep symbols that we want to export to plugin API (same as MP1) */
		KEEP(*vcv_plugin*:(.text*))
		KEEP(*jansson*:(.text*))
		KEEP(*pffft*:(.text*))
		/* newlib's lock functions, which plugins import (system/lock_ca35.cc) */
		KEEP(*lock_ca35*(.text*))
					/* Todo: check if we need the next 3 lines */
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */

		KEEP (*(.init)) /* libc ctors */
		KEEP (*(.fini)) /* libc dtors */

        . = ALIGN(8);
     } > ROM

	/* .rodata sections (constants, strings, etc.) */
	.rodata :
	{
		. = ALIGN(8);
		/* Vtables and typeinfo of the plugin API classes, which plugins import even when the
		   firmware doesn't use them. On AArch64 each is in its own COMDAT section, which
		   --gc-sections drops if unused (MP1's are in the object's .rodata, kept with its .text) */
		KEEP(*vcv_plugin*:(.rodata._ZTV* .rodata._ZTI* .rodata._ZTS*))
		*(.rodata)
		*(.rodata*)
		*(.gcc_except_table*) /* C++ exception handling: language-specific data */
		. = ALIGN(8);
	} > ROM

	/* C++ exception handling: the unwind tables. We link without crtbegin.o/crtend.o, so the
	   app registers them with the unwinder itself (system/eh_frame_ca35.cc), and the zero
	   word that crtend.o normally provides terminates them. */
	.eh_frame :
	{
		. = ALIGN(8);
		__eh_frame_start = .;
		KEEP(*(.eh_frame))
		LONG(0)
	} > ROM

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

	/* The names and addresses of the symbols plugins can use (see src/dynload/host_sym_list.hh),
	   filled in after linking (cmake/mp2.cmake). Fixed size, so filling it in moves nothing. */
	.symlist :
	{
		. = ALIGN(8);
		_A7_SYMS = .;
		BYTE(0)
		. = _A7_SYMS + _A35_SYMS_SZ;
		_A7_SYMS_END = .;
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

		/* Same as MP1's A7 (the GUI, patch loading and modules can use a lot of stack) */
		_stack_start = .;
		. += 16M;
		_stack_end = .;

		/* Core 1 runs the GUI and plays modules (core_a35/aux_core.cc): same as MP1's A7 core 2 */
		_cpu1_stack_start = .;
		. += 16M;
		_cpu1_stack_end = .;
	} > RAM

	/* The rest of RAM: the heap, if system/sbrk_ca35.cc can't open its own region of DDR */
	.heap (NOLOAD):
	{
		. = ALIGN(16);
		_sheap = .;
		. = ORIGIN(RAM) + LENGTH(RAM);
		_eheap = .;
	} > RAM

	_irq_stack_size = _irq_stack_end - _irq_stack_start;
	_fiq_stack_size = _fiq_stack_end - _fiq_stack_start;

	/* Memory shared with the M33 (_SHAREDMEM). Non-cacheable (mmu_ca35.cc),
	   opened to the M33 in RISAF4. Not zeroed at startup: the A35 initializes what it puts here.
	   .sharedmemindex: pointers to the shared objects, at a fixed address the M33 links too. */
	.sharedmemindex _SHAREDMEM (NOLOAD) :
	{
		KEEP(*(.sharedmemindex))
		KEEP(*(.sharedmemindex*))
	}
	ASSERT(SIZEOF(.sharedmemindex) <= 0x1000, ".sharedmemindex is bigger than 4kB")

	.sharedmem (_SHAREDMEM + 0x1000) (NOLOAD) :
	{
		. = ALIGN(64);
		*(.sharedmem)
		*(.sharedmem*)
	}
	ASSERT(ADDR(.sharedmem) + SIZEOF(.sharedmem) <= _SHAREDMEM_END, ".sharedmem doesn't fit in _SHAREDMEM")

	/* DMA buffers (e.g. audio), in _DMABUF. Non-cacheable (mmu_ca35.cc).
	   Not zeroed at startup. */
	.dmabuf _DMABUF (NOLOAD) :
	{
		. = ALIGN(64);
		*(.dmabuf)
		*(.dmabuf*)
	}
	ASSERT(ADDR(.dmabuf) + SIZEOF(.dmabuf) <= _DMABUF_END, ".dmabuf doesn't fit in _DMABUF")

	/* Display framebuffers (LTDC scans these out). Not zeroed at startup. */
	.framebuffers (NOLOAD):
	{
		. = ALIGN(4096);
		*(.framebuffers)
		*(.framebuffers*)
	} > FRAMEBUF


  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
