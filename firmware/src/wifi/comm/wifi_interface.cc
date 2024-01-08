#include "wifi_interface.hh"

#include <flatbuffers/flatbuffers.h>
#include <all_generated.h>

#include "BufferedUSART2.h"
#include "framing/Configuration.h"
#include "framing/StaticDeframer.h"
#include "framing/Framer.h"
using namespace Framing;

#include <stm32mp1xx_hal.h>

#include <console/pr_dbg.hh>



namespace MetaModule::WifiInterface
{

PatchStorage* patchStorage;

Configuration_t FrameConfig
{
    .start=0x01,
    .end=0x02,
    .escape=0x03
};

StaticDeframer<16000> deframer(FrameConfig);
Framer framer(FrameConfig);

flatbuffers::Offset<Message> constructPatchesMessage(flatbuffers::FlatBufferBuilder& fbb)
{
    auto CreateVector = [&fbb](auto fileList)
    {
        std::vector<flatbuffers::Offset<PatchInfo>> elems(fileList.files.size());
        for (std::size_t i=0; i<fileList.files.size(); i++)
        {
            auto thisName = fbb.CreateString(std::string_view(fileList.files[i].patchname));

            auto thisFilename = fbb.CreateString(std::string_view(fileList.files[i].filename));
            auto thisInfo = CreatePatchInfo(fbb, thisName, thisFilename);
            elems[i] = thisInfo;
        };
		//TODO: add directories, and files inside directories
        return fbb.CreateVector(elems);
    };

    auto patchFileList = patchStorage->getPatchList();

    auto usbList = CreateVector(patchFileList.volume_root(Volume::USB));
    auto flashList = CreateVector(patchFileList.volume_root(Volume::NorFlash));
    auto sdcardList = CreateVector(patchFileList.volume_root(Volume::SDCard));

    auto patches = CreatePatches(fbb, usbList, flashList, sdcardList);
    auto message = CreateMessage(fbb, AnyMessage_Patches, patches.Union());

    return message;
}

///////////////////////////

void sendFrame(uint8_t channel, std::span<uint8_t> payload)
{
    uint16_t payloadLength = payload.size() + 1;

    framer.sendStart(BufferedUSART2::transmit);
    framer.sendPayload(uint8_t(payloadLength & 0xFF), BufferedUSART2::transmit);
    framer.sendPayload(uint8_t((payloadLength & 0xFF00) >> 8), BufferedUSART2::transmit);
    framer.sendPayload(channel, BufferedUSART2::transmit);

    for (auto p : payload)
    {
        framer.sendPayload(p, BufferedUSART2::transmit);
    }
    framer.sendStop(BufferedUSART2::transmit);
}

void receiveFrame(std::span<uint8_t> fullFrame)
{
    if (fullFrame.size() >= 2)
    {
        uint16_t parsedLength = fullFrame[0] | fullFrame[1] << 8;
        uint16_t actualLength = fullFrame.size() - 2;
        if (parsedLength == actualLength)
        {
            auto destination = fullFrame[2];
            auto payload = fullFrame.subspan(3, fullFrame.size()-3);
            handle_received_frame(destination, payload);
        }
        else
        {
            pr_err("Invalid length (parsed %u actual %u)", parsedLength, actualLength);
        }
    }
};

void sendBroadcast(std::span<uint8_t> payload)
{
    sendFrame(0, payload);
}

////////////////////////////////7

void init(PatchStorage* storage)
{
    printf("Initializing Wifi\n");

    patchStorage = storage;

    BufferedUSART2::init();
}


void run()
{
    if (auto val = BufferedUSART2::receive(); val)
    {
        deframer.parse(*val, receiveFrame);
    }
}

void handle_received_frame(uint8_t destination, std::span<uint8_t> payload)
{
    auto sendResponse = [destination](auto payload)
    {
        sendFrame(destination, payload);
    };

    // Parse message

    auto message = GetMessage(payload.data());

    if (auto content = message->content(); content)
    {
        if (auto presenceDetection = message->content_as_PresenceDetection(); presenceDetection)
        {
            if (presenceDetection->phase() == Phase::Phase_REQUEST)
            {
                // Answer presence detection
                flatbuffers::FlatBufferBuilder fbb;
                auto answer = fbb.CreateStruct(PresenceDetection(Phase::Phase_ANSWER));
                auto message = CreateMessage(fbb, AnyMessage_PresenceDetection, answer.Union());
                fbb.Finish(message);

                sendResponse(fbb.GetBufferSpan());
            }
            else
            {
                printf("Unexpected detection\n");
            }
        }
        else if (auto switchMessage = message->content_as_Switch(); switchMessage)
        {
            printf("State: %u\n", switchMessage->state());

            // Just echo back raw
            sendResponse(payload);
        }
        else if (auto patchNameMessage = message->content_as_Patches(); patchNameMessage)
        {
            flatbuffers::FlatBufferBuilder fbb;
            auto message = constructPatchesMessage(fbb);
            fbb.Finish(message);

            sendResponse(fbb.GetBufferSpan());
        }
        else if (auto uploadPatchMessage = message->content_as_UploadPatch(); uploadPatchMessage)
        {
            auto destination = uploadPatchMessage->destination();

            assert(uploadPatchMessage->content()->is_span_observable);
            auto receivedPatchData = std::span(uploadPatchMessage->content()->data(), uploadPatchMessage->content()->size());

            auto filename = flatbuffers::GetStringView(uploadPatchMessage->filename());

            printf("Received Patch of %u bytes for location %u\n", receivedPatchData.size(), destination);

            auto LocationToVolume = [](auto location) -> std::optional<Volume>
            {
                switch (location)
                {
                    case StorageLocation::StorageLocation_USB:    return Volume::USB;
                    case StorageLocation::StorageLocation_FLASH:  return Volume::NorFlash;
                    case StorageLocation::StorageLocation_SDCARD: return Volume::SDCard;
                    default:                                      return std::nullopt;
                }
            };

            flatbuffers::FlatBufferBuilder fbb;
            bool filesUpdated = false;

            if (auto thisVolume = LocationToVolume(destination); thisVolume)
            {
                auto success = patchStorage->write_patch_file(*thisVolume, filename, receivedPatchData);

                if (success)
                {
                    auto result = CreateResult(fbb, true);
                    auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
                    fbb.Finish(message);

                    filesUpdated = true;
                }
                else
                {
                    auto description = fbb.CreateString("Saving failed");
                    auto result = CreateResult(fbb, false, description);
                    auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
                    fbb.Finish(message);
                }
            }
            else
            {
                auto description = fbb.CreateString("Invalid volume id");
                auto result = CreateResult(fbb, false, description);
                auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
                fbb.Finish(message);
            }

            sendResponse(fbb.GetBufferSpan());

            if (filesUpdated)
            {
                flatbuffers::FlatBufferBuilder fbb;
                auto message = constructPatchesMessage(fbb);
                fbb.Finish(message);

                sendBroadcast(fbb.GetBufferSpan());
            }
        }
        else
        {
            printf("Other option\n");
        }
    }
    else
    {
        printf("Invalid message\n");
    }

}



} // namespace MetaModule
