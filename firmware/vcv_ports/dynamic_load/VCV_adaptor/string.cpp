// #include "printf.h"
#include "VCV_adaptor/common.hpp"
#include <cstdarg>
#include <string>

namespace rack::string
{

std::string fV(const char *format, va_list args) {
	// va_lists cannot be reused but we need it twice, so clone args.
	va_list args2;
	va_copy(args2, args);
	DEFER({ va_end(args2); });
	// Compute size of required buffer
	int size = vsnprintf(nullptr, 0, format, args);
	if (size < 0)
		return "";
	// Create buffer
	std::string s;
	s.resize(size);
	vsnprintf(&s[0], size + 1, format, args2);
	return s;
}

std::string f(const char *format, ...) {
	va_list args;
	va_start(args, format);
	std::string s = fV(format, args);
	va_end(args);
	return s;
}

} // namespace rack::string
