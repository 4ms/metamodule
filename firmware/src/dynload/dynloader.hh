#pragma once
#include "debug.hh"
#include "dynload/elf_relocator.hh"
#include "dynload/host_sym_list.hh"
// #include "dynload/host_symbol.hh"
#include "elf_file.hh"
#include "keep-symbols.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <cstring>
#include <elf.h>
#include <span>
#include <string>
#include <vector>

#include "CoreModules/elements/dump.hh"
#include "rack.hpp"

namespace MetaModule
{

struct DynLoader {

	DynLoader(std::span<uint8_t> elf_file_data, std::vector<uint8_t> &code_buffer)
		: elf{elf_file_data}
		, codeblock{code_buffer} {

		keep_symbols();

		init_host_symbol_table();
	}

	// GCC_OPTIMIZE_OFF
	bool load() {
		if (elf.segments.size() == 0 || elf.sections.size() == 0 || elf.relocs.size() == 0) {
			pr_err("Not a valid elf file\n");
			return false;
		}

		load_executable();
		bool ok = process_relocs();
		if (!ok)
			return false;

		init_globals();

		run_init_plugin_function();

		return true;
	}

	// GCC_OPTIMIZE_OFF
	void load_executable() {
		size_t load_size = elf.load_size();

		codeblock.clear();
		codeblock.resize(load_size);
		pr_info("Allocating %zu bytes for loading code at 0x%x\n", load_size, codeblock.begin());

		for (auto &seg : elf.segments) {
			if (seg.is_loadable()) {
				std::ranges::copy(seg, std::next(codeblock.begin(), seg.address()));

				pr_info("Loading segment with file offset 0x%x-0x%x to %p-%p\n",
						seg.offset(),
						seg.offset() + seg.file_size(),
						std::next(codeblock.begin(), seg.address()),
						std::next(codeblock.begin(), seg.address() + seg.file_size()));
			}
		}
	}

	void init_host_symbol_table() {
		auto HostSymbols = get_host_symbols();

		hostsyms.clear();
		hostsyms.insert(hostsyms.end(), HostSymbols.begin(), HostSymbols.end());

		hostsyms.push_back({"_ZNSaIcEC1Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC2Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcED1Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcED2Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC1ERKS_", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC2ERKS_", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});

		for (auto sym : hostsyms)
			pr_trace("%.*s %08x\n", sym.name.size(), sym.name.data(), sym.address);
	}

	bool process_relocs() {
		bool all_syms_found = true;
		ElfFile::Relocater relocator{codeblock.data(), hostsyms};

		for (auto reloc : elf.relocs) {
			bool ok = relocator.write(reloc);
			if (!ok) {
				all_syms_found = false;
				//TODO: store the missing symbol name so we can notify the user later
			}
		}

		return all_syms_found;
	}

	// GCC_OPTIMIZE_OFF
	void init_globals() {
		auto initarray_section = elf.find_section(".init_array");
		if (!initarray_section) {
			pr_err("Could not find .init_array section");
			return;
		}

		if (!initarray_section->is_init_array()) {
			pr_err(".init_array section is not an INITARRAY type\n");
		}

		using ctor_func_t = void (*)();
		auto ctors =
			std::span<ctor_func_t>((ctor_func_t *)initarray_section->begin(), initarray_section->num_entries());

		for (auto ctor : ctors) {
			auto addr = reinterpret_cast<uint32_t>(ctor);
			ctor = reinterpret_cast<ctor_func_t>(addr + codeblock.data());
			pr_info("Calling ctor %p\n", ctor);
			ctor();
		}
	}

	// GCC_OPTIMIZE_OFF
	void run_init_plugin_function() {
		// auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initP6Plugin");
		auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initPN4rack6plugin6PluginE");

		plugin.models.clear();

		if (init_plugin_symbol) {
			auto load_address = init_plugin_symbol->offset() + codeblock.data();
			init_func = reinterpret_cast<InitPluginFunc *>(load_address);
			if (init_func) {
				init_func(&plugin);
			} else
				pr_err("Symbol init(rack::plugin::Plugin*) was null\n");

		} else
			pr_err("Did not find init(rack::plugin::Plugin*)\n");
	}

private:
	ElfFile::Elf elf;
	rack::Plugin plugin;
	std::vector<uint8_t> &codeblock;

	using InitPluginFunc = void(rack::Plugin *);
	InitPluginFunc *init_func{};

	std::vector<ElfFile::HostSymbol> hostsyms;
};

} // namespace MetaModule
