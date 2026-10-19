// MetaModule MP2 ("pro") Cortex-M33 firmware -- bring-up.
//
// Loaded and started by the A35 (see core_a35/main.cc), which has already initialized the
// HSEM and IPCC1 peripherals. On MP1 the M4 runs patch storage, controls, USB, and MIDI;
// on MP2 the M33 takes that role.
//
// Bring-up tests:
// - SD card + FatFS (sd_test.cc): read speed, mount, list, write/verify; then report insert/remove
// - respond to the A35's InterCoreComm messages (bringup_ipc.hh), woken by the IPCC1
//   RX-occupied interrupt. The message is in shared memory, found through the shared index.

#include "bringup_ipc.hh"
#include "console.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/ipcc.hh"
#include "drivers/cache.hh"
#include "drivers/stm32xx.h"
#include "sd_test.hh"

using namespace MetaModule;

namespace
{
using IPC = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, BringupIPC::Message, BringupIPC::Channel>;
using IPCChan = mdrivlib::IPCC_<2>::HalfDuplexMode<BringupIPC::Channel>;

volatile bool request_pending = false;
} // namespace

int main() {
	// The MPU is already set up (system_init.cc): DCACHE caches the M33's own memory, not shared memory.
	// It speeds up code and data in DDR ~20-30x.
	bool dcache_ok = mdrivlib::SystemCache::enable_dcache();
	M33Console::log("M33: started. DCACHE ", dcache_ok ? "on" : "enable FAILED", "\n");

	sd_card_test();

	// The A35 publishes the shared objects before starting us
	if (BringupIPC::shared_index().magic != BringupIPC::SharedIndex::ValidMagic) {
		M33Console::Lock lock;
		M33Console::print("M33: shared memory index not valid! magic = ");
		M33Console::print_hex(BringupIPC::shared_index().magic);
		M33Console::print("\n");
		while (true)
			;
	}
	static IPC ipc{*BringupIPC::shared_index().message};

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

		sd_card_poll();

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
