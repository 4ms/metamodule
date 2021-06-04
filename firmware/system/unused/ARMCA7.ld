__ROM_BASE = 0xC2000040;
__ROM_SIZE = 0x00100000;

__RAM_BASE = 0xC0200000;
__RAM_SIZE = 0x00100000;

__RW_DATA_SIZE = 0x00100000;
__ZI_DATA_SIZE = 0x000F0000;

__STACK_SIZE = 0x00008000;
__HEAP_SIZE = 0x00040000;

__UND_STACK_SIZE = 0x00001000;
__ABT_STACK_SIZE = 0x00001000;
__SVC_STACK_SIZE = 0x00001000;
__IRQ_STACK_SIZE = 0x00001000;
__FIQ_STACK_SIZE = 0x00001000;
__TTB_BASE = 0xC0500000;
__TTB_SIZE = 0x00005000;


MEMORY
{
  ROM (rx)   : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
  L_TTB (rw) : ORIGIN = __TTB_BASE, LENGTH = __TTB_SIZE 
  RAM (rwx)  : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {

        Image$$VECTORS$$Base = .;
        * (RESET)
        KEEP(*(.isr_vector))
        Image$$VECTORS$$Limit = .;

        *(SVC_TABLE)
        *(.text)
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        Image$$RO_DATA$$Base = .;
        *(.rodata)
        *(.rodata*)
        Image$$RO_DATA$$Limit = .;

        KEEP(*(.eh_frame*))
    } > ROM

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > ROM

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > ROM
    __exidx_end = .;


    .copy.table :
    {
        . = ALIGN(4);
        __copy_table_start__ = .;
        LONG (__etext)
        LONG (__data_start__)
        LONG (__data_end__ - __data_start__)
        __copy_table_end__ = .;
    } > ROM

    .zero.table :
    {
        . = ALIGN(4);
        __zero_table_start__ = .;
        LONG (__bss_start__)
        LONG (__bss_end__ - __bss_start__)
        __zero_table_end__ = .;
    } > ROM

    __etext = .;
        
    .ttb :
    {
        Image$$TTB$$ZI$$Base = .;
        . += __TTB_SIZE;
        Image$$TTB$$ZI$$Limit = .;
    } > L_TTB

    .data : AT (__etext)
    {
        Image$$RW_DATA$$Base = .;
        __data_start__ = .;
        *(vtable)
        *(.data*)
        Image$$RW_DATA$$Limit = .;

        . = ALIGN(4);
        /* preinit data */
        PROVIDE (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > RAM

    
    .bss ALIGN(0x400):
    {
        Image$$ZI_DATA$$Base = .;
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
        Image$$ZI_DATA$$Limit = .;
        __end__ = .;
        end = __end__;
    } > RAM

    .heap (NOLOAD):
    {
        . = ALIGN(8);
        Image$$HEAP$$ZI$$Base = .;
		_sheap = .;
        . += __HEAP_SIZE;
        Image$$HEAP$$ZI$$Limit = .;
		_eheap = .;
        __HeapLimit = .;
    } > RAM  

    .stack (NOLOAD):
    {
        . = ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE - __FIQ_STACK_SIZE - __IRQ_STACK_SIZE - __SVC_STACK_SIZE - __ABT_STACK_SIZE - __UND_STACK_SIZE;
        . = ALIGN(8);
        
        __StackTop = .;
        Image$$SYS_STACK$$ZI$$Base = .;
        . += __STACK_SIZE;
        Image$$SYS_STACK$$ZI$$Limit = .;
        __stack = .;

        Image$$FIQ_STACK$$ZI$$Base = .;
        . += __FIQ_STACK_SIZE;
        Image$$FIQ_STACK$$ZI$$Limit = .;

        Image$$IRQ_STACK$$ZI$$Base = .;
        . += __IRQ_STACK_SIZE;
        Image$$IRQ_STACK$$ZI$$Limit = .;

        Image$$SVC_STACK$$ZI$$Base = .;
        . += __SVC_STACK_SIZE;
        Image$$SVC_STACK$$ZI$$Limit = .;

        Image$$ABT_STACK$$ZI$$Base = .;
        . += __ABT_STACK_SIZE;
        Image$$ABT_STACK$$ZI$$Limit = .;

        Image$$UND_STACK$$ZI$$Base = .;
        . += __UND_STACK_SIZE;
        Image$$UND_STACK$$ZI$$Limit = .;
        
    } > RAM
}
