#pragma once
#include "VCV-adaptor/engine/ParamQuantity.hpp"
#include "VCV-adaptor/events.hh"
#include "VCV-adaptor/math.hpp"

namespace rack
{
namespace Svg
{
int load(auto) {
	return 0;
}
} // namespace Svg

namespace asset
{
int plugin(auto, auto) {
	return 0;
}
} // namespace asset

struct Widget {
	math::Rect box;
};
struct ParamWidget : Widget {};
struct PortWidget : Widget {};

struct SvgWidget : Widget {
	SvgWidget *bg;
	engine::ParamQuantity *pq;
	void setSvg(auto) {
	}
	engine::ParamQuantity *getParamQuantity() {
		return pq;
	}
	virtual void onDoubleClick(const event::DoubleClick &e) {
	}
	virtual void onAction(const event::ActionEvent &e) {
	}
};

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

struct SvgSwitch : SvgWidget {
	void addFrame(auto) {
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
struct Davies1900hBlackKnob : SvgWidget {};
struct Davies1900hKnob : SvgWidget {};
struct Davies1900hWhiteKnob : SvgWidget {};
struct Davies1900hRedKnob : SvgWidget {};
template<typename T> struct MediumLight : SvgWidget {};
template<typename T> struct SmallLight : SvgWidget {};
struct GreenRedLight : SvgWidget {};
struct RedLight : SvgWidget {};
struct YellowLight : SvgWidget {};
struct GreenLight : SvgWidget {};
struct RedGreenBlueLight : SvgWidget {};

// clang-format off

} // namespace rack

