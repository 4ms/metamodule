#pragma once
#include "drivers/ipcc.hh"
#include "drivers/rcc.hh"
#include <cstdint>
#include <optional>

#include "debug.hh"
#include "printf.h"

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

	// InterCoreCommMessage() = default;
	// InterCoreCommMessage(const InterCoreCommMessage &other) = default;
	// InterCoreCommMessage(InterCoreCommMessage &&other) = default;
	// InterCoreCommMessage &operator=(const InterCoreCommMessage &other) = default;
	// InterCoreCommMessage &operator=(InterCoreCommMessage &other) = default;

	// InterCoreCommMessage(const volatile InterCoreCommMessage &other)
	// 	: message_type(other.message_type)
	// 	, bytes_read{other.bytes_read}
	// 	, patch_id{other.patch_id} {
	// }
};

enum class ICCCoreType { Initiator = 1, Responder = 2 };

template<ICCCoreType Core>
class InterCoreComm {
	static constexpr uint32_t Chan = 1;
	using IPCCHalfDuplex = typename mdrivlib::IPCC_<(uint32_t)Core>::template HalfDuplexMode<Chan>;

	//This can change by another core, so it's volatile
	//Access is protected via IPCC hardware Flag, so it does not need to be atomic
	volatile InterCoreCommMessage &shared_message_;

	bool was_my_turn = false;

public:
	InterCoreComm(volatile InterCoreCommMessage &shared_message)
		: shared_message_{shared_message} {
		mdrivlib::RCC_Enable::IPCC_::set();
	}

	[[nodiscard]] bool send_message(const InterCoreCommMessage &msg) {
		if constexpr (Core == ICCCoreType::Initiator)
			Debug::Pin0::high();
		else
			Debug::Pin2::high();

		if (!IPCCHalfDuplex::is_my_turn()) {
			printf_("%d: send aborted: not my turn\n", Core);
			return false;
		}

		shared_message_.message_type = msg.message_type;
		shared_message_.bytes_read = msg.bytes_read;
		shared_message_.patch_id = msg.patch_id;
		was_my_turn = false;

		__DMB();
		printf_("[%d] %d: sending %d\n", HAL_GetTick(), Core, msg.message_type);
		IPCCHalfDuplex::notify_other();

		if constexpr (Core == ICCCoreType::Initiator)
			Debug::Pin0::low();
		else
			Debug::Pin2::low();
		return true;
	}

	[[nodiscard]] InterCoreCommMessage get_new_message() {
		// Process messages once
		auto is_my_turn = IPCCHalfDuplex::is_my_turn();

		InterCoreCommMessage msg{.message_type = InterCoreCommMessage::None};

		if (is_my_turn && !was_my_turn) {
			if constexpr (Core == ICCCoreType::Initiator)
				Debug::Pin1::high();
			else
				Debug::Pin3::high();

			//TODO: volatile copy constructor
			// msg = shared_message_;
			msg = {shared_message_.message_type, shared_message_.bytes_read, shared_message_.patch_id};

			printf_("[%d] %d: got msg %d\n", HAL_GetTick(), Core, msg.message_type);
			shared_message_.message_type = InterCoreCommMessage::None;

			if constexpr (Core == ICCCoreType::Initiator)
				Debug::Pin1::low();
			else
				Debug::Pin3::low();
		} else if (!is_my_turn) {
			printf_("%d: get_new_message: not my turn\n", Core);
		} else if (was_my_turn) {
			// printf_("%d: get_new_message: already got message\n", Core);
		}
		was_my_turn = is_my_turn;

		return msg;
	}
};

} // namespace MetaModule
