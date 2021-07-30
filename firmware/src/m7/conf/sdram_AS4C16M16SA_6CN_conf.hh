#pragma once
#include "drivers/sdram_config_struct.hh"

constexpr mdrivlib::SDRAMTimingConfig SDRAM_timing_AS4C16M16SA_6CN = {
	.tRC_ns = 60,
	.tRP_ns = 18,
	.tMRD_ns = 12,
	.tXSR_ns = 62,
	.tRAS_ns = 42,
	.tWR_ns = 12,
	.tRCD_ns = 18,

	.max_freq_MHz = 166,
	.CAS_latency = 3,
	.refresh_ms = 64,
	.read_burst_enabled = false,
	.read_pipe_delay = 2,
};

constexpr mdrivlib::SDRAMArchConfig SDRAM_arch_AS4C16M16SA_6CN = {
	.num_internal_banks = 4,
	.bus_width_bits = 16,
	.column_bits = 9,
	.row_bits = 13,
	.num_rows = 8192,
};
