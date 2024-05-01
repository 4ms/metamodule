#pragma once
#include "elf_helpers.hh"
#include "elf_reloc.hh"
#include "elf_symbol.hh"
#include "host_symbol.hh"
#include "pr_dbg.hh"
#include <algorithm>
#include <elf.h>
#include <span>
#include <string_view>

namespace ElfFile
{

class Relocater {
	uintptr_t base_address;
	std::span<const HostSymbol> host_syms;

public:
	Relocater(uint8_t *elf_load_address, const std::span<const HostSymbol> host_symbols)
		: base_address{reinterpret_cast<uintptr_t>(elf_load_address)}
		, host_syms{host_symbols} {
	}

	bool write(ElfReloc &rel) {
		bool ok = false;

		// ARM ELF Docs:
		// A: Addend. Value extracted from the storage unit being relocated.
		// S: Value of the symbol referred to by the relocation.
		// P: Place (address of the storage unit) being relocated. It is calculated using the
		// r_offset field of the relocation directive and the base address of the section being relocated.

		auto reloc_address = reinterpret_cast<uint32_t *>(rel.reloc_offset() + base_address);

		switch (rel.reloc_type()) {

			case R_ARM_RELATIVE:
				*reloc_address = rel.symbol_value() + base_address;
				ok = true;
				pr_dump("R_ARM_RELATIVE: %s ", rel.symbol_name().data());
				pr_dump("write 0x%x (+%x) to address 0x%x (+%x)\n",
						rel.symbol_value() + base_address,
						rel.symbol_value(),
						rel.reloc_offset() + base_address,
						rel.reloc_offset());
				break;

			case R_ARM_GLOB_DAT: {
				//"Resolves to the address of the specified symbol"
				if (rel.symbol_value() == 0) {
					auto sym = std::ranges::find_if(host_syms, [&rel](auto &s) { return s.name == rel.symbol_name(); });
					if (sym != host_syms.end()) {
						pr_dump("R_ARM_GLOB_DAT: %s ", rel.symbol_name().data());
						pr_dump("Symbol val is 0. Found symbol in host at 0x%x\n", sym->address);
						pr_dump(" write this to address 0x%x (+%x)\n",
								rel.reloc_offset() + base_address,
								rel.reloc_offset());
						*reloc_address = sym->address;
						ok = true;
					} else {
						pr_err("R_ARM_GLOB_DAT: %s ", rel.symbol_name().data());
						pr_err("\nSymbol value is 0 and name not found in host symbols\n");
						ok = false;
					}
				} else {
					*reloc_address = rel.symbol_value() + base_address;
					ok = true;
					pr_dump("R_ARM_GLOB_DAT: %s ", rel.symbol_name().data());
					pr_dump("write 0x%x (+%x) to address 0x%x (+%x)\n",
							rel.symbol_value() + base_address,
							rel.symbol_value(),
							rel.reloc_offset() + base_address,
							rel.reloc_offset());
				}
			} break;

			case R_ARM_ABS32: {
				if (rel.symbol_value() == 0) {

					auto sym = std::ranges::find_if(host_syms, [&rel](auto &s) { return s.name == rel.symbol_name(); });
					if (sym != host_syms.end()) {
						pr_dump("R_ARM_ABS32: %s, symval = 0: ", rel.symbol_name().data());
						pr_dump("Found sym in host 0x%x, writing this to 0x%x (+%x)\n",
								sym->address,
								rel.reloc_offset() + base_address,
								rel.reloc_offset());
						*reloc_address = sym->address;
						ok = true;
					} else {
						pr_err("R_ARM_ABS32: %s, symval = 0 ", rel.symbol_name().data());
						pr_err("\nSymbol not found in host symbols\n");
						ok = false;
					}

				} else {
					pr_dump("R_ARM_ABS32: %s, symval = 0x%x, write 0x%x (+%x) to address 0x%x (+%x)\n",
							rel.symbol_name().data(),
							rel.symbol_value(),
							rel.symbol_value() + *reloc_address + base_address,
							rel.symbol_value() + *reloc_address,
							rel.reloc_offset() + base_address,
							rel.reloc_offset());
					*reloc_address = *reloc_address + rel.symbol_value() + base_address;
					ok = true;
				}

			} break;

			// Provide the address of the symbol found in the host
			case R_ARM_JUMP_SLOT: {
				//S+A
				// "Resolves to the address of the specified symbol"
				if (rel.symbol_value() == 0) {
					auto sym = std::ranges::find_if(host_syms, [&rel](auto &s) { return s.name == rel.symbol_name(); });
					if (sym != host_syms.end()) {
						pr_dump("R_ARM_JUMP_SLOT: %s ", rel.symbol_name().data());
						pr_dump("Found symbol at 0x%x\n", sym->address);
						*reloc_address = sym->address;
						ok = true;
					} else {
						pr_err("R_ARM_JUMP_SLOT: %s ", rel.symbol_name().data());
						pr_err("\nSymbol not found in host symbols\n");
						ok = false;
					}
				} else {
					pr_dump("R_ARM_JUMP_SLOT: %s ", rel.symbol_name().data());
					pr_dump("write 0x%x (+%x) to address 0x%x (+%x)\n",
							rel.symbol_value() + base_address,
							rel.symbol_value(),
							rel.reloc_offset() + base_address,
							rel.reloc_offset());
					*reloc_address = rel.symbol_value() + base_address;
					ok = true;
				}

			} break;

			default:
				pr_err("Unknown reloc (%d) reloc %x, symbol value %x\n",
					   rel.reloc_type(),
					   rel.symbol_value(),
					   rel.reloc_offset());
				ok = false;
				break;
		}
		return ok;
	}
};

} // namespace ElfFile
