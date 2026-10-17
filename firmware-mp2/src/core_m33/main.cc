// MetaModule MP2 ("pro") Cortex-M33 firmware -- bring-up.
//
// Loaded and started by the A35 (see core_a35/main.cc), which has already initialized the
// HSEM and IPCC1 peripherals. On MP1 the M4 runs patch storage, controls, USB, and MIDI;
// on MP2 the M33 takes that role.
//
// Bring-up tests:
// - benchmark code and data access in DDR, without and with the DCACHE
// - respond to the A35's InterCoreComm messages (bringup_ipc.hh), woken by the IPCC1
//   RX-occupied interrupt. The message is in shared memory, found through the shared index.

#include "bringup_ipc.hh"
#include "console.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/ipcc.hh"
#include "drivers/cache.hh"
#include "drivers/stm32xx.h"
#include <array>

extern "C" uint32_t stgen_counter_freq();
extern "C" uint64_t stgen_read_counter();

using namespace MetaModule;

namespace
{
using IPC = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, BringupIPC::Message, BringupIPC::Channel>;
using IPCChan = mdrivlib::IPCC_<2>::HalfDuplexMode<BringupIPC::Channel>;

volatile bool request_pending = false;

// Benchmarks: code runs from DDR, and the data buffer is in .bss (also DDR)
std::array<uint32_t, 8192> bench_data; // 32kB

// Register-only loop: dominated by instruction fetch
__attribute__((noinline)) uint32_t bench_code(uint32_t iterations) {
	uint32_t acc = 1;
	for (uint32_t i = 0; i < iterations; i++) {
		acc = acc * 1664525u + 1013904223u;
		__asm volatile("" : "+r"(acc)); // keep the loop from being optimized away
	}
	return acc;
}

// Read-modify-write over a buffer: dominated by data accesses
__attribute__((noinline)) uint32_t bench_data_rw(uint32_t passes) {
	uint32_t acc = 0;
	for (uint32_t p = 0; p < passes; p++) {
		for (auto &d : bench_data) {
			acc = acc * 31 + d;
			d = acc;
		}
	}
	return acc;
}

void run_benchmarks(const char *label) {
	auto us = [](uint64_t ticks) { return uint32_t(ticks * 1'000'000 / stgen_counter_freq()); };

	auto t0 = stgen_read_counter();
	auto r1 = bench_code(1'000'000);
	auto t1 = stgen_read_counter();
	auto r2 = bench_data_rw(10);
	auto t2 = stgen_read_counter();

	M33Console::Lock lock;
	M33Console::print("M33 benchmark (");
	M33Console::print(label);
	M33Console::print("): code loop ");
	M33Console::print(us(t1 - t0));
	M33Console::print(" us, data loop ");
	M33Console::print(us(t2 - t1));
	M33Console::print(" us (");
	M33Console::print((r1 ^ r2) & 1); // use the results
	M33Console::print(")\n");
}
} // namespace

int main() {
	{
		M33Console::Lock lock;
		M33Console::print("M33: started. STGEN counter freq: ");
		M33Console::print(stgen_counter_freq());
		M33Console::print(" Hz\n");
	}

	run_benchmarks("DCACHE off");
	bool dcache_ok = mdrivlib::SystemCache::enable_dcache();
	run_benchmarks(dcache_ok ? "DCACHE on" : "DCACHE enable FAILED");

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
