/*
********************************************************************************
**
**  File        : stm32mp23xx_SYSRAM_a35.ld
**
**  Abstract    : Linker script for STM32MP2 series
**                A35 EL1 Aarch32 application in SYSRAM to be launched
**                by EL3 launcher/switcher and to be booted from memory storage
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed "as is" without any warranty
**                of any kind.
**
********************************************************************************
** @attention
**
** <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
** All rights reserved.</center></h2>
**
** This software component is licensed by ST under BSD 3-Clause license,
** the License; You may not use this file except in compliance with the
** License. You may obtain a copy of the License at:
**                       opensource.org/licenses/BSD-3-Clause
**
********************************************************************************
*/

/******************/
/* Memory mapping */
/******************/
/*** Memory regions
  ROMcode data located at begining of SYSRAM
    RAM Data area used by ROMcode running in BOOTROM in "A35 boot from flash" mode
    9 KBytes
  Image Header located in SYSRAM after ROMcode data
    Data structure used for loading A35 application from flash
    512 Bytes
  EL3 Launcher/Switcher located in SYSRAM between Image Header and A35 application
    A35 Aarch64 EL3 code for switching A35 from Aarch64 EL3 to Aarch32 EL1
    14.5 KBytes
    Actually bundled with image header and application in Flash Image
  IPC shared memory
    Buffer used for communication between A35 and M33 processors
    32 KBytes located at end of SRAM2
*/

/* SYSRAM
   Size 256K
   Base address 0x20000000
   Notes : clocked by ROMcode, RIF protection tuned dynamically
           by EL3 Launcher/Switcher for A35 secure/non-secure accesses
  ------------------------------------------------------------------
  | AREA                        | Start Offs | End Offs   | Size   |
  |-----------------------------|------------|------------|--------|
  | ROMcode data                | 0x00000000 | 0x000023FF |     9K |
  | Image Header                | 0x00002400 | 0x000025FF |    512 |
  | EL3 Launcher/Switcher       | 0x00002600 | 0x00005FFF |  14.5K |
  | A35 Application code & data | 0x00006000 | 0x0003FFFF |   232K |
  ------------------------------------------------------------------
*/

/* MCU SRAM1/SRAM2
   Size 128K + 128K
   Base address 0x20040000
   Notes : not managed (not loadable) by ROMcode
           A35 application shall clock it and tune its RIF protection
           (secure/non-secure accesses) before use
  --------------------------------------------------------
  | AREA              | Start Offs | End Offs   | Size   |
  |-------------------|------------|------------|--------|
  | Application data  | 0x00000000 | 0x0001FFFF |   128K |
  | Application data  | 0x00020000 | 0x00037FFF |    96K |
  | IPC shared memory | 0x00038000 | 0x0003FFFF |    32K |
  --------------------------------------------------------
*/

/* RETRAM
   Size 128K
   Base address 0x20080000
   Notes : not managed (not loadable) by ROMcode
           clocked by default
           A35 application shall tune its RIF protection
           (secure/non-secure accesses) before use
  -------------------------------------------------------
  | AREA             | Start Offs | End Offs   | Size   |
  |------------------|------------|------------|--------|
  | M33 Application  | 0x00000000 | 0x0001DFFF |   120K |
  | M33 NSC / veener | 0x0001E000 | 0x0001FFFF |     8K |
  -------------------------------------------------------
*/

/* VEDRAM
   Size 128K
   Base address 0x200A0000
   Notes : not managed (not loadable) by ROMcode
           A35 application shall clock it, allow ICN access to it and tune
           its RIF protection (secure/non-secure accesses) before use
  -------------------------------------------------------
  | AREA             | Start Offs | End Offs   | Size   |
  |------------------|------------|------------|--------|
  | Application data | 0x00000000 | 0x0001FFFF |   128K |
  -------------------------------------------------------
*/

/* DDR
   Size 1G
   Base address 0x80000000
   Notes : not managed (not loadable) by ROMcode
           A35 application shall initialised it by using a DDR type specific
           driver, and tune its RIF protection
           (CID-filtering & secure/non-secure accesses) before use
  -------------------------------------------------------
  | AREA             | Start Offs | End Offs   | Size   |
  |------------------|------------|------------|--------|
  | Application data | 0x00000000 | 0x3FFFFFFF |  1024K |
  -------------------------------------------------------
*/

