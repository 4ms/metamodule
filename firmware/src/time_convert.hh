#include <cstdint>
#include <ctime>
struct FatTime {
	uint16_t date;
	uint16_t time;

	operator uint32_t() const {
		return ((uint32_t)date << 16) | (uint32_t)time;
	}
};

FatTime make_fattime(unsigned year, unsigned month, unsigned day, unsigned hour, unsigned minute, unsigned second);
FatTime ticks_to_fattime(uint32_t ticks);
uint32_t fattime_to_ticks(FatTime fattime);
std::tm fattime_to_tm(FatTime fattime);
