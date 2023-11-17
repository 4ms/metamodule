#pragma once
#include "ld.h"
#include "pr_dbg.hh"
#include "uimg_header.hh"
#include <cstring>
#include <optional>

namespace MetaModule::UimgLoader
{

struct ImageInfo {
	uint32_t load_addr = 0;
	uint32_t entry_point = 0;
	uint32_t size = 0;
};

std::optional<ImageInfo> parse_header(BootImageDef::ImageHeader *header) {
	if (!header)
		return std::nullopt;

	auto be32_to_cpu = [](uint32_t x) {
		return ((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) | ((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24);
	};

	uint32_t magic = be32_to_cpu(header->ih_magic);

	if (magic == BootImageDef::IH_MAGIC) {
		ImageInfo info{
			.load_addr = be32_to_cpu(header->ih_load),
			.entry_point = be32_to_cpu(header->ih_ep),
			.size = be32_to_cpu(header->ih_size),
		};

		pr_dbg("Found section: %.*s\n", BootImageDef::IH_NMLEN, header->ih_name);
		pr_dbg("   header magic: 0x%08x\n", magic);
		pr_dbg("     image size: 0x%08x\n", info.size);
		pr_dbg("   load address: 0x%08x\n", info.load_addr);

		return info;

	} else {
		pr_dbg("Failed to read a valid header: magic was 0x%08x", magic);
		pr_dbg(" expected 0x%08x\n", BootImageDef::IH_MAGIC);
		return std::nullopt;
	}
}

bool valid_addr(uint64_t addr) {
	// Don't allow loading A7 code, it's already loaded
	if (addr >= (A7_CODE - 0x40) && addr <= A7_CODE)
		return false;

	//RETRAM: 64K
	if (addr >= M4_VECT_A7 && addr <= (M4_VECT_A7 + M4_VECT_SZ)) {
		return true;
	}

	//SYSRAM: 384K
	if (addr >= M4_CODE_A7 && addr <= (M4_CODE_A7 + M4_CODE_SZ))
		return true;

	//DDR: must not overlap TTB
	if (addr >= TTB_END && addr <= A7_CODE_END)
		return true;

	return false;
};

void load() {
	static constexpr uint32_t header_size = sizeof(BootImageDef::ImageHeader);

	auto header_start_addr = A7_CODE - header_size;

	while (true) {

		auto *uimg_header = reinterpret_cast<BootImageDef::ImageHeader *>(header_start_addr);
		auto img = parse_header(uimg_header);

		if (img) {
			auto end_addr = img->load_addr + img->size - header_size;

			if (valid_addr(img->load_addr) && valid_addr(end_addr)) {
				uint32_t section_body_start_addr = header_start_addr + header_size;

				pr_dbg("Copying 0x%x bytes from 0x%08x to 0x%08x", img->size, section_body_start_addr, img->load_addr);
				std::memcpy((void *)img->load_addr, (const void *)section_body_start_addr, img->size);
				pr_dbg("...Done\n");

			} else {
				pr_dbg("Skipping Section with invalid load address range: 0x%08x + 0x%x\n", img->load_addr, img->size);
			}

			header_start_addr += img->size;

		} else {
			pr_dbg("No more sections found\n");
			break;
		}
	}
}

} // namespace MetaModule::UimgLoader
