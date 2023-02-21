#pragma once
#include "drivers/ipcc.hh"
#include <cstdint>
#include <optional>

namespace MetaModule
{

struct InterCoreCommMessage {
	enum MessageType : uint32_t {
		None,

		RequestRefreshPatchList,
		PatchListChanged,
		PatchListUnchanged,

		RequestPatchData,
		PatchDataLoadFail,
		PatchDataLoaded,

		NumRequests,
	};
	MessageType message_type;
	uint32_t bytes_read;
	uint32_t patch_id;
};

enum class ICCNum { Core1, Core2 };

template<ICCNum core>
class InterCoreComm {
	bool got_message_ = false;
	InterCoreCommMessage &shared_message_;
	InterCoreCommMessage last_message_;

public:
	InterCoreComm(InterCoreCommMessage &shared_message)
		: shared_message_{shared_message} {
		//A7 set up ISR for TXFree
		//M4 set up ISR for RXOccupied
		auto recv_req = [this] {
			//Double-check CHnF is set/clear
			got_message_ = true;
			last_message_ = shared_message_;
		};
	}

	[[nodiscard]] bool send_message(const InterCoreCommMessage &msg) {
		// Different checks for each core:
		// check CHnF flag is TXclear/RXset, return false if not
		// TXset/RXclear CHnF bit with CHnS
		// if...
		// return false;
		// else {
		shared_message_ = msg; //copy
		return true;
	}

	[[nodiscard]] InterCoreCommMessage get_new_message() {
		//scoped disable IRQ
		if (!got_message_) {
			last_message_.message_type = InterCoreCommMessage::None;
		}
		got_message_ = false;
		return last_message_;
	}
};

} // namespace MetaModule
