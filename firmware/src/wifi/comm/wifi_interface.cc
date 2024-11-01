#include "wifi_interface.hh"

#include <all_generated.h>
#include <flatbuffers/flatbuffers.h>

#include "BufferedUSART2.h"
#include "framing/Configuration.h"
#include "framing/Framer.h"
#include "framing/StaticDeframer.h"
using namespace Framing;

#include <stm32mp1xx_hal.h>

#include <console/pr_dbg.hh>

namespace MetaModule::WifiInterface
{

/////////////////////////

PatchStorage *patchStorage;

flatbuffers::Offset<Message> constructPatchesMessage(flatbuffers::FlatBufferBuilder &fbb) {

	auto ExtractFileInfo = [&fbb](auto& thisFile)
	{
		auto thisName = fbb.CreateString(std::string_view(thisFile.patchname));
		auto thisFilename = fbb.CreateString(std::string_view(thisFile.filename));

		return CreatePatchInfo(fbb, thisName, thisFilename, thisFile.filesize, thisFile.timestamp);
	};

	auto ExtractFileFromDir = [&fbb, &ExtractFileInfo](const auto& fileList)
	{
		std::vector<flatbuffers::Offset<PatchInfo>> fileInfos(fileList.files.size());
		for (std::size_t i = 0; i < fileList.files.size(); i++) {
			fileInfos[i] = ExtractFileInfo(fileList.files[i]);
		};
		auto files = fbb.CreateVector(fileInfos);

		return files;
	};

	auto ExtractDirFull = [&fbb, &ExtractFileFromDir](const auto& fileList, std::string_view overrideName, bool isMounted)
	{
		auto FixDirName = [](std::string_view in)
		{
			// remove extra leading slash
			return in.substr(1);
		};

		std::vector<flatbuffers::Offset<DirInfo>> dirInfos(fileList.dirs.size());
		for (std::size_t i=0; i<fileList.dirs.size(); i++)
		{
			auto files = ExtractFileFromDir(fileList.dirs[i]);
			auto name = fbb.CreateString(FixDirName(std::string_view(fileList.dirs[i].name)));

			dirInfos[i] = CreateDirInfo(fbb, name, 0, files);
		}
		auto dirs = fbb.CreateVector(dirInfos);

		auto files = ExtractFileFromDir(fileList);
		
		auto name = isMounted 
			? fbb.CreateString(std::string_view(overrideName)) 
			: fbb.CreateString("(not mounted)");

		return CreateDirInfo(fbb, name, dirs, files);
	};


	auto patchFileList = patchStorage->getPatchList();

	auto usbList    = ExtractDirFull(patchFileList.volume_root(Volume::USB), patchFileList.get_vol_name(Volume::USB), patchFileList.is_mounted(Volume::USB));
	auto flashList  = ExtractDirFull(patchFileList.volume_root(Volume::NorFlash), patchFileList.get_vol_name(Volume::NorFlash), patchFileList.is_mounted(Volume::NorFlash));
	auto sdcardList = ExtractDirFull(patchFileList.volume_root(Volume::SDCard), patchFileList.get_vol_name(Volume::SDCard), patchFileList.is_mounted(Volume::SDCard));

	auto patches = CreatePatches(fbb, usbList, flashList, sdcardList);
	auto message = CreateMessage(fbb, AnyMessage_Patches, patches.Union());

	return message;
}

/////////////////////////

Configuration_t FrameConfig{.start = 0x01, .end = 0x02, .escape = 0x03};

__attribute__((section(".wifi"))) std::array<uint8_t,8*1024*1024> ReceiveBuffer;

StaticDeframer deframer(FrameConfig, std::span(ReceiveBuffer));
Framer framer(FrameConfig);

using Timestamp_t = uint32_t;

std::optional<Timestamp_t> lastHeartbeatSentTime;
static constexpr Timestamp_t HeartbeatInterval = 1000;

std::optional<Timestamp_t> lastPatchListSentTime;
static constexpr Timestamp_t PatchListInterval = 1000;

enum ChannelID_t : uint8_t {Broadcast = 0, Management = 1, Connections = 2};

std::optional<Timestamp_t> lastIPAnswerTime;
static constexpr Timestamp_t IPRequestTimeout = 1000;
std::expected<Endpoint_t,ErrorCode_t> currentEndpoint = std::unexpected(ErrorCode_t::NO_ANSWER);

void handle_management_channel(std::span<uint8_t>);
void handle_client_channel(uint8_t, std::span<uint8_t>);

///////////////////////////

void sendFrame(uint8_t channel, std::span<uint8_t> payload) {
	uint16_t payloadLength = payload.size() + 1;

	framer.sendStart(BufferedUSART2::transmit);
	framer.sendPayload(uint8_t(payloadLength & 0xFF), BufferedUSART2::transmit);
	framer.sendPayload(uint8_t((payloadLength & 0xFF00) >> 8), BufferedUSART2::transmit);
	framer.sendPayload(channel, BufferedUSART2::transmit);

	for (auto p : payload) {
		framer.sendPayload(p, BufferedUSART2::transmit);
	}
	framer.sendStop(BufferedUSART2::transmit);
}

void receiveFrame(std::span<uint8_t> fullFrame) {
	if (fullFrame.size() >= 2) {
		uint16_t parsedLength = fullFrame[0] | fullFrame[1] << 8;
		uint16_t actualLength = fullFrame.size() - 2;
		if (parsedLength == actualLength) {
			auto destination = fullFrame[2];
			auto payload = fullFrame.subspan(3, fullFrame.size() - 3);

			if (destination == ChannelID_t::Management)
			{
				handle_management_channel(payload);
			}
			else
			{
				handle_client_channel(destination, payload);
			}

		} else {
			pr_err("Invalid length (parsed %u actual %u)", parsedLength, actualLength);
		}
	}
};

///////////////////////////

Timestamp_t getTimestamp()
{
	return HAL_GetTick();
}


void requestIP()
{
	// For now, every request on the management channel is responded the IP
	std::array<uint8_t,3> payload{0xA, 0xB, 0xC};
	sendFrame(ChannelID_t::Management, std::span(payload));

	if (auto now = getTimestamp(); !lastIPAnswerTime or (now - *lastIPAnswerTime) > IPRequestTimeout)
	{
		 currentEndpoint = std::unexpected(ErrorCode_t::NO_ANSWER);
	}
}

void send_heartbeat()
{
	flatbuffers::FlatBufferBuilder fbb;
	auto answer = fbb.CreateStruct(Heartbeat());
	auto message = CreateMessage(fbb, AnyMessage_Heartbeat, answer.Union());
	fbb.Finish(message);

	sendFrame(ChannelID_t::Broadcast, fbb.GetBufferSpan());
}

////////////////////////////////

void init(PatchStorage *storage) {
	pr_info("Initializing Wifi\n");

	patchStorage = storage;
}

void start() {
	pr_trace("Wifi: Starting RX\n");
	BufferedUSART2::init();
}

void stop() {
	pr_trace("Wifi: Stopping RX\n");
	BufferedUSART2::deinit();
}

void run() {

	if (BufferedUSART2::detectedOverrunSinceLastCall())
	{
		deframer.reset();
	}

	if (auto val = BufferedUSART2::receive(); val) {
		deframer.parse(*val, receiveFrame);
	}

	if (not lastHeartbeatSentTime or (getTimestamp() - *lastHeartbeatSentTime) > HeartbeatInterval)
	{
		send_heartbeat();
		lastHeartbeatSentTime = getTimestamp();

		requestIP();
	}

	if (not lastPatchListSentTime or (getTimestamp() - *lastPatchListSentTime) > PatchListInterval)
	{
		if (patchStorage->has_media_changed() and not deframer.isReceivingFrame())
		{
			flatbuffers::FlatBufferBuilder fbb;
			auto message = constructPatchesMessage(fbb);
			fbb.Finish(message);

			sendFrame(ChannelID_t::Broadcast, fbb.GetBufferSpan());
		}

		lastPatchListSentTime = getTimestamp();
	}
}

std::expected<Endpoint_t,ErrorCode_t> getCurrentIP()
{
	return currentEndpoint;
}

////////////////////////////////

void handle_management_channel(std::span<uint8_t> payload)
{
	if (payload.size() == 6)
	{
		// assemble endpoint struct
		Endpoint_t thisEndpoint;
		std::copy(payload.begin(), payload.begin() + 4, thisEndpoint.ip.data());
		thisEndpoint.port = (payload[5] << 8) | payload[4];

		const Endpoint_t DummyEndpoint {{0,0,0,0}, 0};

		if (std::equal(DummyEndpoint.ip.begin(), DummyEndpoint.ip.end(), thisEndpoint.ip.begin()))
		{
			currentEndpoint = std::unexpected(ErrorCode_t::NO_IP);
		}
		else
		{
			currentEndpoint = thisEndpoint;
		}

		lastIPAnswerTime = getTimestamp();
	}
}



void handle_client_channel(uint8_t destination, std::span<uint8_t> payload) {

	auto sendResponse = [destination](auto payload) {
		sendFrame(destination, payload);
	};

	auto sendBroadcast = [](auto payload) {
		sendFrame(ChannelID_t::Broadcast, payload);
	};

	// Parse message

	auto message = GetMessage(payload.data());

	if (auto content = message->content(); content) {
		if (auto patchNameMessage = message->content_as_Patches(); patchNameMessage) {
			flatbuffers::FlatBufferBuilder fbb;
			auto message = constructPatchesMessage(fbb);
			fbb.Finish(message);

			sendResponse(fbb.GetBufferSpan());
		} else if (auto uploadPatchMessage = message->content_as_UploadPatch(); uploadPatchMessage) {

			assert(uploadPatchMessage->content()->is_span_observable);
			auto receivedPatchData =
				std::span(uploadPatchMessage->content()->data(), uploadPatchMessage->content()->size());

			auto filename = flatbuffers::GetStringView(uploadPatchMessage->filename());

			pr_info("Received Patch %.*s of %u bytes\n", filename.size(), filename.data(), receivedPatchData.size());

			auto ParseStorageString = [](std::string_view locationName) -> std::optional<Volume> {

				if (locationName.compare(PatchDirList::get_vol_name(Volume::USB)) == 0)
				{
					return Volume::USB;
				}
				else if (locationName.compare(PatchDirList::get_vol_name(Volume::NorFlash)) == 0)
				{
					return Volume::NorFlash;
				}
				else if (locationName.compare(PatchDirList::get_vol_name(Volume::SDCard)) == 0)
				{
					return Volume::SDCard;
				}
				else
				{
					return std::nullopt;
				}
			};

			flatbuffers::FlatBufferBuilder fbb;

			auto volumeString = flatbuffers::GetStringView(uploadPatchMessage->volume());

			if (auto thisVolume = ParseStorageString(volumeString); thisVolume) {
				auto success = patchStorage->write_file(*thisVolume, filename, receivedPatchData);

				if (success) {
					auto result = CreateResult(fbb, true);
					auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
					fbb.Finish(message);

				} else {
					auto description = fbb.CreateString("Saving failed");
					auto result = CreateResult(fbb, false, description);
					auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
					fbb.Finish(message);
				}
			} else {
				auto description = fbb.CreateString("Invalid volume id");
				auto result = CreateResult(fbb, false, description);
				auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
				fbb.Finish(message);
			}

			if (patchStorage->has_media_changed())
			{
				flatbuffers::FlatBufferBuilder fbb;
				auto message = constructPatchesMessage(fbb);
				fbb.Finish(message);

				sendBroadcast(fbb.GetBufferSpan());

				lastPatchListSentTime = getTimestamp();
			}

			sendResponse(fbb.GetBufferSpan());


		} else {
			pr_trace("Other option\n");
		}
	} else {
		pr_err("Invalid message\n");
	}
}

} // namespace MetaModule::WifiInterface
