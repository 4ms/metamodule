#pragma once
#include "drivers/stm32xx.h"

namespace MetaModule
{
// The USB OTG core's interrupt (host and device)
constexpr inline IRQn_Type UsbIRQn = OTG_IRQn;
} // namespace MetaModule
