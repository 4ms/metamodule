#pragma once
#include "build-simple-elf.hh"
#include "debug.hh"
#include "elf_parse.hh"
#include "pr_dbg.hh"
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
		// pr_info("prog headers %08x++%x\n", prog_headers.data(), prog_headers.size_bytes());
		// pr_info("%d section headers, start at offset %x\n", section_headers.size(), elf_header->e_shoff);
		// pr_info("%d program headers, start at offset %x\n", prog_headers.size(), elf_header->e_phoff);
		elf.print_sec_headers();
		load_executable();

		while (true) {
			__NOP();
		}
	}

	GCC_OPTIMIZE_OFF
	void load_executable() {
		for (auto &sec : elf.section_headers) {
			if (elf.is_code(sec) || elf.is_rodata(sec)) {
				pr_info(
					"Section %s is code or rodata: loading to %p\n", elf.section_name(sec).data(), loaded_code.end());
				loaded_code.insert(loaded_code.end(), elf.section_start(sec), elf.section_end(sec));
			}
		}
	}

	GCC_OPTIMIZE_OFF
	void process_relocs() {
	}

	GCC_OPTIMIZE_OFF
	void find_init_address() {
	}

	ElfParser elf;
	std::vector<uint8_t> loaded_code;
};
