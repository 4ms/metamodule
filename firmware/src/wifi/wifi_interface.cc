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


namespace MetaModule
{

Configuration_t FrameConfig
{
    .start=0x01,
    .end=0x02,
    .escape=0x03
};

StaticDeframer<16000> deframer(FrameConfig);
Framer framer(FrameConfig);


void WifiInterface::init()
{
    printf("Initializing Wifi\n");

    // auto result = Flasher::init(230400);

    BufferedUSART2::init();
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
        else if (auto patchNameMessage = message->content_as_PatchNames(); patchNameMessage)
        {
            // take a copy of the current file list
            auto fileList = SharedMemoryS::ptrs.patch_file_list->norflash;

            flatbuffers::FlatBufferBuilder fbb;

            std::vector<flatbuffers::Offset<flatbuffers::String>> elems(fileList.size());
            for (std::size_t i=0; i<fileList.size(); i++)
            {
                auto str = fbb.CreateString(std::string_view(fileList[i].patchname));
                elems[i] = str;
            };
            auto names = fbb.CreateVector(elems);

            auto patchNames = CreatePatchNames(fbb, names);
            auto message = CreateMessage(fbb, AnyMessage_PatchNames, patchNames.Union());
            fbb.Finish(message);

            sendResponse(fbb.GetBufferSpan());
        }
        else if (auto uploadPatchMessage = message->content_as_UploadPatch(); uploadPatchMessage)
        {
            assert(uploadPatchMessage->content()->is_span_observable);

            auto receivedPatchData = std::span(uploadPatchMessage->content()->data(), uploadPatchMessage->content()->size());

            printf("Received Patch of %u bytes\n", receivedPatchData.size());

            flatbuffers::FlatBufferBuilder fbb;
            auto result = CreateResult(fbb, true);
            auto message = CreateMessage(fbb, AnyMessage_Result, result.Union());
            fbb.Finish(message);

            sendResponse(fbb.GetBufferSpan());
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
