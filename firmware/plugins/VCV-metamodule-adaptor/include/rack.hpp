#pragma once

/*
The following headers are the "public" API of Rack.

Directly including Rack headers other than rack.hpp in your plugin is unsupported/unstable, since filenames and locations of symbols may change in any Rack version.
*/

#ifdef PRIVATE
#warning "Plugins must only include rack.hpp. Including other Rack headers is unsupported."
#endif

/** Functions with the PRIVATE attribute should not be called by plugins.
*/
#ifdef __clang__
#define PRIVATE __attribute__((deprecated("Using internal Rack function or symbol")))
#else
#define PRIVATE __attribute__((error("Using internal Rack function or symbol")))
#endif

#include "metamodule/dynamic_cast.hpp"

#include <asset.hpp>
#include <audio.hpp>
#include <common.hpp>
#include <componentlibrary.hpp>
#include <context.hpp>
#include <helpers.hpp>
#include <math.hpp>
#include <midi.hpp>
#include <mutex.hpp>
#include <network.hpp>
#include <random.hpp>
#include <settings.hpp>
#include <string.hpp>
#include <system.hpp>
#include <window/Window.hpp>

#include <widget/FramebufferWidget.hpp>
#include <widget/OpaqueWidget.hpp>
#include <widget/OpenGlWidget.hpp>
#include <widget/SvgWidget.hpp>
#include <widget/TransformWidget.hpp>
#include <widget/TransparentWidget.hpp>
#include <widget/Widget.hpp>
#include <widget/ZoomWidget.hpp>
#include <widget/event.hpp>

#include <ui/Button.hpp>
#include <ui/ChoiceButton.hpp>
#include <ui/Label.hpp>
#include <ui/List.hpp>
#include <ui/Menu.hpp>
#include <ui/MenuEntry.hpp>
#include <ui/MenuItem.hpp>
#include <ui/MenuLabel.hpp>
#include <ui/MenuOverlay.hpp>
#include <ui/MenuSeparator.hpp>
#include <ui/OptionButton.hpp>
#include <ui/ProgressBar.hpp>
#include <ui/RadioButton.hpp>
#include <ui/ScrollWidget.hpp>
#include <ui/Scrollbar.hpp>
#include <ui/SequentialLayout.hpp>
#include <ui/Slider.hpp>
#include <ui/TextField.hpp>
#include <ui/Tooltip.hpp>
#include <ui/TooltipOverlay.hpp>

#include <app/AudioDisplay.hpp>
#include <app/CableWidget.hpp>
#include <app/CircularShadow.hpp>
#include <app/Knob.hpp>
#include <app/LedDisplay.hpp>
#include <app/LightWidget.hpp>
#include <app/MidiDisplay.hpp>
#include <app/ModuleLightWidget.hpp>
#include <app/ModuleWidget.hpp>
#include <app/MultiLightWidget.hpp>
#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <app/RackScrollWidget.hpp>
#include <app/RackWidget.hpp>
#include <app/RailWidget.hpp>
#include <app/Scene.hpp>
#include <app/SliderKnob.hpp>
#include <app/SvgButton.hpp>
#include <app/SvgKnob.hpp>
#include <app/SvgPanel.hpp>
#include <app/SvgPort.hpp>
#include <app/SvgScrew.hpp>
#include <app/SvgSlider.hpp>
#include <app/SvgSwitch.hpp>
#include <app/Switch.hpp>

#include <engine/Cable.hpp>
#include <engine/Engine.hpp>
#include <engine/Light.hpp>
#include <engine/LightInfo.hpp>
#include <engine/Module.hpp>
#include <engine/Param.hpp>
#include <engine/ParamHandle.hpp>
#include <engine/ParamQuantity.hpp>
#include <engine/Port.hpp>
#include <engine/PortInfo.hpp>

#include <plugin/Model.hpp>
#include <plugin/Plugin.hpp>
#include <plugin/callbacks.hpp>

#include <dsp/approx.hpp>
#include <dsp/common.hpp>
#include <dsp/convert.hpp>
#include <dsp/digital.hpp>
#include <dsp/fft.hpp>
#include <dsp/filter.hpp>
#include <dsp/fir.hpp>
#include <dsp/midi.hpp>
#include <dsp/minblep.hpp>
#include <dsp/ode.hpp>
#include <dsp/resampler.hpp>
#include <dsp/ringbuffer.hpp>
#include <dsp/vumeter.hpp>
#include <dsp/window.hpp>

#include <simd/Vector.hpp>
#include <simd/functions.hpp>

namespace rack
{

// Import some namespaces for convenience
using namespace logger;
using namespace math;
using namespace window;
using namespace widget;
using namespace ui;
using namespace app;
using plugin::Model;
using plugin::Plugin;
using namespace engine;
using namespace componentlibrary;

} // namespace rack
