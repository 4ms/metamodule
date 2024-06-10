#include "logger.hpp"

namespace rack::logger
{

std::string logPath;

void init() {
}

void destroy() {
}

void log(Level level, const char *filename, int line, const char *func, const char *format, ...) {
	//
}

bool wasTruncated() {
	return false;
}

} // namespace rack::logger
