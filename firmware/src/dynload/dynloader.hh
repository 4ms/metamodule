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

// #include "build-simple-elf.hh"
// #include "build-elf.hh"
// #include "build-vcva-2.hh"
#include "befaco-strip-so.h"

#include "rack.hpp"

// extern "C" void _aeabi_atexit() {
// }

// GCC_OPTIMIZE_OFF
// plugin::Model *testHostCall(const char *slug) {
// 	printf("creating TestModule: %s\n", slug);
// 	return nullptr;
// }

// GCC_OPTIMIZE_OFF
// void testAddModel(rack::Model *model) {
// 	printf("calling addModel(%p)\n", model);
// }

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
		// Force these symbols from libc
		// TODO: how to do this otherwise?
		// We can't link the plugin to libc unless we compile a libc with it, since the arm-none-eabi libc
		// was not compiled with -fPIC
		// Linker KEEP()?
		// build libc with the plugin, mabye musl libc?
		exp(0.5f);
		expf(0.5f);
		fmod(0.5f, 1.f);
		sinf(0.5f);
		tanf(0.5f);
		tanh(0.5f);
		volatile auto keep = std::allocator<char>{};
	}

	GCC_OPTIMIZE_OFF
	void test() {
		keep_symbols();
		// elf.print_sec_headers();
		// elf.print_prog_headers();
		load_executable();
		process_relocs();
		init_globals();
		find_init_plugin_function();

		if (init_func) {
			init_func(&plugin);
		}

		while (true) {
			__NOP();
		}
	}

	GCC_OPTIMIZE_OFF
	void load_executable() {
		size_t load_size = elf.load_size();

		pr_info("Allocating %zu bytes for loading\n", load_size);
		block.code.resize(load_size);

		for (auto &seg : elf.segments) {
			if (seg.is_loadable()) {
				std::ranges::copy(seg, std::next(block.code.begin(), seg.address()));

				pr_info("Loading segment with file offset 0x%x-0x%x to %p-%p\n",
						seg.offset(),
						seg.offset() + seg.file_size(),
						std::next(block.code.begin(), seg.address()),
						std::next(block.code.begin(), seg.address() + seg.file_size()));
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
			ctor = reinterpret_cast<ctor_func_t>(addr + block.code.data());
			pr_info("Calling ctor %p\n", ctor);
			__BKPT();
			volatile int x = strlen("ABCD");
			ctor();
		}
	}

	//GCC_OPTIMIZE_OFF
	//void process_got() {
	//	auto got_section = elf.find_section(".got");
	//	if (!got_section) {
	//		pr_err("No .got section\n");
	//		return;
	//	}
	//	std::span<uint32_t> got{(uint32_t *)got_section->begin(), (uint32_t *)got_section->end()};
	//	//now we can write to got like got[3] = ...
	//	// but we don't know the index so... :(
	//}

	void process_relocs() {
		auto hostsyms = std::vector<ElfFile::HostSymbol>{};
		hostsyms.insert(hostsyms.end(), HostSymbols.begin(), HostSymbols.end());

		hostsyms.push_back({"_ZNSaIcEC1Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});
		hostsyms.push_back({"_ZNSaIcEC2Ev", 0, reinterpret_cast<uint32_t>(&_empty_func_stub)});

		for (auto sym : hostsyms)
			pr_dbg("%.*s %08x\n", sym.name.size(), sym.name.data(), sym.address);

		ElfFile::Relocater relocator{block.code.data(), hostsyms};

		for (auto reloc : elf.relocs) {
			relocator.write(reloc);
		}
	}

	GCC_OPTIMIZE_OFF
	void find_init_plugin_function() {
		auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initP6Plugin");

		if (init_plugin_symbol) {
			auto load_address = init_plugin_symbol->offset() /*- block.elf_offset*/ + block.code.data();
			init_func = reinterpret_cast<InitPluginFunc *>(load_address);

		} else
			pr_err("Did not find init(Plugin*)\n");
	}

	ElfFile::Elf elf;

	struct CodeBlock {
		uint32_t elf_offset{}; //offset where data starts in elf file
		std::vector<uint8_t> code;
	};
	CodeBlock block;

	rack::Plugin plugin;

	using InitPluginFunc = void(rack::Plugin *);
	InitPluginFunc *init_func{};
};
