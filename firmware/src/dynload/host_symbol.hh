#pragma once
#include <string_view>

namespace ElfFile
{

struct HostSymbol {
	std::string_view name{};
	uint32_t hash{};
	uintptr_t address{};
};

} // namespace ElfFile
