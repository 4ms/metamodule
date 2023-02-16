ENTRY(Reset_Handler)


_SHARED_PTR_SIZE = 256;
_SHAREDIDX_START = (0x10060000 - _SHARED_PTR_SIZE);

_estack = _SHAREDIDX_START;

MEMORY
{
	m_interrupts (RX)  	: ORIGIN = 0x00000000, LENGTH = 0x00000440
	m_text       (RX)  	: ORIGIN = 0x10000000, LENGTH = 0x00050000 /*320kB for code*/

    /* Stack: 0x10050000 to 0x1005FF00 == >63kB stack*/

	SHAREDMEMINDEX (RW) : ORIGIN = _SHAREDIDX_START, LENGTH = _SHARED_PTR_SIZE

	/* m_data is for .data (ro) and .bss: all global vars: hopefully all UI assets, default patches */
	m_data	     (RW)	: ORIGIN = 0xC0200000, LENGTH = 30M  /* END = 0xC200'0000 */
	HEAP         (RW)   : ORIGIN = 0xC5000000, LENGTH = 128M /* END = 0xCD00'0000 */
}

_params_ptr = ORIGIN(SHAREDMEMINDEX);
/* 0x1005FF00: 256 Bytes of shared memory addresses = 64 pointers */

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > m_interrupts
 

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

  /* Constant data into ROM memory*/
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
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

  /* Used by the startup to initialize data */
  __DATA_ROM = .;
  _sidata = LOADADDR(.data);

  /* Initialized data sections */
  .data :  AT(__DATA_ROM)
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } > m_data

  __DATA_END = __DATA_ROM + (_edata - _sdata);
  text_end = ORIGIN(m_text) + LENGTH(m_text);
  ASSERT(__DATA_END <= text_end, "region m_text overflowed with text and data")

  /* .resource_table : */
  /* { */
  /*   . = ALIGN(4); */
  /*   KEEP (*(.resource_table*)) */
  /*   . = ALIGN(4); */
  /* } > m_data */

	.sharedmemindex (NOLOAD) :
	{
		. = ALIGN(8);
		*(.sharedmemindex)
		*(.sharedmemindex*)
		. = ALIGN(8);
	} > SHAREDMEMINDEX
  

  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
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
