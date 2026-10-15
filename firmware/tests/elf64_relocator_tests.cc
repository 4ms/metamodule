// Tests the ELF64/AArch64 plugin relocation path (the STM32MP2 "pro" target
// loads AArch64 plugins; MP1 loads ELF32/ARM with REL-style relocations).
//
// Fixture: tests/assets/test_plugin_aarch64.so, a real aarch64 shared object
// (source and build command in tests/assets/test_plugin_aarch64.cc). We can't
// execute its code on the test host -- these tests verify that relocations are
// *written* correctly: R_AARCH64_ABS64/GLOB_DAT to symbols defined in the
// plugin, GLOB_DAT/JUMP_SLOT resolved against the host symbol table, and
// RELATIVE entries (e.g. .init_array) becoming absolute in-image addresses.
//
// This TU selects the ELF64 class locally; no other test TU may include the
// ElfFile headers (the class is a per-build choice, so mixing both classes in
// one binary would violate the ODR).
#define METAMODULE_ELF64

#include "dynload/elf_process/elf_file.hh"
#include "dynload/elf_process/elf_relocator.hh"
#include "doctest.h"
#include <cstring>
#include <fstream>
#include <vector>

using namespace ElfFile;

namespace
{

struct LoadedTestPlugin {
	std::vector<uint8_t> filedata;
	Elf elf;
	std::vector<uint8_t> codeblock;
	uintptr_t base;

	static constexpr uintptr_t HostFuncAddr = 0x1122334455667788ULL;
	static constexpr uintptr_t HostDataAddr = 0x99AABBCCDDEEFF00ULL;

	LoadedTestPlugin()
		: filedata{read_file()}
		, elf{filedata}
		, codeblock(elf.load_size())
		, base{reinterpret_cast<uintptr_t>(codeblock.data())} {

		// Load loadable segments the same way DynLoader::load_executable does
		for (auto &seg : elf.segments)
			if (seg.is_loadable())
				std::copy(seg.begin(), seg.end(), codeblock.begin() + seg.address());
	}

	static std::vector<uint8_t> read_file() {
		std::ifstream f("tests/assets/test_plugin_aarch64.so", std::ios::binary);
		return {std::istreambuf_iterator<char>(f), {}};
	}

	bool relocate() {
		std::vector<HostSymbol> hostsyms = {
			{"host_provided_func", 0, HostFuncAddr},
			{"host_provided_data", 0, HostDataAddr},
		};
		Relocater relocator{codeblock.data(), hostsyms};
		for (auto reloc : elf.relocs)
			if (!relocator.write(reloc))
				return false;
		return true;
	}

	uint64_t read_u64_at_vaddr(uint64_t vaddr) {
		uint64_t v;
		std::memcpy(&v, codeblock.data() + vaddr, 8);
		return v;
	}
};

} // namespace

TEST_CASE("ELF64: parse an aarch64 shared object") {
	LoadedTestPlugin plugin;

	REQUIRE(plugin.filedata.size() > 0);
	CHECK(plugin.elf.segments.size() > 0);
	CHECK(plugin.elf.sections.size() > 0);
	// .rela.dyn + .rela.plt entries (see readelf -r on the fixture)
	CHECK(plugin.elf.relocs.size() == 9);

	CHECK(plugin.elf.find_dyn_symbol("local_func").has_value());
	CHECK(plugin.elf.find_dyn_symbol("use_host").has_value());
	CHECK_FALSE(plugin.elf.find_dyn_symbol("does_not_exist").has_value());
}

TEST_CASE("ELF64: relocations write the correct values") {
	LoadedTestPlugin plugin;
	REQUIRE(plugin.relocate());

	SUBCASE("ABS64 to plugin-defined symbols: slots hold base + symbol vaddr") {
		auto local_func = plugin.elf.find_dyn_symbol("local_func");
		auto ptr_to_func = plugin.elf.find_dyn_symbol("ptr_to_func");
		REQUIRE(local_func.has_value());
		REQUIRE(ptr_to_func.has_value());
		CHECK(plugin.read_u64_at_vaddr(ptr_to_func->offset()) == plugin.base + local_func->offset());

		auto local_value = plugin.elf.find_dyn_symbol("local_value");
		auto ptr_to_local = plugin.elf.find_dyn_symbol("ptr_to_local");
		REQUIRE(local_value.has_value());
		REQUIRE(ptr_to_local.has_value());
		CHECK(plugin.read_u64_at_vaddr(ptr_to_local->offset()) == plugin.base + local_value->offset());
	}

	SUBCASE("GLOB_DAT/JUMP_SLOT to undefined symbols resolve via the host symbol table") {
		bool checked_host_data = false;
		bool checked_host_func = false;

		for (auto reloc : plugin.elf.relocs) {
			if (reloc.symbol_name() == "host_provided_data") {
				CHECK(plugin.read_u64_at_vaddr(reloc.reloc_offset()) == LoadedTestPlugin::HostDataAddr);
				checked_host_data = true;
			}
			if (reloc.symbol_name() == "host_provided_func") {
				CHECK(plugin.read_u64_at_vaddr(reloc.reloc_offset()) == LoadedTestPlugin::HostFuncAddr);
				checked_host_func = true;
			}
		}
		CHECK(checked_host_data);
		CHECK(checked_host_func);
	}

	SUBCASE(".init_array entries become absolute in-image addresses (RELATIVE)") {
		auto initarr = plugin.elf.find_section(".init_array");
		REQUIRE(initarr.has_value());
		REQUIRE(initarr->num_entries() == 1);

		// Unlike ELF32/REL, the relocated image (not the file image) holds the
		// entries, already absolute: base + addend of the RELATIVE reloc.
		auto reloc_entry = plugin.read_u64_at_vaddr(initarr->address());

		bool found_initarray_reloc = false;
		for (auto reloc : plugin.elf.relocs) {
			if (reloc.reloc_offset() == initarr->address()) {
				CHECK(reloc.reloc_type() == R_AARCH64_RELATIVE);
				CHECK(reloc_entry == plugin.base + reloc.addend());
				found_initarray_reloc = true;
			}
		}
		CHECK(found_initarray_reloc);
		CHECK(reloc_entry >= plugin.base);
		CHECK(reloc_entry < plugin.base + plugin.codeblock.size());
	}

	SUBCASE("unresolvable symbol fails cleanly") {
		LoadedTestPlugin plugin2;
		// Empty host symbol table: the undefined host_provided_* symbols can't resolve
		Relocater relocator{plugin2.codeblock.data(), std::span<const HostSymbol>{}};
		bool all_ok = true;
		for (auto reloc : plugin2.elf.relocs)
			all_ok = relocator.write(reloc) && all_ok;
		CHECK_FALSE(all_ok);
	}
}
