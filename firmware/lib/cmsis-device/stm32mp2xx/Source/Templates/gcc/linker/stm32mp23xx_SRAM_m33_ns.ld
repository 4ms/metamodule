/*
******************************************************************************
**
**  File        : stm32mp23xx_SRAM_m33_ns.ld
**
**  Abstract    : Linker script for STM32MP2 series
**                For M33 Core
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
*****************************************************************************
** @attention
**
** <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
** All rights reserved.</center></h2>
**
** This software component is licensed by ST under BSD 3-Clause license,
** the License; You may not use this file except in compliance with the
** License. You may obtain a copy of the License at:
**                       opensource.org/licenses/BSD-3-Clause
**
*****************************************************************************
*/

/******************/
/* Memory mapping */
/******************/
/*** Memory regions
  Bootrom mem located at begining of SYSRAM
    Data area used by Bootrom
    9 KBytes
  Image Header located  in SYSRAM after Bootrom mem
    Code header used for loading from flash
    512 Bytes
  EL3 Switcher (A35 64 bits) located  in SYSRAM between Image Header and Application A35 32 bits
    A35 Aarch64 EL3 code
      which switches A35 from Aarch64 EL3 to Aarch32 EL1
    14.5 KBytes
    Actually bundled with image header and application in Flash Image
  IPC Shared mem
    Buffer used for communication between A35 (Linux) and M33 (Copro) processors
    32 KBytes located at end of SRAM
*/

/* SYSRAM
   Size 256K
   Non Secure boot alias 0x0A000000
   Secure boot alias     0x0E000000
   Non Secure alias      0x20000000
   Secure alias          0x30000000
  -----------------------------------------------------
  | AREA           | Start Offs | End Offs   | Size   |
  |----------------|------------|------------|--------|
  | Bootrom mem    | 0x00000000 | 0x000023FF |     9K |
  | Image Header   | 0x00002400 | 0x000025FF |    512 |
  | EL3 Switcher   | 0x00002600 | 0x00005FFF |  14.5K |
  | App code/data  | 0x00006000 | 0x0003FFFF |   232K |
  -----------------------------------------------------
*/

/* SRAM
   Size 128K + 128K
   Non Secure boot alias 0x0A040000
   Secure boot alias     0x0E040000
   Non Secure alias      0x20040000
   Secure alias          0x30040000
  -----------------------------------------------------
  | AREA           | Start Offs | End Offs   | Size   |
  |----------------|------------|------------|--------|
  | App code/data  | 0x00000000 | 0x00037FFF |   224K |
  | IPC Shared mem | 0x00038000 | 0x0003FFFF |    32K |
  -----------------------------------------------------
*/

/* RETRAM
   Size 128K
   Non Secure boot alias 0x0A080000
   Secure boot alias     0x0E080000
   Non Secure alias      0x20080000
   Secure alias          0x30080000
  -----------------------------------------------------
  | AREA           | Start Offs | End Offs   | Size   |
  |----------------|------------|------------|--------|
  | App code/data  | 0x00000000 | 0x0001DFFF |   120K |
  | NSC / veener   | 0x0001E000 | 0x0001FFFF |     8K |
  -----------------------------------------------------
*/

/* VEDRAM
   Size 128K
   Non Secure boot alias 0x0A0A0000
   Secure boot alias     0x0E0A0000
   Non Secure alias      0x200A0000
   Secure alias          0x300A0000
  -----------------------------------------------------
  | AREA           | Start Offs | End Offs   | Size   |
  |----------------|------------|------------|--------|
  | App code/data  | 0x00000000 | 0x0001FFFF |   128K |
  -----------------------------------------------------
*/

NS_BOOT_ALIAS_BASE = 0x0A000000;
S_BOOT_ALIAS_BASE  = 0x0E000000;
NS_ALIAS_BASE      = 0x20000000;
S_ALIAS_BASE       = 0x30000000;

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

/* Chose alias base here */
USED_ALIAS_BASE  = NS_BOOT_ALIAS_BASE;

