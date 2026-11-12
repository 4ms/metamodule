#pragma once

#include <span>
#include <cstdint>
#include <expected>
#include <params/param_block.hh>
#include <wifi/wifi_live_block.hh>
#include <patch_file/patch_storage.hh>

namespace MetaModule::WifiInterface
{
	void init(PatchStorage *, DoubleBufParamBlock *, WifiLiveBlock *);

	void run();
	void start();
	void stop();


	enum ErrorCode_t {NO_ANSWER, NO_IP};
	struct Endpoint_t
	{
		std::array<uint8_t,4> ip;
		uint16_t port;
	};

	std::expected<Endpoint_t,ErrorCode_t> getCurrentIP();
};