OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_Reset)

INCLUDE system/linker/memory.ld


MEMORY
{
    ROM (rx)			: ORIGIN = _A7_CODE,		LENGTH = _A7_CODE_SZ
    RAM (rx)			: ORIGIN = _A7_RAM,			LENGTH = _A7_RAM_SZ
	VIRTDRIVE (rw)		: ORIGIN = _VIRTDRIVE,		LENGTH = _VIRTDRIVE_SZ 
	FWBUFFER (rw)		: ORIGIN = _FWBUFFER,		LENGTH = _FWBUFFER_SZ 
	HEAP (rw)			: ORIGIN = _A7_HEAP,		LENGTH = _A7_HEAP_SZ
	DMABUF (rw)			: ORIGIN = _DMABUF,			LENGTH = _DMABUF_SZ 

	SYMLIST (r)			: ORIGIN = _A7_SYMS,		LENGTH = _A7_SYMS_SZ

	SHAREDMEMINDEX (rw) : ORIGIN = _A7_SHARED_LIST, LENGTH = _SHARED_LIST_SZ
	SYSRAM (rw)			: ORIGIN = 0x2FFC0000,		LENGTH = 256K
}

/* A7 stacks are at end of RAM */

_shared_list = _A7_SHARED_LIST;

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
		*(.rodata*)
		*(.binary*)
		. = ALIGN(8);
	} > ROM

	.ARM.extab	 : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >ROM
	.ARM : { __exidx_start = .; *(.ARM.exidx*) __exidx_end = .; } >ROM

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

    .data : 
    {
        . = ALIGN(8);
        _data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(8);
        _data_end = .;
    } > ROM

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

	.symlist : {
        FILL(0x00);
        BYTE(0x00);
	} > SYMLIST

	.heap (NOLOAD):
	{
		. = ALIGN(8);
		_sheap = .;
		. += _A7_HEAP_SZ;
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
		*(.noncachable)
		. = ALIGN(8);
		_end_of_sysram = .;
	} > SYSRAM

	.virtdrive (NOLOAD):
	{
		*(.virtdrive)
	} > VIRTDRIVE

	.fwbuffer (NOLOAD):
	{
		*(.fwbuffer)
	} > FWBUFFER

    _user_stack_start = _ram_aligned_end;
    _user_stack_end = _user_stack_start + 0x80000; /* 512k */

    _svc_stack_start = _user_stack_end;
    _svc_stack_end = _svc_stack_start + 0x6000; /* 24k for ISRs*/

    _irq_stack_start = _svc_stack_end;
    _irq_stack_end = _irq_stack_start + 0x100; 

    _fiq_stack_start = _irq_stack_end;
    _fiq_stack_end = _fiq_stack_start + 0x100;

    _auxcore_user_stack_start = _fiq_stack_end;
    _auxcore_user_stack_end = _auxcore_user_stack_start + 0x80000;


	.sharedmemindex (NOLOAD) :
	{
		. = ALIGN(8);
		*(.sharedmemindex)
		*(.sharedmemindex*)
		. = ALIGN(8);
	} > SHAREDMEMINDEX
	

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
