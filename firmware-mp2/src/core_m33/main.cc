// MetaModule MP2 ("pro") Cortex-M33 firmware -- bring-up.
//
// Loaded and started by the A35 (see core_a35/main.cc), which has already initialized the
// HSEM and IPCC1 peripherals. On MP1 the M4 runs patch storage, controls, USB, and MIDI;
// on MP2 the M33 takes that role.
//
// Bring-up test: respond to the A35's InterCoreComm messages (bringup_ipc.hh), woken by the
// IPCC1 RX-occupied interrupt.

#include "bringup_ipc.hh"
#include "console.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/ipcc.hh"
#include "drivers/stm32xx.h"

extern "C" uint32_t stgen_counter_freq();

using namespace MetaModule;

namespace
{
using IPC = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, BringupIPC::Message, BringupIPC::Channel>;
using IPCChan = mdrivlib::IPCC_<2>::HalfDuplexMode<BringupIPC::Channel>;

volatile bool request_pending = false;
} // namespace

int main() {
	{
		M33Console::Lock lock;
		M33Console::print("M33: started. STGEN counter freq: ");
		M33Console::print(stgen_counter_freq());
		M33Console::print(" Hz\n");
	}

	static IPC ipc{BringupIPC::shared_message()};

	// The A35's request holds the channel's RX-occupied flag high until we reply, so the ISR
	// masks the channel; the main loop unmasks it again after replying.
	IPCChan::enable_chan_isr(1, 0, [] {
		IPCChan::disable_chan_isr();
		request_pending = true;
	});

	uint32_t num_requests = 0;
	uint32_t last_print = HAL_GetTick();

	while (true) {
		if (request_pending) {
			request_pending = false;

			auto msg = ipc.get_new_message();
			if (msg.seq) {
				num_requests++;
				if (!ipc.send_message({.seq = msg.seq, .value = msg.seq * 2})) {
					M33Console::Lock lock;
					M33Console::print("M33: reply FAILED (not my turn)\n");
				}
			}
			IPCChan::enable_chan_isr();
		}

		auto now = HAL_GetTick();
		if (now - last_print >= 5000) {
			last_print = now;
			M33Console::Lock lock;
			M33Console::print("M33: uptime ");
			M33Console::print(now / 1000);
			M33Console::print(" s, answered ");
			M33Console::print(num_requests);
			M33Console::print(" requests\n");
		}
	}
}