/* Base address for cacheability according to MMU settings at EL1 */
/* managed in component stm32mp2xx_a35_el1_pagetables.s           */
NON_CACHEABLE_RAM_BASE = 0x20000000;
CACHEABLE_RAM_BASE     = 0x30000000;

/* Memory regions sizes */
/* in SYSRAM */
BOOTROM_AREA_SIZE    = 9K;
IMAGE_HEADER_SIZE    = 512;
EL3_LENGTH           = 14K + 512;
SYSRAM_RESERVED_SIZE = BOOTROM_AREA_SIZE + IMAGE_HEADER_SIZE + EL3_LENGTH;
/* in RETRAM */
NSC_SIZE             = 8K;
/* in SRAM */
IPC_SHM_SIZE         = 32K;

MEMORY
{
  /* Global memory layout : uncomment needed lines */
    SYSRAM (rwx)      : ORIGIN = NON_CACHEABLE_RAM_BASE + 0x00000000,  LENGTH = 256K
/*  SYSRAM (rwx)      : ORIGIN = CACHEABLE_RAM_BASE + 0x00000000,  LENGTH = 256K */
    SRAM1 (rwx)       : ORIGIN = NON_CACHEABLE_RAM_BASE + 0x00040000,  LENGTH = 128K
/*  SRAM1 (rwx)       : ORIGIN = CACHEABLE_RAM_BASE + 0x00040000,  LENGTH = 128K */
/*  SRAM2 (rwx)       : ORIGIN = NON_CACHEABLE_RAM_BASE + 0x00060000,  LENGTH = 128K */
/*  SRAM2 (rwx)       : ORIGIN = CACHEABLE_RAM_BASE + 0x00060000,  LENGTH = 128K */
/*  RETRAM (rwx)      : ORIGIN = NON_CACHEABLE_RAM_BASE + 0x00080000,  LENGTH = 128K */
/*  RETRAM (rwx)      : ORIGIN = CACHEABLE_RAM_BASE + 0x00080000,  LENGTH = 128K */
/*  VEDRAM (rwx)      : ORIGIN = NON_CACHEABLE_RAM_BASE + 0x000A0000,  LENGTH = 128K */
/*  VEDRAM (rwx)      : ORIGIN = CACHEABLE_RAM_BASE + 0x000A0000,  LENGTH = 128K */
/*  DDR (rwx)         : ORIGIN = 0x80000000, LENGTH = 1024M */

  /* Gathered SRAMs */
/*  SRAM  (rwx)       : ORIGIN = ORIGIN(SRAM1),   LENGTH = LENGTH(SRAM1)   + LENGTH(SRAM2)  */

  /* Application memory areas */
    SYSRAM_APP (rwx)  : ORIGIN = ORIGIN(SYSRAM) + SYSRAM_RESERVED_SIZE,     LENGTH = LENGTH(SYSRAM) - SYSRAM_RESERVED_SIZE
/*  SYSRAM_APP0 (rwx) : ORIGIN = ORIGIN(SYSRAM) + SYSRAM_RESERVED_SIZE,     LENGTH = LENGTH(SYSRAM) / 2 */
/*  SYSRAM_APP1 (rwx) : ORIGIN = ORIGIN(SYSRAM_APP0) + LENGTH(SYSRAM_APP0), LENGTH = LENGTH(SYSRAM) - LENGTH(SYSRAM_APP0) - SYSRAM_RESERVED_SIZE */
/*  SRAM_APP (rwx)    : ORIGIN = ORIGIN(SRAM),                              LENGTH = LENGTH(SRAM) - IPC_SHM_SIZE */
/*  RETRAM_APP (rwx)  : ORIGIN = ORIGIN(RETRAM),                            LENGTH = LENGTH(RETRAM) - NSC_SIZE  */
}

MEMORY
{
  /* A35 application memory mapping */
  m_text_data (rwx) : ORIGIN = ORIGIN(SYSRAM_APP), LENGTH = LENGTH(SYSRAM_APP)

  /* Example of data buffer for A35 application in MCU SRAM1 */
  m_sram1_buffer (rw) : ORIGIN = ORIGIN(SRAM1), LENGTH = LENGTH(SRAM1)
}
REGION_ALIAS("TEXT_DATA", m_text_data);
REGION_ALIAS("UNINIT_DATA_BUFFER", m_sram1_buffer);
__UNINIT_DATA_BUFFER_START__ = ORIGIN(UNINIT_DATA_BUFFER);


