#pragma once
#include "VCV-adaptor/engine/ParamQuantity.hpp"
#include "VCV-adaptor/events.hh"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/window.hpp"

namespace rack
{

struct DrawArgs {};

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
};

struct OpaqueWidget : Widget {};
struct TransparentWidget : Widget {};
struct FramebufferWidget : Widget {};

struct SvgWidget : Widget {
	SvgWidget *bg;
	engine::ParamQuantity *pq;
	void setSvg(auto) {
	}
	engine::ParamQuantity *getParamQuantity() {
		return pq;
	}
};

} // namespace widget

namespace app
{
struct PortWidget : widget::Widget {};
struct ParamWidget : widget::SvgWidget {};
struct SvgPort : widget::SvgWidget {};

struct SvgSlider : widget::SvgWidget {
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
	void addFrame(window::Svg *) {
	}
};
} // namespace app

// clang-format off
// These are defined in Rack, though some appear to be brand-specific
struct SvgScrew : widget::SvgWidget {};
struct BefacoBigKnob : widget::SvgWidget {};
struct BefacoTinyKnob : widget::SvgWidget {};
struct BefacoSlidePot : widget::SvgWidget {};
struct BefacoSwitch : widget::SvgWidget {};
struct BefacoPush : widget::SvgWidget {};
struct CKSS : widget::SvgWidget {};
struct Davies1900hBlackKnob : widget::SvgWidget {};
struct Davies1900hKnob : widget::SvgWidget {};
struct Davies1900hWhiteKnob : widget::SvgWidget {};
struct Davies1900hRedKnob : widget::SvgWidget {};
struct Davies1900hLargeWhiteKnob : widget::SvgWidget{};
template<typename T> struct MediumLight : widget::SvgWidget {};
template<typename T> struct SmallLight : widget::SvgWidget {};
struct GreenRedLight : widget::SvgWidget {};
struct RedLight : widget::SvgWidget {};
struct YellowLight : widget::SvgWidget {};
struct GreenLight : widget::SvgWidget {};
struct RedGreenBlueLight : widget::SvgWidget {};

// clang-format off

} // namespace rack

