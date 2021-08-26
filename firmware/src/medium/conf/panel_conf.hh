#pragma once
#include "CoreModules/panel_medium_defs.hh"
namespace MetaModule
{
//Do we need to do this, or can't we just access PanelDef from whatever includes this file?
static constexpr uint32_t NumAudioIn = PanelDef::NumAudioIn;
static constexpr uint32_t NumAudioOut = PanelDef::NumAudioOut;
static constexpr uint32_t NumDACOut = PanelDef::NumDACOut;
static constexpr uint32_t NumPot = PanelDef::NumPot;
static constexpr uint32_t NumCVIn = PanelDef::NumCVIn;
static constexpr uint32_t NumGateIn = PanelDef::NumGateIn;
static constexpr uint32_t NumGateOut = PanelDef::NumGateOut;
static constexpr uint32_t NumPatchCV = PanelDef::NumMetaCV;
static constexpr uint32_t NumRgbButton = PanelDef::NumRgbButton;

} // namespace MetaModule
