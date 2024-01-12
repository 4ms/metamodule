#pragma once
#include "build-simple-elf.hh"
#include "debug.hh"
#include "dynload/elf_relocator.hh"
#include "dynload/host_symbol.hh"
#include "elf_file.hh"
#include "pr_dbg.hh"
#include "stm32mp1xx.h"
#include <cstring>
#include <elf.h>
#include <span>
#include <string>
#include <vector>

#include "rack.hpp"

GCC_OPTIMIZE_OFF
plugin::Model *testHostCall(std::string_view slug) {
	printf("creating TestModule: %.*s\n", (int)slug.size(), slug.data());
	return nullptr;
}

GCC_OPTIMIZE_OFF
void testAddModel(rack::Model *model) {
	printf("calling addModel(%p)\n", model);
}

struct DynLoadTest {

	DynLoadTest()
		: elf{{testbrand_elf, testbrand_elf_len}} {
	}

	GCC_OPTIMIZE_OFF
	void test() {
		// elf.print_sec_headers();
		elf.print_prog_headers();
		load_executable();
		process_relocs();
		find_init_plugin_function();

		__BKPT();
		if (init_func) {
			init_func(&plugin);
		}

		// All below assumes code loaded to 0xd001'6e68

		// function pointers;
		// wrote &createModel to +1388 (d001'81f0) &got[3]
		// wrote &Plugin::addModel to +138C (d001'81f4) &got[4]

		// global data pointers (may be pointers to pointers!)
		// wrote +139c (d001'8204) to +1390 (d001'81f8) &got[5]. 139c is the address of modelTest (which itself is a pointer containing addr of a global... that we don't have allocated??)
		// wrote +13a0 (d001'8208) to +1394 (d001'81fc) &got[6]. 13a0 is the address of pluginInstance (which is a pointer)

		// wrote +1398 (d001'8200) to +1398 (d001'8200) (__dso_handle). Points to itself???

		// Handle .rel.dyn section:
		// R_ARM_GLOB_DAT: global data needs... a pointer?
		// Relocation section '.rel.dyn' at offset 0x200 contains 4 entries:
		//  Offset     Info    Type                Sym. Value  Symbol's Name
		// 000012d8  00000017 R_ARM_RELATIVE
		// 00001390  00000415 R_ARM_GLOB_DAT         0000139c   modelTest
		// 00001394  00000715 R_ARM_GLOB_DAT         000013a0   pluginInstance
		// 00001398  00000502 R_ARM_ABS32            00001398   __dso_handle

		// init plugin = +290 = 70f8

		// void init(Plugin *p) {
		//  290:	e92d4010 	push	{r4, lr}
		//  294:	e59f3020 	ldr	r3, [pc, #32]	@ 2bc <init(Plugin*)+0x2c> 	--> r3 = 10dc
		//  298:	e08f3003 	add	r3, pc, r3									--> r3 = +298 + 8 + 10dc = +137c = d001'81e4 = &got
		// 	pluginInstance = p;
		//  29c:	e59f201c 	ldr	r2, [pc, #28]	@ 2c0 <init(Plugin*)+0x30>	--> r2 = 0x18
		//  2a0:	e7932002 	ldr	r2, [r3, r2]					--> r2 = *(+137c+18) = *(+1394) = *(d001'81fc) (=got[6]) = +13A0 (d001'8208)
		//  2a4:	e5820000 	str	r0, [r2] 									--> store host's Plugin* p to local pluginInstance
		//	p->addModel(modelTest);
		//  2a8:	e59f2014 	ldr	r2, [pc, #20]	@ 2c4 <init(Plugin*)+0x34> 	--> r2 = 0x14 = 20
		//  2ac:	e7933002 	ldr	r3, [r3, r2] 								--> r3 = value at got[5] = *(+138c) = +139c = d001'8204 = &modelTest
		//  2b0:	e5931000 	ldr	r1, [r3] 									--> r1 = value at +139c (modelTest)
		//  2b4:	ebffffe5 	bl	250 <Plugin::addModel(Model*)@plt> 			--> call addModel(r0 = p, r1 = modelTest)
		//  2b8:	e8bd8010 	pop	{r4, pc}
		//  2bc:	000010dc 	ldrdeq	r1, [r0], -ip
		//  2c0:	00000018 	andeq	r0, r0, r8, lsl r0
		//  2c4:	00000014 	andeq	r0, r0, r4, lsl r0

		// 00000250 <Plugin::addModel(Model*)@plt>:
		//  250:	e28fc600 	add	ip, pc, #0, 12								--> ip(r12) = +258
		//  254:	e28cca01 	add	ip, ip, #4096	@ 0x1000 					--> r12 = +1258
		//  258:	e5bcf134 	ldr	pc, [ip, #308]!	@ 0x134						--> jump to *(+138c) = *(d001'81f4) = &addModel (c203'a320)
		// 																			params are the same (p, modelTest)

		// Model *modelTest = createModel<TestModule, TestWidget>("TestModuleSlug");
		//  25c:	e92d4010 	push	{r4, lr}
		//  260:	e59f401c 	ldr	r4, [pc, #28]	@ 284 <_GLOBAL__sub_I_test_module.cpp+0x28>	--> r4 = 0x1100
		//  264:	e08f4004 	add	r4, pc, r4													--> r4 = +137c (d001'81e4) = &got
		//  268:	e59f0018 	ldr	r0, [pc, #24]	@ 288 <_GLOBAL__sub_I_test_module.cpp+0x2c>
		//  26c:	e08f0000 	add	r0, pc, r0
		//  270:	ebfffff3 	bl	244 <Model* createModel<TestModule, TestWidget>(char const*)@plt>
		//  274:	e59f3010 	ldr	r3, [pc, #16]	@ 28c <_GLOBAL__sub_I_test_module.cpp+0x30>
		//  278:	e7943003 	ldr	r3, [r4, r3]
		//  27c:	e5830000 	str	r0, [r3]
		//  280:	e8bd8010 	pop	{r4, pc}
		//  284:	00001110 	andeq	r1, r0, r0, lsl r1
		//  288:	00000054 	andeq	r0, r0, r4, asr r0
		//  28c:	00000014 	andeq	r0, r0, r4, lsl r0

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
		auto addmodel_addr = reinterpret_cast<uint32_t>(&testAddModel);
		auto createmodel_addr = reinterpret_cast<uint32_t>(&testHostCall);
		std::array<ElfFile::HostSymbol, 2> hostsyms{{
			{"_ZN6Plugin8addModelEP5Model", 0, addmodel_addr},
			{"_Z11createModelI10TestModule10TestWidgetEP5ModelPKc", 0, createmodel_addr},
		}};
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
