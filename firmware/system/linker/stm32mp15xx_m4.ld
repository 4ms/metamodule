ENTRY(Reset_Handler)

INCLUDE system/linker/memory.ld


MEMORY
{
	m_interrupts (RX)  	: ORIGIN = 0x00000000, LENGTH = 0x00000440
	m_text       (RX)  	: ORIGIN = _M4_CODE, LENGTH = _M4_CODE_SZ

	SHAREDMEMINDEX (RW) : ORIGIN = _M4_SHARED_LIST, LENGTH = _SHARED_LIST_SZ

	/* m_data is for .data (ro and rw) and .bss: all global vars: hopefully all UI assets, default patches */
	/* startup.s copies from somewhre in the middle of .text (probably .rodata) to m_data */
	/* TODO: no need for startup to copy them, just link them to the right place */

	m_data	     (RW)	: ORIGIN = _M4_EXTDATA, LENGTH = _M4_EXTDATA_SZ
	ddr_code     (RX)   : ORIGIN = _M4_EXTCODE, LENGTH = _M4_EXTCODE_SZ
	HEAP         (RW)   : ORIGIN = _M4_HEAP, 	LENGTH = _M4_HEAP_SZ
}

_estack = _M4_STACK_END;
_shared_list = _M4_SHARED_LIST;

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > m_interrupts

  .ddr_code :
  {
	/* *lfs.o(.text.lfs_*) */
	/* *lfs_*.o(.text.lfs_*) */
	/* *(.text.lv_*) */ 
	/* *(.text.*c43yml*) */
  } > ddr_code

  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } > m_text


  .ARM.extab   : { 
  	. = ALIGN(4);
  	*(.ARM.extab* .gnu.linkonce.armextab.*)
  	. = ALIGN(4);
  } > m_text
  
  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } > m_text

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } > m_text
  
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } > m_text
  
  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } > m_text

  /* Constant data */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } > m_data

/*  Uncommenting this allows startup to initialize data */
/*  By copying from _sidata to _sdata */
/*  __DATA_ROM = .; */
/*  _sidata = LOADADDR(.data); */
/*  .data : AT(__DATA_ROM)*/

  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } > m_text

  /* Uncommenting this, prevents any data init */
  _sidata = _sdata;

  .sharedmemindex (NOLOAD) :
  {
	. = ALIGN(8);
	*(.sharedmemindex)
	*(.sharedmemindex*)
	. = ALIGN(8);
  } > SHAREDMEMINDEX
  

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } > m_data

  /* User_heap_stack section, used to check that there is enough RAM left */
  /* ._user_heap_stack : */
  /* { */
  /*   . = ALIGN(8); */
  /*   PROVIDE ( end = . ); */
  /*   PROVIDE ( _end = . ); */
	/* _sheap = .; */
  /*   . = . + _Min_Heap_Size; */
	/* _eheap = .; */
  /*   . = . + _Min_Stack_Size; */
  /*   . = ALIGN(8); */
  /* } > m_data */

  .heap (NOLOAD):
  {
	. = ALIGN(8);
	_sheap = .;
	. += LENGTH(HEAP);
	_eheap = .;
  } > HEAP

  

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }

}
