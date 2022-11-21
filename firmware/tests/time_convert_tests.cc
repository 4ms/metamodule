#include "doctest.h"
#include "src/time_convert.hh"
#include <cstdio>

TEST_CASE("roundtrip") {
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

	uint32_t ticks = fattime_to_ticks(ft);
	printf("ticks = %u\n", ticks);
	FatTime ft2 = ticks_to_fattime(ticks);
	printf("ft2.date = %d 0x%x, ft2.time = %d 0x%x\n", ft2.date, ft2.date, ft2.time, ft2.time);
	CHECK(ft.date == ft2.date);
	CHECK(ft.time == ft2.time);
}

TEST_CASE("tick -> ft -> tick") {
	uint32_t ticks = 1239481;
	auto ft = ticks_to_fattime(ticks);
	auto ticks2 = fattime_to_ticks(ft);
	CHECK(ticks == ticks2);
}
