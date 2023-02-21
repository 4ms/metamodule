#pragma once
#include <cstdint>
// #include "drivers/ipcc.hh"
#include "shared_memory.hh"

namespace MetaModule
{

enum class ICCNum { Core1, Core2 };

template<ICCNum core>
class InterCoreComm {
public:
	InterCoreComm() {
		//A7 set up ISR for TXFree
		//M4 set up ISR for RXOccupied
		//ctor parameter? if constexpr? do it in parent code?

		auto recv_req = [this] { read_message(); };
	}
	enum Message : uint32_t {
		None,
		RequestRefreshPatchList,
		PatchListChanged,
		PatchListUnchanged,

		RequestPatchData,
		PatchDataLoadFail,
		PatchDataLoaded,

		NumRequests,
	};

	[[nodiscard]] bool send_message(Message req) {
		// Different checks for each core:
		// TODO: check CHnF flag is TXclear/RXset, return false if not
		SharedMemory::write_value(static_cast<uint32_t>(req), SharedMemory::InterCoreCommReqLocation);
		// TODO: TXset/RXclear CHnF bit with CHnS
		return true;
	}

	Message get_last_message() {
		auto t = last_message_;
		last_message_ = None;
		return t;
	}

private:
	Message last_message_ = None;

	void read_message() {
		auto reqptr = SharedMemory::read_value(SharedMemory::InterCoreCommReqLocation);
		if (reqptr < NumRequests)
			last_message_ = static_cast<Message>(reqptr);
		else
			last_message_ = None;
	}
};

struct InterCoreCommParams {

	uint32_t bytes_read;
	uint32_t patch_id;
};

} // namespace MetaModule
