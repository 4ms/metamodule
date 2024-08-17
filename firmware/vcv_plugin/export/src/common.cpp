#include <common.hpp>
#include <string.hpp>

#if defined ARCH_WIN
#include <windows.h>

FILE *fopen_u8(const char *filename, const char *mode) {
	return _wfopen(rack::string::UTF8toUTF16(filename).c_str(), rack::string::UTF8toUTF16(mode).c_str());
}

#endif

namespace rack
{

const std::string APP_NAME = "MetaModule";
const std::string APP_EDITION = "";
const std::string APP_EDITION_NAME = "";
const std::string APP_VERSION_MAJOR = "2";
const std::string APP_VERSION = "2.4.1";

#if defined ARCH_WIN
const std::string APP_OS = "win";
const std::string APP_OS_NAME = "Windows";
#elif defined ARCH_MAC
const std::string APP_OS = "mac";
const std::string APP_OS_NAME = "macOS";
#elif defined ARCH_LIN
const std::string APP_OS = "lin";
const std::string APP_OS_NAME = "Linux";
#elif defined METAMODULE
const std::string APP_OS = "mm";
const std::string APP_OS_NAME = "MetaModule";
#endif
#if defined ARCH_X64
const std::string APP_CPU = "x64";
const std::string APP_CPU_NAME = "x64";
#elif defined ARCH_ARM64
const std::string APP_CPU = "arm64";
const std::string APP_CPU_NAME = "ARM64";
#endif
#if defined METAMODULE
const std::string APP_CPU = "armv7a";
const std::string APP_CPU_NAME = "armv7a";
#endif

const std::string API_URL = "";

} // namespace rack
