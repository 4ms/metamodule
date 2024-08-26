#pragma once
#include "printf.h"
#include <cstdint>

enum g_Errors {
	READ_BUFF1_OVERRUN = (1 << 0),
	READ_BUFF2_OVERRUN = (1 << 1),
	READ_BUFF1_UNDERRUN = (1 << 2),
	READ_BUFF2_UNDERRUN = (1 << 3),

	DMA_OVR_ERROR = (1 << 4),
	sFLASH_BAD_ID = (1 << 5),
	WRITE_BUFF_OVERRUN = (1 << 6),
	OUT_OF_MEM = (1 << 7),

	SDCARD_CANT_MOUNT = (1 << 8),
	READ_MEM_ERROR = (1 << 9),
	WRITE_SDCARD_ERROR = (1 << 10),
	WRITE_BUFF_UNDERRUN = (1 << 11),

	FILE_OPEN_FAIL = (1 << 12),
	FILE_READ_FAIL_1 = (1 << 13),
	FILE_READ_FAIL_2 = (1 << 14),
	FILE_WAVEFORMATERR = (1 << 15),

	FILE_UNEXPECTEDEOF = (1 << 16),
	FILE_SEEK_FAIL = (1 << 17),
	READ_BUFF_OVERRUN_RESAMPLE = (1 << 18),
	FILE_CANNOT_CREATE_CLTBL = (1 << 19),

	CANNOT_OPEN_ROOT_DIR = (1 << 20),
	FILE_REC_OPEN_FAIL = (1 << 21),
	FILE_WRITE_FAIL = (1 << 22),
	FILE_UNEXPECTEDEOF_WRITE = (1 << 23),

	CANNOT_WRITE_INDEX = (1 << 24),
	LSEEK_FPTR_MISMATCH = (1 << 25),
	HEADER_READ_FAIL = (1 << 26),
	MATH_ERROR = (1 << 27),
};

static inline void check_errors(uint32_t err) {
	if (err)
		printf_("Error: %x\n", err);
}
