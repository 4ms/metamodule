#pragma once
#include <cstdint>
#include <elf.h>

// The plugin loader is built for exactly one ELF class per firmware target:
// - ELF32 / ARM 32-bit (STM32MP1 "medium"): REL-style relocations (.rel.dyn/.rel.plt)
// - ELF64 / AArch64 (STM32MP2 "pro"): RELA-style relocations (.rela.dyn/.rela.plt)
// Define METAMODULE_ELF64 (the mp2 build does) to select the 64-bit class.
// The default is ELF32 so existing builds are unchanged.

namespace ElfFile
{

#if defined(METAMODULE_ELF64)

inline constexpr bool ElfClass64 = true;
using Elf_Ehdr = Elf64_Ehdr;
using Elf_Shdr = Elf64_Shdr;
using Elf_Phdr = Elf64_Phdr;
using Elf_Sym = Elf64_Sym;
using Elf_Rel = Elf64_Rela; // AArch64 dynamic relocations carry explicit addends
using elf_addr_t = uint64_t;

constexpr uint32_t elf_r_sym(uint64_t info) {
	return ELF64_R_SYM(info);
}
constexpr uint32_t elf_r_type(uint64_t info) {
	return ELF64_R_TYPE(info);
}

inline constexpr const char *RelDynSectionName = ".rela.dyn";
inline constexpr const char *RelPltSectionName = ".rela.plt";

#else

inline constexpr bool ElfClass64 = false;
using Elf_Ehdr = Elf32_Ehdr;
using Elf_Shdr = Elf32_Shdr;
using Elf_Phdr = Elf32_Phdr;
using Elf_Sym = Elf32_Sym;
using Elf_Rel = Elf32_Rel; // ARM32 dynamic relocations have implicit (in-place) addends
using elf_addr_t = uint32_t;

constexpr uint32_t elf_r_sym(uint32_t info) {
	return ELF32_R_SYM(info);
}
constexpr uint32_t elf_r_type(uint32_t info) {
	return ELF32_R_TYPE(info);
}

inline constexpr const char *RelDynSectionName = ".rel.dyn";
inline constexpr const char *RelPltSectionName = ".rel.plt";

#endif

// Not all toolchains' <elf.h> define the AArch64 relocation codes:
#ifndef R_AARCH64_ABS64
#define R_AARCH64_ABS64 257
#endif
#ifndef R_AARCH64_GLOB_DAT
#define R_AARCH64_GLOB_DAT 1025
#endif
#ifndef R_AARCH64_JUMP_SLOT
#define R_AARCH64_JUMP_SLOT 1026
#endif
#ifndef R_AARCH64_RELATIVE
#define R_AARCH64_RELATIVE 1027
#endif

} // namespace ElfFile
