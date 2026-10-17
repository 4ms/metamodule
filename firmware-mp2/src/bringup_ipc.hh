#pragma once
#include <cstdint>

// Bring-up test of the A35 <-> M33 path that core_intercom uses:
// mdrivlib::InterCoreComm over IPCC1, with the message in shared memory.
// The A35 (Initiator) sends a sequence number; the M33 (Responder) replies with seq * 2.

namespace MetaModule::BringupIPC
{

struct Message {
	uint32_t seq; // 0 = no message
	uint32_t value;
};

// The top 4kB of SRAM2. The A35 maps SRAM2 non-cacheable (system/mmu_ca35.cc); the M33 has no
// cache enabled. (Must not overlap the M33 image when that runs from SRAM2.)
constexpr uintptr_t SharedAddr = 0x0E07F000;
static_assert(M33_LOAD_ADDR + M33_REGION_SIZE <= SharedAddr || M33_LOAD_ADDR >= 0x0E080000,
			  "Shared memory overlaps the M33 region");

inline Message &shared_message() {
	return *reinterpret_cast<Message *>(SharedAddr);
}

constexpr uint32_t Channel = 1;

} // namespace MetaModule::BringupIPC
