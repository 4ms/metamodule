#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <ctime>

//_gettimeofday allows std::time() to work
extern "C" int _gettimeofday(struct timeval *tp, struct timezone *tzp) {
	if (tp == nullptr)
		return -1;

	constexpr long long starting_epoch = ((2000LL - 68LL) * 365LL - 262LL) * 24LL * 60LL * 60LL; //2000-0-1 12:00:00

	auto ticks24MHz = PL1_GetCurrentPhysicalValue();
	tp->tv_sec = ticks24MHz / (uint64_t)24'000'000;
	tp->tv_usec = (ticks24MHz - (tp->tv_sec * (uint64_t)24'000'000)) / 24;

	tp->tv_sec += starting_epoch;

	return 0;
}

void print_time() {
	auto secs = std::time(nullptr);
	auto tm = std::localtime(&secs);
	pr_info("Current Time: %04d-%d-%d %d:%02d:%02d (Ticks: %lu, posix time: %lld)\n",
			tm->tm_year,
			tm->tm_mon + 1,
			tm->tm_mday,
			tm->tm_hour,
			tm->tm_min,
			tm->tm_sec,
			(unsigned long)HAL_GetTick(),
			secs);
}
