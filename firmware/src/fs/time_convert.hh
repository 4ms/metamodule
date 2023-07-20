#pragma once

#include <cstdint>
#include <ctime>

struct FatTime {
	uint16_t date;
	uint16_t time;

	operator uint32_t() const {
		return ((uint32_t)date << 16) | (uint32_t)time;
	}
	uint8_t year() {
		return static_cast<uint8_t>(date >> 9) + 1980; //top 7 bits are year-1980 1980..2107
	}
	uint8_t month() {
		return static_cast<uint8_t>((date >> 5) & 0x0F); //middle 4 bits are month 1..12
	}
	uint8_t day() {
		return static_cast<uint8_t>(date & 0x1F); //bottom 5 bits are day 1..31
	}
	uint8_t hour() {
		return static_cast<uint8_t>(time >> 11); //top 5 bits are hour 0..23
	}
	uint8_t minute() {
		return static_cast<uint8_t>((time >> 5) & 0x3F); //middle 6 bits are minute 0..59
	}
	uint8_t second() {
		return static_cast<uint8_t>((time & 0x1F) * 2); //bottom 5 bits are seconds/2 0..29
	}
};

FatTime make_fattime(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second);
FatTime ticks_to_fattime(uint32_t ticks);
uint64_t fattime_to_ticks(FatTime fattime);
std::tm fattime_to_tm(FatTime fattime);

void set_time_now(std::tm &now, uint32_t ticks_since_poweron);

// void set_poweron_tm(std::tm &t);
time_t get_poweron_time();
