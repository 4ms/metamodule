#pragma once

#include <span>
#include <cstdint>
#include <patch_file/patch_storage.hh>

namespace MetaModule::WifiInterface
{
	void init(PatchStorage*);

	void run();

	void handle_received_frame(uint8_t, std::span<uint8_t>);
};