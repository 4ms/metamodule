// State that the C and C++ runtimes keep per thread, kept per core on the A35 (MP2): errno, and the
// C++ exception handling globals (the stack of caught exceptions, and the uncaught count).
// The toolchain's versions are single, shared by both cores, so an exception being handled on one
// core could be seen (and popped) by the other. MP1 keeps errno per process (system/reent_mm.cc).
//
// Interrupt handlers share their core's state. That's safe for exceptions: a handler's exception is
// thrown and caught before it returns, which leaves the state as it was.

#include <array>
#include <cstdint>

namespace
{
constexpr unsigned NumCores = 2;

unsigned this_core() {
	uint64_t mpidr;
	asm volatile("mrs %0, mpidr_el1" : "=r"(mpidr));
	return (mpidr & 0xFF) % NumCores;
}

std::array<int, NumCores> errnos{};
} // namespace

// Replaces system/libc_stub.c's
extern "C" int *__errno() {
	return &errnos[this_core()];
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
std::array<__cxa_eh_globals, NumCores> eh_globals{};
}

extern "C" __cxa_eh_globals *__cxa_get_globals_fast() noexcept {
	return &eh_globals[this_core()];
}

extern "C" __cxa_eh_globals *__cxa_get_globals() noexcept {
	return &eh_globals[this_core()];
}
} // namespace __cxxabiv1