/* Entry Point */
ENTRY(Reset_Handler)

_Min_Heap_Size = 0x200;     /* required amount of heap  */
_Min_Stack_Size = 0x400;    /* required amount of stack */

__MEM_START__ = ORIGIN(TEXT_DATA);
__MEM_SIZE__  = LENGTH(TEXT_DATA);

__FIQ_STACK_SIZE = 0x400;
__IRQ_STACK_SIZE = 0x400;
__ABT_STACK_SIZE = 0x400;
__SVC_STACK_SIZE = 0x400;
__UND_STACK_SIZE = 0x400;

/* put the stacks at the end of the memory */
FIQ_STACK = __MEM_START__ + __MEM_SIZE__;
IRQ_STACK = FIQ_STACK - __FIQ_STACK_SIZE;
ABT_STACK = IRQ_STACK - __IRQ_STACK_SIZE;
SVC_STACK = ABT_STACK - __ABT_STACK_SIZE;
UND_STACK = SVC_STACK - __SVC_STACK_SIZE;
SYS_STACK = UND_STACK - __UND_STACK_SIZE;

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

ENTRY(Reset_Handler)

SECTIONS
{
    . = __MEM_START__;
    .RESET . : {
        __TEXT_START__ = .;
        * (RESET)
        *(.text*)

        /* .init is used by libc_nano */
        KEEP (*(.init))
        KEEP (*(.fini))

        __TEXT_END_UNALIGNED__ = .;

        /*
         * Memory page(s) mapped to this section will be marked as
         * read-only, executable.  No non-executable data from the next section must
         * creep in.  Ensure the rest of the current memory page is unused.
         */
        __TEXT_END__ = .;

        . = NEXT(4096);

        __RO_START__ = .;
        *(.rodata*)

        __RO_END_UNALIGNED__ = .;
        /*
         * Memory page(s) mapped to this section will be marked as
         * read-only, non-executable.  No RW data from the next section must
         * creep in.  Ensure the rest of the current memory page is unused.
         */
        . = NEXT(4096);
        __RO_END__ = .;
    } > TEXT_DATA

    .ARM.extab   : {
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } > TEXT_DATA

    .ARM : {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
        . = ALIGN(4);
    } > TEXT_DATA

    /* .init_array is used by libc_nano */
    .preinit_array     :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } > TEXT_DATA

    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } > TEXT_DATA

    .fini_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } > TEXT_DATA

    .data . : {
        RW_DATA = .;
        *(.data*)
        __DATA_END__ = .;
    } > TEXT_DATA

    /*
     * The .bss section gets initialised to 0 at runtime.
     * Its base address must be 16-byte aligned.
     */
    .bss : ALIGN(32) {
        ZI_DATA = .;
        *(SORT_BY_ALIGNMENT(.bss*))
        *(COMMON)
        . = ALIGN(32);
        __BSS_END__ = .;
    } > TEXT_DATA

    __BSS_SIZE__ = SIZEOF(.bss);

    /* User_heap_stack section, used to check that there is enough RAM left */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >TEXT_DATA

    /* Data buffer for A35 application to collect uninitialized variables     */
    /* defined with "__attribute__ ((section ("uninit_data_buffer")))" pragma */
    /* WARNINGS ! Constant or initialized variables located out of SYSRAM     */
    /*            memory bank cannot be part of any flashable application.    */
    /*            Flashable application can use data out of SYSRAM memory,    */
    /*            only if corresponding memory bank is clocked and protected  */
    /*            according to A35 security configuration before.             */
    /*            If latter memory is defined as cacheable, check/action shall*/
    /*            be done to avoid "speculative accesses" [TO BE CONFIRMED]   */            
    SRAM1_BUFFER_FOR_A35 __UNINIT_DATA_BUFFER_START__ : {
        KEEP(*(uninit_data_buffer))
    } >UNINIT_DATA_BUFFER

    /* Remove information from the compiler libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}
