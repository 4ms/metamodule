OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_Reset)

_DMABUF_SIZE = 1024 * 1024;
_DMABUF_END = 0xE0000000;
_DMABUF_BASE = (_DMABUF_END - _DMABUF_SIZE);

_HEAP_BASE = 0xD0000000;
_HEAP_END = _DMABUF_BASE;
_HEAP_SIZE = _HEAP_END - _HEAP_BASE;

_SHARED_PTR_SIZE = 256;

MEMORY
{
    ROM (rx) 			: ORIGIN = 0xC2000040, 		LENGTH = (1M - 0x40)
    RAM (rw) 			: ORIGIN = 0xC0200000, 		LENGTH = 1M
	HEAP (rw) 			: ORIGIN = _HEAP_BASE,		LENGTH = _HEAP_SIZE
	DMABUF (rw) 		: ORIGIN = _DMABUF_BASE, 	LENGTH = _DMABUF_SIZE
	SHAREDMEM (rw) 		: ORIGIN = 0x30040000, 		LENGTH = (128K - _SHARED_PTR_SIZE) /* shared with cm4 */
	SYSRAM (rw) 		: ORIGIN = 0x2FFC0000, 		LENGTH = 192K
	SYSRAM_STACK (rw) 	: ORIGIN = 0x2FFF0000, 		LENGTH = 64K
}

_params_ptr = ORIGIN(SHAREDMEM) + LENGTH(SHAREDMEM);
/* 0x1005FF00: 256 Bytes of shared memory addresses = 64 pointers */

SECTIONS
{
    .text : {
        *(.vector_table)
		*(.resethandler)
		*(.irqhandler)
        *(.text)
        *(.text*)
					/* Todo: check if we need the next 5 lines */
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */
		*(.eh_frame)
		KEEP (*(.init))
		KEEP (*(.fini))

        . = ALIGN(8);
     } > ROM

	.rodata :
	{
		. = ALIGN(8);
		*(.rodata)         /* .rodata sections (constants, strings, etc.) */
		*(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
		. = ALIGN(8);
	} > ROM

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

    .data : AT(_text_end)
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
		. = ALIGN(256);
		_ram_aligned_end = .;
    } > RAM

	.heap (NOLOAD):
	{
		. = ALIGN(8);
		_sheap = .;
		. += _HEAP_SIZE;
		_eheap = .;
	} > HEAP

	.ddma (NOLOAD):
	{
		. = ALIGN(8);
        *(.ddma)
	} > DMABUF

	.sysram (NOLOAD):
	{
		. = ALIGN(8);
		*(.sysram)
		. = ALIGN(8);
		_end_of_sysram = .;
	} > SYSRAM

	/* User Stack: 0x2FFF0000 - 0x2FFFFD00 */
    _user_stack_start = ORIGIN(SYSRAM_STACK);
    _user_stack_end = _user_stack_start + 0x8000 - 0x200; /* 32k - 512B  */

    _svc_stack_start = _user_stack_end;
    _svc_stack_end = _svc_stack_start + 0x8000; /* 32k for ISRs*/

    _irq_stack_start = _svc_stack_end;
    _irq_stack_end = _irq_stack_start + 0x100; 

    _fiq_stack_start = _irq_stack_end;
    _fiq_stack_end = _fiq_stack_start + 0x100;


	.shared_memory (NOLOAD) :
	{
		. = ALIGN(8);
		*(.shared_memory)
		*(.shared_memory*)
		. = ALIGN(8);
	} > SHAREDMEM
	

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
