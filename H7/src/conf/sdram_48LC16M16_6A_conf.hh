#pragma once
#include "drivers/sdram_config_struct.hh"

const SDRAMTimingConfig SDRAM_timing_48LC16M16_6A = {
	.tRC_ns = 60,
	.tRP_ns = 18,
	.tMRD_ns = 14,
	.tXSR_ns = 65,
	.tRAS_ns = 42, //
	.tWR_ns = 14,
	.tRCD_ns = 18,

	.max_freq_MHz = 143,
	.CAS_latency = 3,
	.refresh_ms = 64,
	.read_burst_enabled = true,
	.read_pipe_delay = 2,
};

const SDRAMArchConfig SDRAM_arch_48LC16M16_6A = {
	.num_internal_banks = 4,
	.bus_width_bits = 16,
	.column_bits = 8,
	.row_bits = 12,
	.num_rows = 8192,
};

