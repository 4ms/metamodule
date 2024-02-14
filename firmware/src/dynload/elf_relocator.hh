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

	void write(ElfReloc &rel) {
		// ARM ELF Docs:
		// A: Addend. Value extracted from the storage unit being relocated.
		// S: Value of the symbol referred to by the relocation.
		// P: Place (address of the storage unit) being relocated. It is calculated using the
		// r_offset field of the relocation directive and the base address of the section being relocated.

		auto reloc_address = reinterpret_cast<uint32_t *>(rel.reloc_offset() + base_address);
		switch (rel.reloc_type()) {
			case R_ARM_RELATIVE:
				pr_trace("R_ARM_RELATIVE: no action\n");
				break;

			case R_ARM_GLOB_DAT: {
				//"Resolves to the address of the specified symbol"
				if (rel.symbol_value() == 0) {
					auto sym = std::ranges::find_if(host_syms, [&rel](auto &s) { return s.name == rel.symbol_name(); });
					if (sym != host_syms.end()) {
						*reloc_address = sym->address;
						pr_dbg("R_ARM_GLOB_DAT: %s ", rel.symbol_name().data());
						pr_dbg("Found symbol at 0x%x\n", sym->address);
					} else {
						pr_err("R_ARM_GLOB_DAT: %s ", rel.symbol_name().data());
						pr_err("Symbol not found in host symbols\n");
					}
				} else {
					*reloc_address = rel.symbol_value() + base_address;
					pr_trace("R_ARM_GLOB_DAT: %s ", rel.symbol_name().data());
					pr_trace("write 0x%x (+%x) to address 0x%x (+%x)\n",
							 rel.symbol_value() + base_address,
							 rel.symbol_value(),
							 rel.reloc_offset() + base_address,
							 rel.reloc_offset());
				}
			} break;

			case R_ARM_ABS32: {
				pr_trace("R_ARM_ABS32: %s, write 0x%x (+%x) to address 0x%x (+%x)\n",
						 rel.symbol_name().data(),
						 rel.symbol_value() + *reloc_address + base_address,
						 rel.symbol_value() + *reloc_address,
						 rel.reloc_offset() + base_address,
						 rel.reloc_offset());
				// S + A
				// This seems like it makes sense since we need the base_Address, but it's P +A:
				*reloc_address = *reloc_address + rel.symbol_value() + base_address;
				// This is S+A but doesn't seem to be an "absolute" address
				// *reloc_address += symbol_value();

			} break;

			// Provide the address of the symbol found in the host
			case R_ARM_JUMP_SLOT: {
				//S+A
				// "Resolves to the address of the specified symbol"
				if (rel.symbol_value() == 0) {
					auto sym = std::ranges::find_if(host_syms, [&rel](auto &s) { return s.name == rel.symbol_name(); });
					if (sym != host_syms.end()) {
						*reloc_address = sym->address;
						pr_trace("R_ARM_JUMP_SLOT: %s ", rel.symbol_name().data());
						pr_trace("Found symbol at 0x%x\n", sym->address);
					} else {
						pr_err("R_ARM_JUMP_SLOT: %s ", rel.symbol_name().data());
						pr_err("Symbol not found in host symbols\n");
					}
				} else {
					pr_trace("R_ARM_JUMP_SLOT: %s ", rel.symbol_name().data());
					pr_trace("write 0x%x (+%x) to address 0x%x (+%x)\n",
							 rel.symbol_value() + base_address,
							 rel.symbol_value(),
							 rel.reloc_offset() + base_address,
							 rel.reloc_offset());
					*reloc_address = rel.symbol_value() + base_address;
				}

			} break;

			default:
				pr_dbg("Unknown reloc (%d) reloc %x, symbol value %x\n",
					   rel.reloc_type(),
					   rel.symbol_value(),
					   rel.reloc_offset());

				break;
		}
	}
};

} // namespace ElfFile
