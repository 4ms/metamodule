#include "drivers/stm32xx.h"

unsigned make_timestamp(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second) {
	uint32_t date = (year - 1980) << 9;
	date |= month << 5;
	date |= day;
	uint32_t time = hour << 11;
	time |= minute << 5;
	time |= second / 2;
	return (date << 16) | time;
}

//ticks_to_timestamp
//timestamp_to_ticks

extern "C" uint32_t get_fattime() {
	uint32_t seconds = HAL_GetTick() / 1000;
	uint32_t minutes = seconds / 60;
	uint32_t hours = minutes / 60;
	uint32_t days = hours / 24;
	uint32_t months = days / 30; //FIXME
	uint32_t years = months / 12;

	seconds -= minutes * 60;
	minutes -= hours * 60;
	hours -= days * 24;
	days -= months * 30;
	months -= years * 12;

	// FIXME: rollover
	return make_timestamp(2018 + years, 9 + months, 19 + days, 7 + hours, 30 + minutes, 0 + seconds);
}
