#pragma once
#include "VCV-adaptor/engine/ParamQuantity.hpp"
#include "VCV-adaptor/events.hh"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/window.hpp"
#include "nanovg.h"

namespace rack
{

struct DrawArgs {
	NVGcontext *vg;
	math::Rect clipBox;
	NVGLUframebuffer *fb;
};

namespace widget
{
struct Widget {
	math::Rect box;
	virtual void onDragStart(const event::DragStart &e) {
	}
	virtual void onDragMove(const event::DragMove &e) {
	}
	virtual void onDragEnd(const event::DragEnd &e) {
	}
	virtual void onDoubleClick(const event::DoubleClick &e) {
	}
	virtual void onAction(const event::ActionEvent &e) {
	}
	virtual void onHover(const HoverEvent &e) {
	}
	virtual void onHoverKey(const HoverKeyEvent &e) {
	}
	virtual void onButton(const ButtonEvent &e) {
	}
	virtual void onDragHover(const DragHoverEvent &e) {
	}
	virtual void step() {
	}
	virtual void draw(const DrawArgs &) {
	}
	virtual void drawLayer(const DrawArgs &, int) {
	}
};

struct OpaqueWidget : Widget {};
struct TransparentWidget : Widget {};
struct FramebufferWidget : Widget {};

struct SvgWidget : Widget {
	SvgWidget *bg;
	bool visible;
	engine::ParamQuantity *pq;
	void setSvg(std::shared_ptr<window::Svg>) {
	}
	void setSVG(std::shared_ptr<window::Svg>) {
	}

	engine::ParamQuantity *getParamQuantity() {
		return pq;
	}
};

} // namespace widget

namespace app
{
// Ports
struct PortWidget : widget::SvgWidget {};
struct SvgPort : app::PortWidget {};

// Params
struct ParamWidget : widget::SvgWidget {};

struct SvgSlider : app::ParamWidget {
	math::Vec minHandlePos;
	math::Vec maxHandlePos;
	bool horizontal;
	widget::SvgWidget *background;

	void setBackgroundSvg(auto) {
	}
	void setHandleSvg(auto) {
	}
};

struct SvgSwitch : ParamWidget {
	bool momentary;
	void addFrame(std::shared_ptr<window::Svg>) {
	}
};
} // namespace app

// clang-format off
// These are defined in Rack, though some appear to be brand-specific
struct SvgScrew : widget::SvgWidget {};
struct ScrewSilver : SvgScrew {};

struct BefacoBigKnob : app::ParamWidget {};
struct BefacoTinyKnob : app::ParamWidget {};
struct BefacoSlidePot : app::ParamWidget {};
struct BefacoSwitch : app::ParamWidget {};
struct BefacoPush : app::ParamWidget {};
struct CKSS : app::ParamWidget {};
struct Davies1900hBlackKnob : app::ParamWidget {};
struct Davies1900hKnob : app::ParamWidget {};
struct Davies1900hWhiteKnob : app::ParamWidget {};
struct Davies1900hRedKnob : app::ParamWidget {};
struct Davies1900hLargeWhiteKnob : app::ParamWidget{};

struct Rogan2SGray : app::ParamWidget {};
struct Rogan2PSWhite : app::ParamWidget {};
struct Rogan2PSRed : app::ParamWidget {};
struct Rogan2PSGreen : app::ParamWidget {};

struct PJ301MPort : app::PortWidget{};

template<typename T> struct MediumLight : widget::SvgWidget {};
template<typename T> struct SmallLight : widget::SvgWidget {};
struct GreenRedLight : widget::SvgWidget {};
struct RedLight : widget::SvgWidget {};
struct YellowLight : widget::SvgWidget {};
struct GreenLight : widget::SvgWidget {};
struct RedGreenBlueLight : widget::SvgWidget {};

// clang-format off

} // namespace rack

