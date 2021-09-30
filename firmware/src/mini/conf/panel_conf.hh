#pragma once
#include "CoreModules/panel_mini_defs.hh"
#include <arm_neon.h>
#include <cstdint>
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
static constexpr uint32_t NumMetaRgbButton = PanelDef::NumMetaRgbButton;
} // namespace MetaModule
