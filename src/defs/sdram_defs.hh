#pragma once
#include "sdram_config_struct.hh"

const SDRAMTimingConfig SDRAMTiming_AS4C16M16SA_7CN = {
	.tRC_ns = 63,
	.tRP_ns = 21,
	.tMRD_ns = 14,
	.tXSR_ns = 65,
	.tRAS_ns = 42,
	.tWR_ns = 14,
	.tRCD_ns = 21,
	.max_freq_MHz = 143,
	.CAS_latency = 3,
};

const SDRAMTimingConfig SDRAMTiming_W9825G6KH_75 = {
	.tRC_ns = 65,
	.tRP_ns = 21,
	.tMRD_ns = 2,
	.tXSR_ns = 75,
	.tRAS_ns = 45,
	.tWR_ns = 2,
	.tRCD_ns = 20,
	.max_freq_MHz = 133,
	.CAS_latency = 3,
};
