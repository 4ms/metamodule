#include "doctest.h"
#include "dynload/build-simple-elf.hh"
#include "dynload/elf_file.hh"
#include "dynload/elf_relocator.hh"

TEST_CASE("Relocations") {
	ElfFile::Elf elf{{testbrand_elf, testbrand_elf_len}};
	elf.print_sec_headers();
	elf.print_prog_headers();

	auto load_size = elf.load_size();
	CHECK(load_size == 5029);

	pr_info("Allocating %zu bytes for loading\n", load_size);
	std::vector<uint8_t> code(load_size);

	for (auto &seg : elf.segments) {
		if (seg.is_loadable()) {
			std::ranges::copy(seg, std::next(code.begin(), seg.address()));

			pr_info(
				"Loading segment with file offset 0x%x to %p\n", seg.offset(), std::next(code.begin(), seg.address()));
		}
	}

	//

	auto init_plugin_symbol = elf.find_dyn_symbol("_Z4initP6Plugin");

	struct Plugin {};
	using InitPluginFunc = void(Plugin *);
	InitPluginFunc *init_func{};
	if (init_plugin_symbol) {
		auto load_address = init_plugin_symbol->offset() + code.data();
		init_func = reinterpret_cast<InitPluginFunc *>(load_address);

	} else
		pr_err("Did not find init(Plugin*)\n");

	printf("init_func is at %p (+%x)\n", init_func, (uint8_t *)init_func - (uint8_t *)code.data());
	auto initfunc_mem = std::span<uint32_t>{(uint32_t *)init_func, 16};
	for (unsigned i = 0; auto byte : initfunc_mem) {
		printf("%08x ", byte);
		if (++i % 4 == 0)
			printf("\n");
	}

	/////
	std::array<ElfFile::HostSymbol, 2> hostsyms{{
		{"_ZN6Plugin8addModelEP5Model", 0, 0xAA1234},
		{"_Z11createModelI10TestModule10TestWidgetEP5ModelPKc", 0, 0x55443322},
	}};
	ElfFile::Relocater relocator{code.data(), hostsyms};

	for (auto reloc : elf.relocs) {
		relocator.write(reloc);
	}
}
