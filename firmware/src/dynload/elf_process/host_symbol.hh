#pragma once
#include <string>
#include <cstdint>

namespace ElfFile
{

struct HostSymbol {
	std::string name{};
	uint32_t hash{};
	uintptr_t address{};
};

} // namespace ElfFile
