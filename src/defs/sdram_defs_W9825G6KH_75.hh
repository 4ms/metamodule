#pragma once
#include "sdram_config_struct.hh"

const SDRAMTimingConfig SDRAM_timing_W9825G6KH_75 = {
	.tRC_ns = 65,
	.tRP_ns = 21,
	.tMRD_ns = 2,
	.tXSR_ns = 75,
	.tRAS_ns = 45,
	.tWR_ns = 2,
	.tRCD_ns = 20,

	.max_freq_MHz = 133,
	.CAS_latency = 3,
	.refresh_ms = 64,
	.read_burst_enabled = true,
	.read_pipe_delay = 2,
};

const SDRAMArchConfig SDRAM_arch_W9825G6KH_75 = {
	.num_internal_banks = 4,
	.bus_width_bits = 16,
	.column_bits = 12,
	.row_bits = 9,
	.num_rows = 8192,
};
