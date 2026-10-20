#pragma once
#include "drivers/stm32xx.h"

namespace MetaModule
{
// The USB3DR controller's interrupt (host and device)
constexpr inline IRQn_Type UsbIRQn = USB3DR_IRQn;
} // namespace MetaModule
