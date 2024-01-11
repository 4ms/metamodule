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
		// elf.print_sec_headers();
		elf.print_prog_headers();
		load_executable();

		// Handle .rel.dyn section:
		// R_ARM_GLOB_DAT: global data needs... a pointer?
		// Relocation section '.rel.dyn' at offset 0x200 contains 4 entries:
		//  Offset     Info    Type                Sym. Value  Symbol's Name
		// 000012d8  00000017 R_ARM_RELATIVE
		// 00001390  00000415 R_ARM_GLOB_DAT         0000139c   modelTest
		// 00001394  00000715 R_ARM_GLOB_DAT         000013a0   pluginInstance
		// 00001398  00000502 R_ARM_ABS32            00001398   __dso_handle

		// void init(Plugin *p) {
		//  290:	e92d4010 	push	{r4, lr}
		//  294:	e59f3020 	ldr	r3, [pc, #32]	@ 2bc <init(Plugin*)+0x2c> -->
		//  298:	e08f3003 	add	r3, pc, r3
		// 	pluginInstance = p;
		//  29c:	e59f201c 	ldr	r2, [pc, #28]	@ 2c0 <init(Plugin*)+0x30>
		//  2a0:	e7932002 	ldr	r2, [r3, r2]
		//  2a4:	e5820000 	str	r0, [r2]
		// ...
		// 2bc:	000010dc 	ldrdeq	r1, [r0], -ip
		// 2c0:	00000018 	andeq	r0, r0, r8, lsl r0
		// 2c4:	00000014 	andeq	r0, r0, r4, lsl r0

		// pluginInstance is @13a0

		// 000013a0 <pluginInstance>:
		// Plugin *pluginInstance;
		//     13a0:	00000000 	andeq	r0, r0, r0

		// run init_array: .dynamic section has types INIT_ARRAY and INIT_ARRAYSZ
		// .init_array section
		// [ 9] .init_array       INIT_ARRAY      000012d8 0002d8 000004 04  WA  0   0  4
		// So we could find that section, load sz/4 values from its address (0x12d8 + block start)
		// then execute each one (entry is 0x0000025c, which is address offset of createModel call)

		// handle PLT?
		// handle GOT?
		// handle REL?

		find_init_plugin_function();

		if (init_func) {
			__BKPT();
			init_func(&plugin);
		}

		while (true) {
			__NOP();
		}
	}

	GCC_OPTIMIZE_OFF
	void load_executable() {

		uint32_t lowest_addr = 0xFFFFFFFF;
		uint32_t highest_addr = 0;
		for (auto &seg : elf.segments) {
			if (seg.is_loadable()) {
				lowest_addr = std::min(seg.address(), lowest_addr);
				highest_addr = std::max(seg.address() + seg.mem_size(), highest_addr);
			}
		}
		size_t load_size = highest_addr - lowest_addr + 1;

		pr_info("Allocating %zu bytes for loading\n", load_size);
		block.code.resize(load_size);

		for (auto &seg : elf.segments) {
			if (seg.is_loadable()) {
				std::ranges::copy(seg, std::next(block.code.begin(), seg.address()));

				pr_info("Loading segment with file offset 0x%x to %p\n",
						seg.offset(),
						std::next(block.code.begin(), seg.address()));
			}
		}
	}

	GCC_OPTIMIZE_OFF
	void process_relocs() {
	}

	GCC_OPTIMIZE_OFF
	void find_init_plugin_function() {
		auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initP6Plugin");

		if (init_plugin_symbol) {
			auto load_address = init_plugin_symbol->offset() - block.elf_offset + block.code.data();
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
