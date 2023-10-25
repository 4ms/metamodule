#include "wifi_interface.hh"

#include <flatbuffers/flatbuffers.h>
#include <all_generated.h>

#include "flasher/flasher.h"
#include "comm/BufferedUSART2.h"
#include "comm/framing/Configuration.h"
#include "comm/framing/StaticDeframer.h"
using namespace Framing;

#include <stm32mp1xx_hal.h>



#include <console/pr_dbg.hh>

namespace MetaModule
{

void WifiInterface::init()
{
    printf_("Initializing Wifi\n");

    // auto result = Flasher::init(230400);

    BufferedUSART2::init();

    Configuration_t FrameConfig
    {
        .start=0x01,
        .end=0x02,
        .escape=0x03
    };

    StaticDeframer<100> deframer(FrameConfig, [](auto frame)
    {
        auto message = GetMessage(frame.data());

        printf_("Val: %u\n", message->state());

    });

    while (true)
    {
        auto val = BufferedUSART2::receive();
        if (val)
        {
            deframer.parse(*val);
        }
    }

}

} // namespace MetaModule
