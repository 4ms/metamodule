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



#include <console/pr_dbg.hh>


namespace MetaModule
{

Configuration_t FrameConfig
{
    .start=0x01,
    .end=0x02,
    .escape=0x03
};

StaticDeframer<100> deframer(FrameConfig);
Framer framer(FrameConfig);


void WifiInterface::init()
{
    printf_("Initializing Wifi\n");

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
    printf("Frame\n");

    auto message = GetMessage(frame.data());

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

                send_frame(fbb.GetBufferSpan());
            }
            else
            {
                printf_("Unexpected detection\n");
            }
        }
        else if (auto switchMessage = message->content_as_Switch(); switchMessage)
        {
            printf_("State: %u\n", switchMessage->state());

            // Just echo back raw
            send_frame(frame);
        }
        else if (auto patchNameMessage = message->content_as_PatchNames(); patchNameMessage)
        {
                // Answer presence detection
                flatbuffers::FlatBufferBuilder fbb;
                auto str1 = fbb.CreateString("First Name");
                auto str2 = fbb.CreateString("Second Name");
                auto names = fbb.CreateVector({str1, str2});
                auto patchNames = CreatePatchNames(fbb, false, names);
                auto message = CreateMessage(fbb, AnyMessage_PatchNames, patchNames.Union());
                fbb.Finish(message);

                send_frame(fbb.GetBufferSpan());
        }
        else
        {
            printf_("Other option\n");
        }
    }
    else
    {
        printf_("Invalid message\n");
    }
}



} // namespace MetaModule
