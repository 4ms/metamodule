#pragma once
#include "build-simple-elf.hh"
#include "debug.hh"
#include "elf_file.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <cstring>
#include <elf.h>
#include <span>
#include <string>
#include <vector>

#include "rack.hpp"

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

		// code loaded to 0xd001'6e68
		// init plugin = +290 = 70f8

		// void init(Plugin *p) {
		//  290:	e92d4010 	push	{r4, lr}
		//  294:	e59f3020 	ldr	r3, [pc, #32]	@ 2bc <init(Plugin*)+0x2c> 	--> r3 = 10dc
		//  298:	e08f3003 	add	r3, pc, r3									--> r3 = +298 + 8 + 10dc = +137c = d001'81e4
		// 	pluginInstance = p;
		//  29c:	e59f201c 	ldr	r2, [pc, #28]	@ 2c0 <init(Plugin*)+0x30>	--> r2 = 18
		//  2a0:	e7932002 	ldr	r2, [r3, r2]								--> r2 = *(+137c+18) = *(+1394) = *(d001'81fc) (=got[6])
		//	p->addModel(modelTest);
		//  2a4:	e5820000 	str	r0, [r2]
		//  2a8:	e59f2014 	ldr	r2, [pc, #20]	@ 2c4 <init(Plugin*)+0x34>
		//  2ac:	e7933002 	ldr	r3, [r3, r2]
		//  2b0:	e5931000 	ldr	r1, [r3]
		//  2b4:	ebffffe5 	bl	250 <Plugin::addModel(Model*)@plt>
		//  2b8:	e8bd8010 	pop	{r4, pc}
		//  2bc:	000010dc 	ldrdeq	r1, [r0], -ip
		//  2c0:	00000018 	andeq	r0, r0, r8, lsl r0
		//  2c4:	00000014 	andeq	r0, r0, r4, lsl r0

		// pluginInstance is @13a0,
		// so we should write 13a0 to got[6] (which is +1394)
		// -> to do this, we would traverse .rel.dyn and write Value+Offset to +Offset
		// that is, write 0xd001'8208 to address 0xd001'81fc (+13a0 to address +1394)

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
		size_t load_size = elf.load_size();

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
	void process_got() {
		auto got_section = elf.find_section(".got");
		if (!got_section) {
			pr_err("No .got section\n");
			return;
		}
		std::span<uint32_t> got{(uint32_t *)got_section->begin(), (uint32_t *)got_section->end()};
		//now we can write to got like got[3] = ...
		// but we don't know the index so... :(
	}

	void process_relocs() {
		for (auto reloc : elf.relocs) {
			reloc.write(block.code.data());
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
