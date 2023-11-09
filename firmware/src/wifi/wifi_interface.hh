#pragma once

#include <span>
#include <cstdint>
#include <patch_file/patch_storage.hh>

namespace MetaModule
{

struct WifiInterface {
	static void init(PatchStorage*);

	static void run();

	static void handle_received_frame(std::span<uint8_t>);
	static void send_frame(std::span<uint8_t>);

private:
	static PatchStorage* patchStorage;

};
} // namespace MetaModule
