#include "wifi_interface.hh"

#include <flatbuffers/flatbuffers.h>
#include <all_generated.h>

#include "flasher/flasher.h"
#include "comm/BufferedUSART2.h"
#include "comm/framing/Configuration.h"
#include "comm/framing/StaticDeframer.h"
#include "comm/framing/Framer.h"
using namespace Framing;

#include <stm32mp1xx_hal.h>

#include "core_intercom/shared_memory.hh"

#include <console/pr_dbg.hh>

extern unsigned int _binary_firmware_bin_start;
extern unsigned int _binary_firmware_bin_end;
extern unsigned int _binary_littlefs_img_start;
extern unsigned int _binary_littlefs_img_end;


namespace MetaModule
{

PatchStorage* WifiInterface::patchStorage;

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
        std::vector<flatbuffers::Offset<PatchInfo>> elems(fileList.size());
        for (std::size_t i=0; i<fileList.size(); i++)
        {
            auto thisName = fbb.CreateString(std::string_view(fileList[i].patchname));

            auto thisFilename = fbb.CreateString(std::string_view(fileList[i].filename));
            auto thisInfo = CreatePatchInfo(fbb, thisName, thisFilename);
            elems[i] = thisInfo;
        };
        return fbb.CreateVector(elems);
    };

    auto usbList = CreateVector(SharedMemoryS::ptrs.patch_file_list->usb);
    auto flashList = CreateVector(SharedMemoryS::ptrs.patch_file_list->norflash);
    auto sdcardList = CreateVector(SharedMemoryS::ptrs.patch_file_list->sdcard);

    auto patches = CreatePatches(fbb, usbList, flashList, sdcardList);
    auto message = CreateMessage(fbb, AnyMessage_Patches, patches.Union());

    return message;
}

void sendBroadcast(std::span<uint8_t> payload)
{
    framer.sendStart(BufferedUSART2::transmit);
    framer.sendPayload(0, BufferedUSART2::transmit);
    for (auto p : payload)
    {
        framer.sendPayload(p, BufferedUSART2::transmit);
    }
    framer.sendStop(BufferedUSART2::transmit);
}


void WifiInterface::init(PatchStorage* storage)
{
    printf("Initializing Wifi\n");

    checkForUpdate();

    patchStorage = storage;

    BufferedUSART2::init();
}

void WifiInterface::checkForUpdate()
{
    auto result = Flasher::init(230400);

    if (result == ESP_LOADER_SUCCESS)
    {
        printf("Bootloader ready\n");

        const uint32_t FirmwareStartAddress = 0x0;
        std::span<const uint8_t> Firmware ((uint8_t*)&_binary_firmware_bin_start, std::size_t((uint8_t*)&_binary_firmware_bin_end - (uint8_t*)&_binary_firmware_bin_start));
        const auto FirmwareChecksum = firmware_MD5;

        const uint32_t FilesystemStartAddress = 0x200000;
        std::span<const uint8_t> Filesystem ((uint8_t*)&_binary_littlefs_img_start, std::size_t((uint8_t*)&_binary_littlefs_img_end - (uint8_t*)&_binary_littlefs_img_start));
        const auto FileystemChecksum = littlefs_MD5;

        printf("Firmware image at   %p-%p\n", &_binary_firmware_bin_start, &_binary_firmware_bin_end);
        printf("Filesystem image at %p-%p\n", &_binary_littlefs_img_start, &_binary_littlefs_img_end);

        result = Flasher::verify(FirmwareStartAddress, Firmware.size(), FirmwareChecksum);

        if (result == ESP_LOADER_SUCCESS)
        {
            printf("Firmware binary already matches\n");
            return;
        }
        else if (result == ESP_LOADER_ERROR_INVALID_MD5)
        {
            result = Flasher::flash(FirmwareStartAddress, Firmware);

            if (result == ESP_LOADER_SUCCESS)
            {
                printf("Firmware flashed\n");
            }
            else
            {
                printf("Flashing failed with %u\n", result);
            }
        }
        else
        {
            printf("Cannot get md5\n");
        }

    }
}



void WifiInterface::send_frame(std::span<uint8_t> payload)
{
    framer.send(payload, BufferedUSART2::transmit);
}

void WifiInterface::run()
{
    if (auto val = BufferedUSART2::receive(); val)
    {
        deframer.parse(*val, handle_received_frame);
    }
}

void WifiInterface::handle_received_frame(std::span<uint8_t> frame)
{
    auto destination = frame[0];
    auto payload = frame.subspan(1, frame.size()-1);

    auto sendResponse = [destination](auto payload)
    {
        framer.sendStart(BufferedUSART2::transmit);
        framer.sendPayload(destination, BufferedUSART2::transmit);
        for (auto p : payload)
        {
            framer.sendPayload(p, BufferedUSART2::transmit);
        }
        framer.sendStop(BufferedUSART2::transmit);
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
                auto success = patchStorage->add_patch_file(*thisVolume, filename, receivedPatchData);

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
