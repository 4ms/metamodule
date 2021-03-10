#pragma once
#include "CoreModules/panel_defs.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"

namespace MetaModule
{
static constexpr uint32_t NumAudioIn = PanelDef::NumAudioIn;
static constexpr uint32_t NumAudioOut = PanelDef::NumAudioOut;
static constexpr uint32_t NumDACOut = PanelDef::NumDACOut;
static constexpr uint32_t NumPot = PanelDef::NumPot;
static constexpr uint32_t NumCVIn = PanelDef::NumCVIn;
static constexpr uint32_t NumGateIn = PanelDef::NumGateIn;
static constexpr uint32_t NumGateOut = PanelDef::NumGateOut;
static constexpr uint32_t NumPatchCV = PanelDef::NumMetaCV;
static constexpr uint32_t NumRgbButton = PanelDef::NumRgbButton;

const TimekeeperConfig control_read_tim_conf = {
	.TIMx = TIM6,
	.period_ns = 20833, // 48kHz
	.priority1 = 0,
	.priority2 = 3,
};
} // namespace MetaModule
