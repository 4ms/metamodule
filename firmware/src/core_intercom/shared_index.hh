#pragma once
#include "core_intercom/intercore_types.hh"
#include <cstdint>

// Objects shared between the A35 and the M33.
//
// The A35 creates them in .sharedmem (DDR, non-cacheable on both cores) and publishes pointers
// to them in SharedIndex, at the start of the shared region, before starting the M33. This is
// MP2's version of MP1's SharedMemoryS::ptrs, which holds raw pointers and so can't cross a
// 64-bit/32-bit core boundary. Each core can fill in its own SharedMemoryS::ptrs from this.

namespace MetaModule
{

struct IntercoreStorageMessage;

// Crosses the core boundary: no raw pointers (8 bytes on the A35, 4 on the M33).
// Both cores see shared DDR at the same addresses, so InterCoreSharedRegion::base stays 0.
struct SharedIndex {
	static constexpr uint32_t ValidMagic = 0x5EA4ED01;
	uint32_t magic; // set by the A35 once the pointers below are valid

	InterCorePtr32<IntercoreStorageMessage> storage_message; // FileStorageProxy (A35) <-> PatchStorage (M33)
};
static_assert(sizeof(SharedIndex) == 8);

// At the start of the shared region (SHAREDMEM_ADDR), where both cores see it.
// Deliberately not a defined object: InterCorePtr32 has a default member initializer, so
// a defined object would get a static constructor on *each* core, and the M33's would wipe
// the pointers the A35 published. The A35 sets every field explicitly before starting the M33.
inline SharedIndex &shared_index() {
	return *reinterpret_cast<SharedIndex *>(SHAREDMEM_ADDR);
}

} // namespace MetaModule
