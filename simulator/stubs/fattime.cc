#include "fs/time_convert.hh"
#include <ctime>

// Timestamp files with the host's current local time.
// std::localtime can return nullptr (e.g. on Windows for out-of-range values),
// so fall back to the FAT epoch rather than crash.
extern "C" uint32_t get_fattime() {
	std::time_t now = std::time(nullptr);
	std::tm *t = std::localtime(&now);
	if (!t)
		return (uint32_t)make_fattime(1980, 1, 1, 0, 0, 0);

	return (uint32_t)make_fattime(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
