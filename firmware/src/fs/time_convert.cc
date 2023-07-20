#include "time_convert.hh"
#include <cstdint>
#include <ctime>

// FatTime: (4 bytes) date and time, minimum 1980, resolution 2 seconds. LFS and FATFS use this
// Ticks: (4 bytes) milliseconds since power-on. Hardware uses this
// std::tm: (36 bytes) date and time, minimum 1970, resolution 1 second. Intermediate value
// time_t: (8 bytes) seconds since 1970

static std::tm default_poweron_tm = {
	.tm_sec = 0,
	.tm_min = 0,
	.tm_hour = 1,
	.tm_mday = 1,
	.tm_mon = 1,
	.tm_year = 2000,
	.tm_isdst = 0,
};

static inline time_t mktime_(std::tm *t) {
	return mktime(t);
}

static time_t poweron_sec_since_epoch = mktime_(&default_poweron_tm);

void set_time_now(std::tm &now, uint32_t ticks_since_poweron) {
	poweron_sec_since_epoch = mktime_(&now) - (time_t)(ticks_since_poweron / 1000);
}

time_t get_poweron_time() {
	return poweron_sec_since_epoch;
}

FatTime make_fattime(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second) {
	FatTime ft;
	ft.date = (year - 1980) << 9;
	ft.date |= month << 5;
	ft.date |= day;
	ft.time = hour << 11;
	ft.time |= minute << 5;
	ft.time |= second / 2;
	return ft;
}

FatTime tm_to_fattime(std::tm &t) {
	return make_fattime(t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}

std::tm fattime_to_tm(FatTime fattime) {
	uint16_t fdate = fattime.date;
	uint16_t ftime = fattime.time;
	std::tm t;
	t.tm_year = static_cast<uint8_t>(fdate >> 9) + 1980;  //top 7 bits are year-1980 1980..2107
	t.tm_mon = static_cast<uint8_t>((fdate >> 5) & 0x0F); //middle 4 bits are month 1..12
	t.tm_mday = static_cast<uint8_t>(fdate & 0x1F);		  //bottom 5 bits are day 1..31
	t.tm_hour = static_cast<uint8_t>(ftime >> 11);		  //top 5 bits are hour 0..23
	t.tm_min = static_cast<uint8_t>((ftime >> 5) & 0x3F); //middle 6 bits are minute 0..59
	t.tm_sec = static_cast<uint8_t>((ftime & 0x1F) * 2);  //bottom 5 bits are seconds/2 0..29
	t.tm_isdst = 0;
	return t;
}

//Convert FatTime to ticks since power-on
uint64_t fattime_to_ticks(FatTime fattime) {
	std::tm t = fattime_to_tm(fattime);
	time_t secs = mktime_(&t);
	if (secs <= poweron_sec_since_epoch)
		return 0; //Negative ticks?

	return (secs - poweron_sec_since_epoch) * 1000;
}

// Convert ticks in ms since poweron to FatTime
FatTime ticks_to_fattime(uint32_t ticks) {
	time_t secs = (time_t)(ticks / 1000) + poweron_sec_since_epoch;
	std::tm *t = std::localtime(&secs);

	return make_fattime(t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

#if TIME_PRINT_TESTS_ENABLE
#include "printf.h"
void time_tests() {
	printf_("Time Tests\n");
	unsigned year = 1980;
	unsigned month = 1;
	unsigned day = 2;
	unsigned hour = 14;
	unsigned minute = 24;
	unsigned second = 52;
	FatTime ft = make_fattime(year, month, day, hour, minute, second);
	printf_("ft(1980/1/2 14:24:52) = %x\n", (uint32_t)ft);
	FatTime ft1 = make_fattime(year + 1, month, day, hour, minute, second);
	printf_("ft1(1981/1/2 14:24:52) = %x\n", (uint32_t)ft1);
	FatTime ft2 = make_fattime(year + 1, month, day, hour, minute, second + 2);
	printf_("ft2(1981/1/2 14:24:54) = %x\n", (uint32_t)ft2);
	std::tm t = fattime_to_tm(ft);
	printf_("ft to tm: %u/%u/%u %u:%u:%u\n", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	t = fattime_to_tm(ft1);
	printf_("ft1 to tm: %u/%u/%u %u:%u:%u\n", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	t = fattime_to_tm(ft2);
	printf_("ft2 to tm: %u/%u/%u %u:%u:%u\n", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	std::tm poweron_tm = {
		.tm_sec = 0,
		.tm_min = 40,
		.tm_hour = 9,
		.tm_mday = 21,
		.tm_mon = 11,
		.tm_year = 2022,
	};
	time_t poweron_time = mktime(&poweron_tm);
	printf_("poweron_time: secs since epoch = %llu", poweron_time);
	printf_(" = %u/%u/%u %u:%u:%u\n",
			poweron_tm.tm_year,
			poweron_tm.tm_mon,
			poweron_tm.tm_mday,
			poweron_tm.tm_hour,
			poweron_tm.tm_min,
			poweron_tm.tm_sec);

	std::tm *tt = std::localtime(&poweron_time);
	printf_("localtime(poweron_time): %u/%u/%u %u:%u:%u\n",
			tt->tm_year,
			tt->tm_mon,
			tt->tm_mday,
			tt->tm_hour,
			tt->tm_min,
			tt->tm_sec);

	FatTime ftt = ticks_to_fattime(3600000); //1 hour
	t = fattime_to_tm(ftt);
	printf_("3600000 ticks to tm: %u/%u/%u %u:%u:%u\n", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	uint32_t nowticks = HAL_GetTick();
	FatTime fn = ticks_to_fattime(nowticks);
	t = fattime_to_tm(fn);
	printf_("%u ticks = fat 0x%x = tm: %u/%u/%u %u:%u:%u\n",
			nowticks,
			(uint32_t)fn,
			t.tm_year,
			t.tm_mon,
			t.tm_mday,
			t.tm_hour,
			t.tm_min,
			t.tm_sec);

	printf_("set time now\n");
	set_time_now(poweron_tm, nowticks);
	FatTime nowfat = ticks_to_fattime(nowticks);
	printf_("nowticks: %u, nowfat: 0x%x, ", nowticks, nowfat);
	t = fattime_to_tm(nowfat);
	printf_("tm: %u/%u/%u %u:%u:%u\n", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}
#endif
