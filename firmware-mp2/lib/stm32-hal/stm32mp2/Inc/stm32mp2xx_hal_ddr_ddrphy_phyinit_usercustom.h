/*
 * Copyright (C) 2021-2023, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DDRPHY_PHYINIT_USERCUSTOM_H
#define DDRPHY_PHYINIT_USERCUSTOM_H

#include <stdbool.h>
#include <stdint.h>

#include "stm32mp2xx_hal.h"
#include "stm32mp2xx_hal_ddr_ddrphy_phyinit_struct.h"

#ifndef __AARCH64__
extern uint32_t FW_DDR_START;
#endif /* __AARCH64__ */

/*
 * -------------------------------------------------------------
 * Defines for Firmware Images
 * - point to IMEM/DMEM incv files,
 * - indicate IMEM/DMEM size (bytes)
 * -------------------------------------------------------------
 *
 * FW_FILES_LOC set the location of training firmware uncompressed path.
 *   PhyInit will use this path to load the imem and dmem incv files of the
 *   firmware image.
 *
 * IMEM_INCV_FILENAME firmware instruction memory (imem) filename for 1D training
 *
 * DMEM_INCV_FILENAME firmware data memory (dmem) filename for 1D training.
 *
 * IMEM_SIZE max size of instruction memory.
 *
 * DMEM_SIZE max size of data memory.
 *
 * DMEM_ST_ADDR start of DMEM address in memory.
 */
#ifndef FW_FILES_LOC
#define FW_FILES_LOC "./fw"
#endif /* FW_FILES_LOC */

#if STM32MP_DDR3_TYPE
#define IMEM_INCV_FILENAME	FW_FILES_LOC "/ddr3/ddr3_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME	FW_FILES_LOC "/ddr3/ddr3_pmu_train_dmem.incv"
#elif STM32MP_DDR4_TYPE
#define IMEM_INCV_FILENAME	FW_FILES_LOC "/ddr4/ddr4_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME	FW_FILES_LOC "/ddr4/ddr4_pmu_train_dmem.incv"
#elif STM32MP_LPDDR4_TYPE
#define IMEM_INCV_FILENAME	FW_FILES_LOC "/lpddr4/lpddr4_pmu_train_imem.incv"
#define DMEM_INCV_FILENAME	FW_FILES_LOC "/lpddr4/lpddr4_pmu_train_dmem.incv"
#endif /* STM32MP_LPDDR4_TYPE */

#if STM32MP_DDR3_TYPE
#define IMEM_SIZE			0x4c28
#define DMEM_SIZE			0x6c8
#elif STM32MP_DDR4_TYPE
#define IMEM_SIZE			0x6d24
#define DMEM_SIZE			0x6cc
#elif STM32MP_LPDDR4_TYPE
#define IMEM_SIZE			0x7e50
#define DMEM_SIZE			0x67c
#endif
#define IMEM_ST_ADDR			0x50000
#define DMEM_ST_ADDR			0x54000
#define DMEM_BIN_OFFSET			0x200

#ifndef __AARCH64__
#define STM32MP_DDR_FW_BASE		((unsigned long)(&FW_DDR_START))
#endif /* __AARCH64__ */
#define STM32MP_DDR_FW_DMEM_OFFSET	0x400
#define STM32MP_DDR_FW_IMEM_OFFSET	0x800

/*
 * -------------------------------------------------------------
 * Defines for SR Firmware Images
 * - point to IMEM incv files,
 * - indicate IMEM size (bytes)
 * -------------------------------------------------------------
 *
 * SR_FW_FILES_LOC location of optional retention save restore firmware image.
 *
 * SR_IMEM_SIZE max IMEM size of retention save/restore firmware.
 *
 * SR_IMEM_INCV_FILENAME file name of retention save/restore IMEM image.
 */
#ifndef SR_FW_FILES_LOC
#define SR_FW_FILES_LOC		FW_FILES_LOC "/save_restore"
#endif /* SR_FW_FILES_LOC */

#define SR_IMEM_SIZE		16384
#define SR_IMEM_INCV_FILENAME	SR_FW_FILES_LOC "/ddrphy_io_retention_save_restore_imem.incv"

/* Message Block Structure Definitions */
#if STM32MP_DDR3_TYPE
#include "stm32mp2xx_hal_ddr_mnpmusrammsgblock_ddr3.h"
#elif STM32MP_DDR4_TYPE
#include "stm32mp2xx_hal_ddr_mnpmusrammsgblock_ddr4.h"
#elif STM32MP_LPDDR4_TYPE
#include "stm32mp2xx_hal_ddr_mnpmusrammsgblock_lpddr4.h"
#endif /* STM32MP_LPDDR4_TYPE */

/*
 * ------------------
 * Type definitions
 * ------------------
 */

