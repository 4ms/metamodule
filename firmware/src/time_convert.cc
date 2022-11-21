#include "time_convert.hh"
#include <cstdint>
#include <ctime>

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
	return t;
}

//timestamp_to_ticks
uint32_t fattime_to_ticks(FatTime fattime) {
	std::tm t = fattime_to_tm(fattime);
	// uint16_t fdate = fattime.date;
	// uint16_t ftime = fattime.time;
	// std::tm t;
	// t.tm_year = static_cast<uint8_t>(fdate >> 9);		  //top 7 bits are year-1980 1980..2107
	// t.tm_mon = static_cast<uint8_t>((fdate >> 5) & 0x0F); //middle 4 bits are month 1..12
	// t.tm_mday = static_cast<uint8_t>(fdate & 0x1F);		  //bottom 5 bits are day 1..31
	// t.tm_hour = static_cast<uint8_t>(ftime >> 11);		  //top 5 bits are hour 0..23
	// t.tm_min = static_cast<uint8_t>((ftime >> 5) & 0x3F); //middle 6 bits are minute 0..59
	// t.tm_sec = static_cast<uint8_t>((ftime & 0x1F) * 2);  //bottom 5 bits are seconds/2 0..29
	return mktime(&t);
}

FatTime ticks_to_fattime(uint32_t ticks) {
	//Convert ticks + starting point to year/mo/day hh:mm:ss
	time_t ticks_l = ticks / 10;
	std::tm *t = std::localtime(&ticks_l);

	//Then convert that to fattime
	return make_fattime(t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

// {
// uint32_t seconds = ticks / 1000;
// uint32_t minutes = seconds / 60;
// uint32_t hours = minutes / 60;
// uint32_t days = hours / 24;
// uint32_t months = days / 30; //FIXME
// uint32_t years = months / 12;

// seconds -= minutes * 60;
// minutes -= hours * 60;
// hours -= days * 24;
// days -= months * 30;
// months -= years * 12;

// return make_fattime(2018 + years, 9 + months, 19 + days, 7 + hours, 30 + minutes, 0 + seconds);
// }
