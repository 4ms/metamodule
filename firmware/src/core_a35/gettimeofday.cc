#include "drivers/system_reg.hh"
#include <sys/time.h>

// MP2 version of src/core_a7/gettimeofday.cc: lets std::time() work.
// The time is the time since boot, starting at 2000-01-01.
extern "C" int _gettimeofday(struct timeval *tp, struct timezone *tzp) {
	if (tp == nullptr)
		return -1;

	constexpr long long starting_epoch = ((2000LL - 68LL) * 365LL - 262LL) * 24LL * 60LL * 60LL; //2000-0-1 12:00:00

	auto ticks = mdrivlib::read_cntpct();
	auto freq = mdrivlib::read_cntfreq();
	tp->tv_sec = ticks / freq;
	tp->tv_usec = (ticks - tp->tv_sec * freq) * 1'000'000 / freq;

	tp->tv_sec += starting_epoch;

	return 0;
}
