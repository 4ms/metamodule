#pragma once
#include <cstdarg>
#include <string>

namespace rack::string
{

std::string f(const char *format, ...);
std::string fV(const char *format, va_list args);

} // namespace rack::string
