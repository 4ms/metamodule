#include "doctest.h"
#include "src/fs/time_convert.hh"
#include <cstdio>

TEST_CASE("fatetime->tm") {
	unsigned year = 1980;
	unsigned month = 1;
	unsigned day = 2;
	unsigned hour = 14;
	unsigned minute = 24;
	unsigned second = 52;
	FatTime ft = make_fattime(year, month, day, hour, minute, second);
	std::tm t = fattime_to_tm(ft);
	CHECK(t.tm_year == year);
	CHECK(t.tm_mon == month);
	CHECK(t.tm_mday == day);
	CHECK(t.tm_hour == hour);
	CHECK(t.tm_min == minute);
	CHECK(t.tm_sec == second);
}

void print_tm(std::tm t) {
	printf("%u/%u/%u %u:%02u:%02u (%lld)\n",
		   t.tm_year,
		   t.tm_mon,
		   t.tm_mday,
		   t.tm_hour,
		   t.tm_min,
		   t.tm_sec,
		   (long long)mktime(&t));
}

TEST_CASE("fattime<->ticks") {
	std::tm poweron_tm{
		.tm_sec = 0,
		.tm_min = 0,
		.tm_hour = 1,
		.tm_mday = 1,
		.tm_mon = 2,
		.tm_year = 2000,
	};
	set_time_now(poweron_tm, 0); //0 ticks since power-on

	FatTime ft = make_fattime(2000, 2, 1, 4, 30, 10); //1:00 -> 4:30:10 is 3.5 hours + 10 seconds after poweron

	uint32_t ticks = fattime_to_ticks(ft);
	uint32_t elapsedtm = ((3.5 * 60 * 60) + 10) * 1000; //3.5 hours + 10 seconds
	CHECK(ticks == elapsedtm);

	FatTime ft2 = ticks_to_fattime(ticks);
	CHECK(ft.date == ft2.date);
	CHECK(ft.time == ft2.time);
}

TEST_CASE("tick -> ft -> tick") {
	uint32_t ticks_ms = 1241234;

	auto ft = ticks_to_fattime(ticks_ms);
	auto ticks_ms2 = fattime_to_ticks(ft);

	//Result will be a multiple of 2000 since the resolution of FatTime is 2sec (2000ms)
	ticks_ms /= 2000;
	ticks_ms *= 2000;
	CHECK(ticks_ms == ticks_ms2);
}