MEMORY
{
  /* Global memory layout */
/*  SYSRAM (rwx)      : ORIGIN = USED_ALIAS_BASE + 0x00000000,  LENGTH = 256K */
    SRAM1 (rwx)       : ORIGIN = USED_ALIAS_BASE + 0x00040000,  LENGTH = 128K
    SRAM2 (rwx)       : ORIGIN = USED_ALIAS_BASE + 0x00060000,  LENGTH = 128K
/*  RETRAM (rwx)      : ORIGIN = USED_ALIAS_BASE + 0x00080000,  LENGTH = 128K  */
/*  VEDRAM (rwx)      : ORIGIN = USED_ALIAS_BASE + 0x000A0000,  LENGTH = 128K  */
/*  DDR (rwx)         : ORIGIN = 0x80000000,                    LENGTH = 1024M  */

  /* Gathered SRAMs */
    SRAM  (rwx)       : ORIGIN = ORIGIN(SRAM1),   LENGTH = LENGTH(SRAM1)   + LENGTH(SRAM2)
  /* Application memory areas */
/*  SYSRAM_APP (rwx)  : ORIGIN = ORIGIN(SYSRAM) + SYSRAM_RESERVED_SIZE, LENGTH = LENGTH(SYSRAM) - SYSRAM_RESERVED_SIZE */
  SRAM_APP (rwx)    : ORIGIN = ORIGIN(SRAM),                          LENGTH = LENGTH(SRAM) - IPC_SHM_SIZE
/*  RETRAM_APP (rwx)  : ORIGIN = ORIGIN(RETRAM),                        LENGTH = LENGTH(RETRAM) - NSC_SIZE  */
}

MEMORY
{
  /* M33 Secure application memory mapping */
  m_text (rx)       : ORIGIN = ORIGIN(SRAM_APP),                             LENGTH = 180K
  m_data (rwx)      : ORIGIN = ORIGIN(SRAM_APP) + LENGTH(m_text),            LENGTH = LENGTH(SRAM_APP) - LENGTH(m_text)
/*  m_text_nsc(rx)    : ORIGIN = ORIGIN(RETRAM_APP) + LENGTH(RETRAM) - NSC_SIZE, LENGTH = NSC_SIZE  */
  m_ipc_shm (rw)    : ORIGIN = ORIGIN(SRAM) + LENGTH(SRAM) - IPC_SHM_SIZE,     LENGTH = IPC_SHM_SIZE
}

REGION_ALIAS("TEXT", m_text);
REGION_ALIAS("DATA", m_data);

/* Symbols needed for OpenAMP to enable rpmsg */

__OPENAMP_region_start__  = ORIGIN(m_ipc_shm);
__OPENAMP_region_end__    = ORIGIN(m_ipc_shm)+LENGTH(m_ipc_shm);


/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

ENTRY(Reset_Handler)

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors))
    __Vectors_End = .;
    __Vectors_Size = __Vectors_End - __Vectors;
    __end__ = .;

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
  } > TEXT

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > TEXT

  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > TEXT
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
    __copy_table_end__ = .;
  } > TEXT
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
    __zero_table_end__ = .;
  } > TEXT
  */

  __etext = .;

  .data : AT (__etext)
  {
    __data_start__ = .;
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
  } > DATA

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > DATA

  .heap (COPY):
  {
    __HeapBase = .;
    __end__ = .;
    end = __end__;
    KEEP(*(.heap*))
    __HeapLimit = .;
  } > DATA

  /* .stack_dummy section doesn't contains any symbols. It is only
   * used for linker to calculate size of stack sections, and assign
   * values to stack symbols later */
  .stack_dummy (COPY):
  {
    KEEP(*(.stack*))
  } > DATA

  /* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(DATA) + LENGTH(DATA);
  __StackLimit = __StackTop - SIZEOF(.stack_dummy);
  PROVIDE(__stack = __StackTop);

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
  
  
}
