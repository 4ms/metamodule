#pragma once
#include "build-simple-elf.hh"
#include "debug.hh"
#include "elf_file.hh"
#include "pr_dbg.hh"
#include "rack.hpp"
#include "stm32mp1xx.h"
#include <cstring>
#include <elf.h>
#include <span>
#include <string>
#include <vector>

struct DynLoadTest {

	DynLoadTest()
		: elf{{testbrand_elf, testbrand_elf_len}} {
	}

	GCC_OPTIMIZE_OFF
	void test() {
		elf.print_sec_headers();
		load_executable();
		find_init_address();

		__BKPT();
		init_func(&plugin);

		while (true) {
			__NOP();
		}
	}

	GCC_OPTIMIZE_OFF
	void load_executable() {
		for (auto &sec : elf.sections) {
			if (sec.is_code() || sec.is_rodata()) {
				pr_info("Loading section %s to %p\n", sec.section_name().data(), code.exec_data.end());
				code.exec_data.insert(code.exec_data.end(), sec.begin(), sec.end());
				code.elf_offset = sec.offset();
				pr_info("Section has offset in elf file of 0x%x\n", code.elf_offset);
			}
		}
	}

	GCC_OPTIMIZE_OFF
	void process_relocs() {
	}

	GCC_OPTIMIZE_OFF
	void find_init_address() {
		auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initP6Plugin");
		if (init_plugin_symbol) {
			auto load_address = init_plugin_symbol->offset() - code.elf_offset + code.exec_data.data();
			pr_info("init(Plugin*) is at offset 0x%x => %08x\n", init_plugin_symbol->offset(), load_address);
			init_func = reinterpret_cast<InitPluginFunc *>(load_address);
		} else
			pr_info("Did not find init(Plugin*)\n");
		//scan symbols
	}

	ElfFile::Elf elf;
	struct CodeBlock {
		uint32_t elf_offset{}; //offset where data starts in elf file
		std::vector<uint8_t> exec_data;
	};

	CodeBlock code;
	rack::Plugin plugin;

	using InitPluginFunc = void(rack::Plugin *);
	InitPluginFunc *init_func;
};
