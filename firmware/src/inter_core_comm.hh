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

	// Only the "Initiator" core can begin by sending a message
	bool already_got_message_ = Core == ICCCoreType::Initiator ? false : false;

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

		//Prevent sending while a message has been received in the ISR
		//but not yet processed in get_new_message(). Otherwise,
		//there's a chance the response will happen before we can
		//process the previous message, which will get clobbered by the new one
		if (already_got_message_) {
			printf_("%d: send aborted: already_got_message\n", Core);
			return false;
		}
		//Prevent sending while waiting for a response
		if (!IPCCHalfDuplex::is_my_turn()) {
			printf_("%d: send aborted: not my turn\n", Core);
			return false;
		}

		shared_message_.message_type = msg.message_type;
		shared_message_.bytes_read = msg.bytes_read;
		shared_message_.patch_id = msg.patch_id;

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
		if (already_got_message_) {
			printf_("%d: get_new_message: Already got a message, nothing new\n", Core);
			return {.message_type = InterCoreCommMessage::None};
		}

		// Only have access to shared_message_ when IPCC Flag says its our turn
		if (!IPCCHalfDuplex::is_my_turn()) {
			printf_("%d: get_new_message: not my turn\n", Core);
			return {.message_type = InterCoreCommMessage::None};
		}

		if constexpr (Core == ICCCoreType::Initiator)
			Debug::Pin1::high();
		else
			Debug::Pin3::high();

		already_got_message_ = true;

		//TODO: volatile copy constructor
		InterCoreCommMessage msg{shared_message_.message_type, shared_message_.bytes_read, shared_message_.patch_id};

		printf_("[%d] %d: got msg %d\n", HAL_GetTick(), Core, msg.message_type);
		shared_message_.message_type = InterCoreCommMessage::None;

		if constexpr (Core == ICCCoreType::Initiator)
			Debug::Pin1::low();
		else
			Debug::Pin3::low();

		return msg;
	}
};

} // namespace MetaModule
