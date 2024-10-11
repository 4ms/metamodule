#include "logger.hpp"
#include "console/pr_dbg.hh"
#include <ctime>

namespace rack::logger
{

std::string logPath;

void init() {
}

void destroy() {
}

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

static const char* const levelLabels[] = {
	"debug",
	"info",
	"warn",
	"fatal",
};

void log(Level level, const char *filename, int line, const char *func, const char *format, ...) {

	if (level == Level::DEBUG_LEVEL && LOG_LEVEL <= 3)
		return;
	else if (level == Level::INFO_LEVEL && LOG_LEVEL <= 2)
		return;
	else if (level == Level::WARN_LEVEL && LOG_LEVEL <= 1)
		return;
	else if (level == Level::FATAL_LEVEL && LOG_LEVEL <= 0)
		return;

	va_list args;
	va_start(args, format);
	printf("[%lld %s %s:%d %s] ", std::time(nullptr), levelLabels[level], filename, line, func);
	vprintf(format, args);
	printf("\n");
	va_end(args);
}

bool wasTruncated() {
	return false;
}

} // namespace rack::logger
