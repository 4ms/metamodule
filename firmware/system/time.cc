#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <chrono>
#include <ctime>

void print_time() {
	auto secs = std::time(nullptr);
	auto tm = std::localtime(&secs);
	pr_info("Current Time: %04d-%d-%d %d:%02d:%02d (Ticks: %lu, posix time: %lld, chrono::now %lld)\n",
			tm->tm_year,
			tm->tm_mon + 1,
			tm->tm_mday,
			tm->tm_hour,
			tm->tm_min,
			tm->tm_sec,
			(unsigned long)HAL_GetTick(),
			secs,
			std::chrono::steady_clock::now().time_since_epoch().count() / 1'000'000LL);
}
