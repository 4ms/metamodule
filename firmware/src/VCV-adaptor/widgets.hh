#pragma once
#include "VCV-adaptor/engine/ParamQuantity.hpp"
#include "VCV-adaptor/events.hh"
#include "VCV-adaptor/math.hpp"

namespace rack
{
namespace Svg
{
inline std::string_view load(auto) {
	return "";
}
} // namespace Svg

namespace asset
{
inline std::string_view plugin(auto, auto) {
	return "";
}

inline std::string_view system(std::string_view) {
	return "";
}
} // namespace asset

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
};

struct PortWidget : Widget {};

struct SvgWidget : Widget {
	SvgWidget *bg;
	engine::ParamQuantity *pq;
	void setSvg(auto) {
	}
	engine::ParamQuantity *getParamQuantity() {
		return pq;
	}
};

struct ParamWidget : SvgWidget {};

namespace app
{
struct SvgPort : SvgWidget {};
struct SvgSlider : SvgWidget {
	math::Vec minHandlePos;
	math::Vec maxHandlePos;
	bool horizontal;
	SvgWidget *background;

	void setBackgroundSvg(auto) {
	}
	void setHandleSvg(auto) {
	}
};

struct SvgSwitch : ParamWidget {
	bool momentary;
	void addFrame(std::string_view) {
	}
};
} // namespace app

// clang-format off
// These are defined in Rack, though some appear to be brancd-specific
struct SvgScrew : SvgWidget {};
struct BefacoBigKnob : SvgWidget {};
struct BefacoTinyKnob : SvgWidget {};
struct BefacoSlidePot : SvgWidget {};
struct BefacoSwitch : SvgWidget {};
struct BefacoPush : SvgWidget {};
struct CKSS : SvgWidget {};
struct Davies1900hBlackKnob : SvgWidget {};
struct Davies1900hKnob : SvgWidget {};
struct Davies1900hWhiteKnob : SvgWidget {};
struct Davies1900hRedKnob : SvgWidget {};
struct Davies1900hLargeWhiteKnob : SvgWidget{};
template<typename T> struct MediumLight : SvgWidget {};
template<typename T> struct SmallLight : SvgWidget {};
struct GreenRedLight : SvgWidget {};
struct RedLight : SvgWidget {};
struct YellowLight : SvgWidget {};
struct GreenLight : SvgWidget {};
struct RedGreenBlueLight : SvgWidget {};

// clang-format off

} // namespace rack

