/* Linker script to configure memory regions. */

_virtio_shmem_size = 32K;  /* size of the virtio pool used fior rpmsg communication */

/* Memories definition */
MEMORY
{
  NS_VECTOR_TBL (xrw)   : ORIGIN = 0x80100000,	LENGTH = 0x00000600
  FLASH         (rx)    : ORIGIN = 0x80100600,  LENGTH = 8M - LENGTH(NS_VECTOR_TBL)
  RAM           (rwx)   : ORIGIN = 0x80A00000,  LENGTH = 8M
  IPC_SHMEM_1   (rw)    : ORIGIN = 0x81200000,  LENGTH = 1M - _virtio_shmem_size
  VIRTIO_SHMEM  (rw)    : ORIGIN = ORIGIN(IPC_SHMEM_1) + LENGTH(IPC_SHMEM_1), LENGTH = _virtio_shmem_size
  SCMI_SHMEM    (rw)    : ORIGIN = 0x0A062000,	LENGTH = 0x1000
}

 /* Symbols needed for OpenAMP to enable rpmsg */
__OPENAMP_region_start__  = ORIGIN(VIRTIO_SHMEM);
__OPENAMP_region_end__ = ORIGIN(VIRTIO_SHMEM)+LENGTH(VIRTIO_SHMEM);

 /* Symbols needed for scmiagent to enable mailbox communication */
__SCMI_SHM_region_start__  = ORIGIN(SCMI_SHMEM);
__SCMI_SHM_region_end__    = ORIGIN(SCMI_SHMEM)+LENGTH(SCMI_SHMEM);

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapBase
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */
ENTRY(Reset_Handler)

SECTIONS
{
  /* The startup code into "NS_VECTOR_TBL" Ram type memory
   * Do not update the ".isr_vectors" section name. the name
   * is used by the Linux kernel to retrieve the address
   * of the vector table*/
	.isr_vectors :
	{
		. = ALIGN(4);
		KEEP(*(.vectors))
		__Vectors_End = .;
		__Vectors_Size = __Vectors_End - __Vectors;
		__end__ = .;
		. = ALIGN(4);
	} >NS_VECTOR_TBL

	.resource_table :
	{
		. = ALIGN(4);
		KEEP (*(.resource_table*))
		. = ALIGN(4);
	} >IPC_SHMEM_1

	.text :
	{
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

		*(.rodata*)

		KEEP(*(.eh_frame*))
	} > FLASH

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	/* To copy multiple ROM to RAM sections,
	 * uncomment .copy.table section and,
	 * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
	/*
	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		LONG (__etext2)
		LONG (__data2_start__)
		LONG (__data2_end__ - __data2_start__)
		__copy_table_end__ = .;
	} > FLASH
	*/

	/* To clear multiple BSS sections,
	 * uncomment .zero.table section and,
	 * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
	/*
	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
		LONG (__bss2_start__)
		LONG (__bss2_end__ - __bss2_start__)
		__zero_table_end__ = .;
	} > FLASH
	*/

	__etext = .;
	
    /* Used by the startup to initialize data */
    _sidata = LOADADDR(.data);
	
	.data : AT (__etext)
	{
		__data_start__ = .;
		_sdata = .;        /* create a global symbol at data start */
		*(vtable)
		*(.data*)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		KEEP(*(.jcr*))
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;
        _edata = .;        /* define a global symbol at data end */
   	} > RAM

	.bss :
	{
		. = ALIGN(4);
        _sbss = .;         /* define a global symbol at bss start */
        __bss_start__ = _sbss;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
        _ebss = .;         /* define a global symbol at bss end */
        __bss_end__ = _ebss;  
	} > RAM

	.heap (COPY):
	{
		__HeapBase = .;
		__end__ = .;
		end = __end__;
		KEEP(*(.heap*))
		__HeapLimit = .;
	} > RAM

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		KEEP(*(.stack*))
	} > RAM

  /* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(RAM) + LENGTH(RAM);
  __StackLimit = __StackTop - SIZEOF(.stack_dummy);
  PROVIDE(__stack = __StackTop);
  PROVIDE(_estack = __StackTop);

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
