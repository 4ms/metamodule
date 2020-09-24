#pragma once
#include <cstdint>

struct SDRAMTimingConfig {
	uint8_t tRC_ns;	 // Row Cycle time (same bank)
	uint8_t tRP_ns;	 // Precharge to refresh/row activate
	uint8_t tMRD_ns; // Mode register set cycle time? == LoadToActiveDelay
	uint8_t tXSR_ns; // Exit Self Refresh time
	uint8_t tRAS_ns; // Row activate to precharge time == Self-refresh?
	uint8_t tWR_ns;	 // Write Recovery time
	uint8_t tRCD_ns; // RAS to CAS delay (same bank)

	uint8_t max_freq_MHz;
	uint8_t CAS_latency;
};
