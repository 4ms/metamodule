#pragma once
#include "drivers/sdram_config_struct.hh"

constexpr mdrivlib::SDRAMTimingConfig SDRAM_timing_AS4C16M16SA_7CN = {
	.tRC_ns = 63,
	.tRP_ns = 21,
	.tMRD_ns = 14,
	.tXSR_ns = 65,
	.tRAS_ns = 42,
	.tWR_ns = 14,
	.tRCD_ns = 21,

	.max_freq_MHz = 143,
	.CAS_latency = 3,
	.refresh_ms = 64,
	.read_burst_enabled = true,
	.read_pipe_delay = 2,
};

constexpr mdrivlib::SDRAMArchConfig SDRAM_arch_AS4C16M16SA_7CN = {
	.num_internal_banks = 4,
	.bus_width_bits = 16,
	.column_bits = 8, // 9?
	.row_bits = 12,	  // 13?
	.num_rows = 8192,
};
