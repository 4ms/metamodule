#pragma once
#include <cstdint>
// #include "drivers/ipcc.hh"
#include "shared_memory.hh"

namespace MetaModule
{

struct InterCoreCommParams {
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
	Message message;
	uint32_t bytes_read;
	uint32_t patch_id;
};

enum class ICCNum { Core1, Core2 };

template<ICCNum core>
class InterCoreComm {
	bool got_message_ = false;

public:
	InterCoreComm() {
		//A7 set up ISR for TXFree
		//M4 set up ISR for RXOccupied
		auto recv_req = [this] {
			got_message_ = true;
			;
		};
	}

	[[nodiscard]] bool send_message(InterCoreCommParams msg) {
		// Different checks for each core:
		// TODO: check CHnF flag is TXclear/RXset, return false if not
		// TODO: TXset/RXclear CHnF bit with CHnS
		// if...
		// return false;
		// else
		return true;
	}

	[[nodiscard]] bool got_message() {
		if (got_message_) {
			got_message_ = false;
			return true;
		}
		return false;
	}
};

} // namespace MetaModule
