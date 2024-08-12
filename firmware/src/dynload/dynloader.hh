#pragma once
#include "CoreModules/dump.hh"
#include "debug.hh"
#include "elf_process/elf_file.hh"
#include "elf_process/elf_relocator.hh"
#include "host_sym_list.hh"
#include "keep-symbols.hh"
#include "metamodule-plugin-sdk/version.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <cstring>
#include <elf.h>
#include <span>
#include <string>
#include <vector>

namespace MetaModule
{

struct DynLoader {

	DynLoader(std::span<uint8_t> elf_file_data, std::vector<uint8_t> &code_buffer)
		: elf{elf_file_data}
		, codeblock{code_buffer} {

		keep_symbols();
		init_host_symbol_table();
	}

	std::string load() {
		if (elf.segments.size() == 0 || elf.sections.size() == 0 || elf.relocs.size() == 0) {
			pr_err("Not a valid elf file\n");
			return "Not a valid plugin file";
		}

		load_executable();

		if (auto err_msg = process_relocs(); err_msg != "") {
			pr_err("Failed: %s\n", err_msg.c_str());
			return err_msg;
		}

		init_globals();
		return "";
	}

	std::optional<Version> get_sdk_version() {
		auto sym = elf.find_dyn_symbol("_ZN10MetaModule11sdk_versionEv");
		if (!sym)
			sym = elf.find_symbol("_ZN10MetaModule11sdk_versionEv");
		if (!sym)
			sym = elf.find_dyn_symbol("sdk_version");
		if (!sym)
			sym = elf.find_symbol("sdk_version");
		if (!sym)
			return std::nullopt;

		auto func_address = sym->offset() + codeblock.data();

		auto version_func = *reinterpret_cast<Version (*)()>(func_address);

		auto plugin_sdk = version_func();

		pr_info("Plugin has version %d.%d.%d\n", plugin_sdk.major, plugin_sdk.minor, plugin_sdk.revision);

		return plugin_sdk;
	}

	template<typename PluginInitFunc>
	PluginInitFunc *find_init_func() {
		auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initPN4rack6plugin6PluginE");
		if (!init_plugin_symbol) {
			pr_trace("No c++ init(rack::plugin::Plugin*) symbol found, trying init()\n");
			init_plugin_symbol = elf.find_dyn_symbol("init");
		}

		if (!init_plugin_symbol) {
			pr_trace("No init() dyn symbol found, trying non-dyn init(Plugin*)\n");
			init_plugin_symbol = elf.find_symbol("_Z4initPN4rack6plugin6PluginE");
		}

		if (!init_plugin_symbol) {
			pr_trace("No non-dyn init(Plugin*) symbol found, trying non-dyn init()\n");
			init_plugin_symbol = elf.find_symbol("init");
		}

		if (init_plugin_symbol) {
			auto load_address = init_plugin_symbol->offset() + codeblock.data();
			return reinterpret_cast<PluginInitFunc *>(load_address);
		} else {
			pr_err("Did not find init function\n");
			return nullptr;
		}
	}

private:
	void load_executable() {
		size_t load_size = elf.load_size();

		codeblock.clear();
		codeblock.resize(load_size);
		pr_trace("Allocating %zu bytes for loading code at 0x%x\n", load_size, codeblock.begin());

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
		if (hostsyms.size() == 0) {
			auto host_symbols = get_host_symbols();
			pr_trace("Found %zu host symbols in binary to export for plugins\n", host_symbols.size());

			hostsyms.insert(hostsyms.end(), host_symbols.begin(), host_symbols.end());

			// for (auto sym : hostsyms)
			// 	pr_dump("%.*s %08x\n", sym.name.size(), sym.name.data(), sym.address);
		}
	}

	std::string process_relocs() {
		ElfFile::Relocater relocator{codeblock.data(), hostsyms};

		for (auto reloc : elf.relocs) {
			if (!relocator.write(reloc)) {
				std::string err_msg;
				if (reloc.symbol_name().data() && reloc.symbol_name().size() > 0)
					err_msg = "Missing symbol: " + std::string(reloc.symbol_name());
				else
					err_msg = "Unknown relocation entry";
				return err_msg;
			}
		}

		return "";
	}

	void init_globals() {
		auto initarray_section = elf.find_section(".init_array");
		if (!initarray_section) {
			pr_err("Could not find .init_array section\n");
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
			pr_trace("Calling ctor %p\n", ctor);
			ctor();
		}
	}

private:
	ElfFile::Elf elf;
	std::vector<uint8_t> &codeblock;

	static std::vector<ElfFile::HostSymbol> hostsyms;
};

} // namespace MetaModule
