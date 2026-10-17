#pragma once
#include "core_intercom/intercore_types.hh"
#include <cstdint>

// Bring-up test of the A35 <-> M33 path that core_intercom uses:
// mdrivlib::InterCoreComm over IPCC1, with the message in shared memory.
// The A35 (Initiator) sends a sequence number; the M33 (Responder) replies with seq * 2.
//
// The message lives in .sharedmem (DDR, non-cacheable on both cores), and the M33 finds it
// through SharedIndex at the start of the shared region (like MP1's SharedMemoryS::ptrs).

namespace MetaModule::BringupIPC
{

struct Message {
	uint32_t seq; // 0 = no message
	uint32_t value;
};

// Crosses the core boundary: no raw pointers (8 bytes on the A35, 4 on the M33).
// Both cores see shared DDR at the same addresses, so InterCoreSharedRegion::base stays 0.
struct SharedIndex {
	static constexpr uint32_t ValidMagic = 0x5EA4ED00;
	uint32_t magic;					 // set by the A35 once the pointers below are valid
	InterCorePtr32<Message> message; // in .sharedmem
};
static_assert(sizeof(Message) == 8);
static_assert(sizeof(SharedIndex) == 8);

// At the start of the shared region (SHAREDMEM_ADDR), where both cores see it.
// Deliberately not a defined object: InterCorePtr32 has a default member initializer, so
// a defined object would get a static constructor on *each* core, and the M33's would wipe
// the pointers the A35 published. The A35 sets every field explicitly before starting the M33.
inline SharedIndex &shared_index() {
	return *reinterpret_cast<SharedIndex *>(SHAREDMEM_ADDR);
}

constexpr uint32_t Channel = 1;

} // namespace MetaModule::BringupIPC
