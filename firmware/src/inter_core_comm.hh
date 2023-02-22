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
				Debug::Pin2::high();

			got_message_ = true;
			last_message_.message_type = shared_message_.message_type;
			last_message_.bytes_read = shared_message_.bytes_read;
			last_message_.patch_id = shared_message_.patch_id;
			if constexpr (Core == ICCCoreType::Initiator)
				Debug::Pin1::low();
			else
				Debug::Pin2::low();
		});
	}

	[[nodiscard]] bool send_message(const InterCoreCommMessage &msg) {
		if (!IPCCHalfDuplex::is_my_turn()) {
			// printf_("%d: send: not my turn\n", Core);
			return false;
		}

		shared_message_.message_type = msg.message_type;
		shared_message_.bytes_read = msg.bytes_read;
		shared_message_.patch_id = msg.patch_id;

		__DMB();
		printf_("%d: sending %d\n", Core, msg.message_type);
		IPCCHalfDuplex::notify_other();
		return true;
	}

	[[nodiscard]] InterCoreCommMessage get_new_message() {
		//scoped disable IRQ
		if (!got_message_) {
			last_message_.message_type = InterCoreCommMessage::None;
		} else
			printf_("%d: got msg %d\n", Core, last_message_.message_type);
		got_message_ = false;
		return last_message_;
	}
};

} // namespace MetaModule
