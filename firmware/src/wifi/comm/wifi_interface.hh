#pragma once

#include <span>
#include <cstdint>
#include <optional>
#include <patch_file/patch_storage.hh>

namespace MetaModule::WifiInterface
{
	void init(PatchStorage*);

	void run();
	void start();
	void stop();

	using IPAddress_t = std::array<uint8_t,4>;
	std::optional<IPAddress_t> getCurrentIP();
};