// MP2's version of system/reent_mm.cc: which process is running on an A35 core (its main loop, or
// one of its interrupts), and the state the C and C++ runtimes keep per thread, kept per process:
// errno, and the C++ exception handling globals (the stack of caught exceptions, and the uncaught
// count). The toolchain's versions are single, shared by everything.
//
// The processes are MP1's (reent_mm.hh), but MP2 runs the GUI on core 0 (Core0Main), and core 1's
// main loop only waits for interrupts. MP2 doesn't run async threads yet.

#include "reent_mm.hh"
#include "drivers/stm32xx.h"
#include <array>
#include <cstdint>

namespace MetaModule
{

namespace
{
bool is_active(IRQn_Type irqn) {
	return GIC_GetIRQStatus(irqn) & 0b10;
}
} // namespace

Processes get_current_proc() {
	uint64_t mpidr;
	asm volatile("mrs %0, mpidr_el1" : "=r"(mpidr));

	// An interrupt stays active while one that preempted it runs, so check the higher priority ones
	// first (unlike MP1)
	if (mpidr & 0b1) {
		if (is_active(SGI4_IRQn)) // SMPCommand::PlayModuleList
			return Processes::Core1Audio;
		if (is_active(SGI1_IRQn)) // SMPCommand::ReadPatchGuiElements
			return Processes::Core1ReadPatchElements;
		return Processes::Core1Main;

	} else {
		if (is_active(HPDMA1_Channel0_IRQn)) // Audio SAI TX DMA (src/pro/conf/codec_sai_conf.hh)
			return Processes::Core0Audio;
		return Processes::Core0Main;
	}
}

int get_current_proc_id() {
	return static_cast<int>(get_current_proc());
}

namespace
{
std::array<int, NUM_PROCESSES> errnos{};
}

} // namespace MetaModule

// Replaces system/libc_stub.c's
extern "C" int *__errno() {
	return &MetaModule::errnos[MetaModule::get_current_proc_id()];
}

// libsupc++'s (unwind-cxx.h): replacing both functions replaces its eh_globals.o
namespace __cxxabiv1
{
struct __cxa_exception;

struct __cxa_eh_globals {
	__cxa_exception *caughtExceptions;
	unsigned int uncaughtExceptions;
};

namespace
{
std::array<__cxa_eh_globals, MetaModule::NUM_PROCESSES> eh_globals{};
}

extern "C" __cxa_eh_globals *__cxa_get_globals_fast() noexcept {
	return &eh_globals[MetaModule::get_current_proc_id()];
}

extern "C" __cxa_eh_globals *__cxa_get_globals() noexcept {
	return &eh_globals[MetaModule::get_current_proc_id()];
}
} // namespace __cxxabiv1
