#pragma once
#include "debug.hh"
#include "dynload/elf_relocator.hh"
#include "dynload/host_sym_list.hh"
#include "dynload/host_symbol.hh"
#include "elf_file.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <cstring>
#include <elf.h>
#include <span>
#include <string>
#include <vector>

#include "CoreModules/elements/dump.hh"
#include "rack.hpp"

// #include "build-simple-elf.hh"
// #include "build-elf.hh"
// #include "build-vcva-2.hh"
// #include "befaco-strip-so.h"
#include "befaco-strip-so-2modules.h"

GCC_OPTIMIZE_OFF
extern "C" void _empty_func_stub() {
}

struct DynLoadTest {

	DynLoadTest()
		// : elf{{testbrand_elf, testbrand_elf_len}} {
		: elf{{Befaco_strip_so, Befaco_strip_so_len}} {
	}

	GCC_OPTIMIZE_OFF
	void keep_symbols() {
		// Force these symbols from libc and other libs
		// TODO: how to do this otherwise?
		// We can't link the plugin to libc unless we compile a libc with it, since the arm-none-eabi libc
		// was not compiled with -fPIC
		// - Linker KEEP()?
		// - build libc with the plugin, mabye musl libc?
		// - build plugin with json library
		exp(0.5f);
		expf(0.5f);
		fmod(0.5f, 1.f);
		sinf(0.5f);
		tanf(0.5f);
		tanh(0.5f);
		volatile auto keep = std::allocator<char>{}; //seems to do nothing
		volatile int x = strlen("ABCD");
		auto savefunc = &json_object_set_new;
	}

	GCC_OPTIMIZE_OFF
	void test() {
		keep_symbols();
		// elf.print_sec_headers();
		// elf.print_prog_headers();
		load_executable();
		process_relocs();
		init_globals();

		// test_run_module();

		find_init_plugin_function();

		if (init_func) {
			init_func(&plugin);
		}

		// while (true) {
		// 	__NOP();
		// }
	}

	GCC_OPTIMIZE_OFF
	void load_executable() {
		size_t load_size = elf.load_size();

		// pr_info("Need %zu bytes for loading (%zu max)\n", load_size, codeblock.code.size());
		// if (load_size > codeblock.code.size()) {
		// 	pr_err("Too big!\n");
		// 	return;
		// }
		codeblock.code.resize(load_size);
		pr_info("Allocating %zu bytes for loading code at 0x%x\n", load_size, codeblock.code.begin());

		for (auto &seg : elf.segments) {
			if (seg.is_loadable()) {
				std::ranges::copy(seg, std::next(codeblock.code.begin(), seg.address()));

				pr_info("Loading segment with file offset 0x%x-0x%x to %p-%p\n",
						seg.offset(),
						seg.offset() + seg.file_size(),
						std::next(codeblock.code.begin(), seg.address()),
						std::next(codeblock.code.begin(), seg.address() + seg.file_size()));
			}
		}
	}

	GCC_OPTIMIZE_OFF
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
			ctor = reinterpret_cast<ctor_func_t>(addr + codeblock.code.data());
			pr_info("Calling ctor %p\n", ctor);
			ctor();
		}
	}

	GCC_OPTIMIZE_OFF
	void test_run_module() {
		printf("EvenVCOPlugin:\n");
		MetaModule::DumpModuleInfo::print("EvenVCOPlugin");

		printf("DualAtenuverterPlugin\n");
		MetaModule::DumpModuleInfo::print("DualAtenuverterPlugin");

		auto evenvco = MetaModule::ModuleFactory::create("EvenVCOPlugin");
		auto dualat = MetaModule::ModuleFactory::create("DualAtenuverterPlugin");

		if (dualat) {
			pr_dbg("Dualat ptr is at %p\n", dualat.get());
		} else
			pr_dbg("Dual at did not create()");

		if (evenvco) {
			pr_dbg("Even is at %p\n", evenvco.get());
		} else
			pr_dbg("EvenVCO did not create()");

		evenvco->update();
		auto out1 = dualat->get_output(0);
		auto out2 = dualat->get_output(1);
		pr_dbg("Out 1 %f, Out 2 %f\n", out1, out2);
		dualat->update();
		dualat->mark_input_patched(0);
		dualat->mark_input_patched(1);
		dualat->mark_output_patched(0);
		dualat->mark_output_patched(1);
		dualat->set_param(0, 0.75f);
		dualat->set_param(1, 0.25f);
		dualat->set_param(2, 0.25f);
		dualat->set_param(3, 0.75f);
		dualat->set_input(0, 0.3333f);
		dualat->set_input(1, 0.8888f);
		dualat->update();
		out1 = dualat->get_output(0);
		out2 = dualat->get_output(1);
		pr_dbg("Out 1 %f, Out 2 %f\n", out1, out2);
	}

	void process_relocs() {
		auto hostsyms = std::vector<ElfFile::HostSymbol>{};
		hostsyms.insert(hostsyms.end(), HostSymbols.begin(), HostSymbols.end());

		hostsyms.push_back({"_ZNSaIcEC1Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC2Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcED1Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcED2Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC1ERKS_", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC2ERKS_", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});

		for (auto sym : hostsyms)
			pr_trace("%.*s %08x\n", sym.name.size(), sym.name.data(), sym.address);

		ElfFile::Relocater relocator{codeblock.code.data(), hostsyms};

		for (auto reloc : elf.relocs) {
			relocator.write(reloc);
		}
	}

	GCC_OPTIMIZE_OFF
	void find_init_plugin_function() {
		// auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initP6Plugin");
		auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initPN4rack6plugin6PluginE");

		if (init_plugin_symbol) {
			auto load_address = init_plugin_symbol->offset() /*- block.elf_offset*/ + codeblock.code.data();
			init_func = reinterpret_cast<InitPluginFunc *>(load_address);

		} else
			pr_err("Did not find init(Plugin*)\n");
	}

	ElfFile::Elf elf;

	rack::Plugin plugin;

	struct CodeBlock {
		std::vector<uint8_t> code;
		// std::array<uint8_t, 0x10'0000> alignas(0x10'000) code;
		uint32_t elf_offset{}; //offset where data starts in elf file
	};
	CodeBlock codeblock;

	using InitPluginFunc = void(rack::Plugin *);
	InitPluginFunc *init_func{};
};