/* A structure used to SRAM memory address space. */
enum return_offset_lastaddr {
	RETURN_OFFSET,
	RETURN_LASTADDR
};

/* A structure to store the sequence function runtime input variables. */
struct runtime_config {
	bool	skip_train;	/* skip_train input parameter */
	bool	reten;		/*
				 * Retention Enable input parameter, instructs phyinit to issue
				 * register reads during initialization to retention registers.
				 */
};

/* Enumeration of instructions for PhyInit Register Interface */
enum reginstr {
	STARTTRACK,	/* Start register tracking */
	STOPTRACK,	/* Stop register tracking */
	SAVEREGS,	/* Save(read) tracked register values */
	RESTOREREGS,	/* Restore (write) saved register values */
	DUMPREGS,	/* Write register address,value pairs to file */
	IMPORTREGS	/* Import register address,value pairs to file */
} ;

/* Data structure to store register address, value pairs */
struct reg_addr_val {
	uint32_t	address;	/* Register address */
	uint16_t	value;		/* Register value */
};

/* TargetCSR Target CSR for the impedance value for ddrphy_phyinit_mapdrvstren() */
enum drvtype {
	DRVSTRENFSDQP,
	DRVSTRENFSDQN,
	ODTSTRENP,
	ODTSTRENN,
	ADRVSTRENP,
	ADRVSTRENN
};

/*
 * -------------------------------
 * Global variables - defined in ddrphy_phyinit_globals.c
 * -------------------------------
 */

extern int ardptrinitval[NB_PS];

static inline void mmio_write_16(uintptr_t addr, uint16_t value)
{
  uint32_t data;

  data = READ_REG(*(volatile uint32_t*)addr);
  data &= 0xFFFF0000;
  data |= (value & 0xFFFF);
  WRITE_REG(*(volatile uint32_t*)addr, data);
}

static inline uint16_t mmio_read_16(uintptr_t addr)
{
  return (uint16_t)READ_REG(*(volatile uint32_t*)addr);
}

static inline void mmio_write_32(uintptr_t addr, uint32_t value)
{
  WRITE_REG(*(volatile uint32_t*)addr, value);
}

#define VERBOSE(...)
#define ERROR(...)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*
 * -------------------------------------------------------------
 * Fixed Function prototypes
 * -------------------------------------------------------------
 */
int ddrphy_phyinit_sequence(bool skip_training, bool reten);
int ddrphy_phyinit_restore_sequence(void);
int ddrphy_phyinit_c_initphyconfig(void);
void ddrphy_phyinit_d_loadimem(void);
void ddrphy_phyinit_progcsrskiptrain(bool skip_training);
int ddrphy_phyinit_f_loaddmem(int pstate);
int ddrphy_phyinit_g_execfw(void);
void ddrphy_phyinit_h_readmsgblock(void);
void ddrphy_phyinit_i_loadpieimage(bool skip_training);
void ddrphy_phyinit_loadpieprodcode(void);
int ddrphy_phyinit_mapdrvstren(int drvstren_ohm, enum drvtype targetcsr);
void ddrphy_phyinit_storemsgblk(void *msgblkptr, int sizeofmsgblk, int mem[]);
int ddrphy_phyinit_calcmb(void);
int ddrphy_phyinit_storeincvfile(char *incv_file_name, int mem[],
				 enum return_offset_lastaddr return_type);
void ddrphy_phyinit_writeoutmem(uint32_t *mem, int mem_offset, int mem_size);
void ddrphy_phyinit_writeoutmsgblk(uint16_t *mem, int mem_offset, int mem_size);
int ddrphy_phyinit_isdbytedisabled(int dbytenumber);
int ddrphy_phyinit_setretreglistbase(unsigned long base);
int ddrphy_phyinit_trackreg(uint32_t adr);
int ddrphy_phyinit_reginterface(enum reginstr myreginstr, uint32_t adr, uint16_t dat);

extern void ddrphy_phyinit_usercustom_a_bringuppower(void);
extern void ddrphy_phyinit_usercustom_b_startclockresetphy(void);
extern void ddrphy_phyinit_usercustom_custompretrain(void);
extern void ddrphy_phyinit_usercustom_customposttrain(void);
extern int ddrphy_phyinit_usercustom_e_setdficlk(int dfi_frequency);
extern int ddrphy_phyinit_usercustom_g_waitfwdone(void);
extern void ddrphy_phyinit_usercustom_h_readmsgblock(void);
extern void ddrphy_phyinit_usercustom_j_entermissionmode(void);
extern int ddrphy_phyinit_usercustom_saveretregs(void);

#include "stm32mp2xx_hal_ddr_ddrphy_csr_all_cdefines.h"

#endif /* DDRPHY_PHYINIT_USERCUSTOM_H */
