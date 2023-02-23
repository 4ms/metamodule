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

	// InterCoreCommMessage(InterCoreCommMessage &other) = default;

	// InterCoreCommMessage(volatile InterCoreCommMessage &other)
	// 	: message_type(other.message_type)
	// 	, bytes_read{other.bytes_read}
	// 	, patch_id{other.patch_id} {
	// }
};

enum class ICCCoreType { Initiator = 1, Responder = 2 };

template<ICCCoreType Core>
class InterCoreComm {
	using IPCCCore = mdrivlib::IPCC_<(uint32_t)Core>;
	static constexpr uint32_t Chan = 1;

	using IPCCHalfDuplex = typename IPCCCore::template HalfDuplexMode<Chan>;

	//This can change by another core, so it volatile
	//Access is protected via IPCC, so it does not need to be atomic
	volatile InterCoreCommMessage &shared_message_;

	//These change in an ISR on this core, so are volatile
	volatile bool got_message_ = false;
	volatile InterCoreCommMessage last_message_;

public:
	InterCoreComm(volatile InterCoreCommMessage &shared_message)
		: shared_message_{shared_message} {
		mdrivlib::RCC_Enable::IPCC_::set();
		uint32_t isr_pri = 2;
		uint32_t isr_subpri = 2;

		IPCCHalfDuplex::enable_chan_isr(isr_pri, isr_subpri, [this] {
			// Verify flag has not been changed by other core since ISR fired
			// irqmask = ~(currentInstance->MR) & IPCC_ALL_RX_BUF or TX_BUF;
			// irqmask = irqmask & otherInstance->SR;
			// for each bit set in irqmask:

			IPCCHalfDuplex::disable_chan_isr();

			if constexpr (Core == ICCCoreType::Initiator)
				Debug::Pin1::high();
			else
				Debug::Pin3::high();

			got_message_ = true;
			last_message_.message_type = shared_message_.message_type;
			last_message_.bytes_read = shared_message_.bytes_read;
			last_message_.patch_id = shared_message_.patch_id;
			if constexpr (Core == ICCCoreType::Initiator)
				Debug::Pin1::low();
			else
				Debug::Pin3::low();

			printf_("[%d] %d: GOT msg %d\n", HAL_GetTick(), Core, last_message_.message_type);
		});
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
		if (got_message_) {
			printf_("%d: send aborted: got_message\n", Core);
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
		IPCCHalfDuplex::enable_chan_isr();

		if constexpr (Core == ICCCoreType::Initiator)
			Debug::Pin0::low();
		else
			Debug::Pin2::low();
		return true;
	}

	// struct ScopedISRMask {
	// 	ScopedISRMask() {
	// 		IPCCHalfDuplex::disable_chan_isr();
	// 	}
	// 	~ScopedISRMask() {
	// 		IPCCHalfDuplex::enable_chan_isr();
	// 	}
	// };

	[[nodiscard]] InterCoreCommMessage get_new_message() {
		// ISR might be enabled at this point, if we sent a message and are waiting to hear back
		// But we just check true/false on got_message. If we read it as false and the ISR fires,
		// we'll take the false branch and then take the true branch next time (no harm done)
		if (!got_message_) {
			return {.message_type = InterCoreCommMessage::None};
		}
		// If we get to this point, then got_message_ == true, which can only be set
		// in the ISR, after the ISR is masked (disabled).
		// Therefore ISR must be masked and the ISR can't interrupt the following:

		printf_("[%d] %d: got msg %d\n", HAL_GetTick(), Core, last_message_.message_type);

		got_message_ = false;
		InterCoreCommMessage msg = {last_message_.message_type, last_message_.bytes_read, last_message_.patch_id};
		last_message_.message_type = InterCoreCommMessage::None;

		return msg;
	}
};

} // namespace MetaModule
