#pragma once
#include "VCV-adaptor/events.hh"
#include "VCV-adaptor/math.hpp"

namespace rack
{
// clang-format off

struct Plugin {};
struct Model {};

namespace Svg
{
int load(auto) { return 0; }
}

namespace asset
{
int plugin(auto, auto) { return 0; }
} 

struct ParamQuantity;

struct SvgWidget {
	math::Rect box;
	SvgWidget *bg;
	ParamQuantity *pq;
	void setSvg(auto) {}
	ParamQuantity *getParamQuantity() { return pq; }
	virtual void onDoubleClick(const event::DoubleClick &e) {}
	virtual void onAction(const event::ActionEvent &e) {}
};

namespace app
{
struct SvgPort : SvgWidget {};
struct SvgSlider : SvgWidget {
	math::Vec minHandlePos;
	math::Vec maxHandlePos;
	bool horizontal;
	SvgWidget *background;

	void setBackgroundSvg(auto) {}
	void setHandleSvg(auto) {}
};

struct SvgSwitch : SvgWidget {
	void addFrame(auto) {}
};
}

struct SvgScrew : SvgWidget {};
struct BefacoTinyKnob : SvgWidget {};
struct Davies1900hBlackKnob : SvgWidget {};
struct Davies1900hKnob : SvgWidget {};
struct Davies1900hWhiteKnob : SvgWidget {};
struct Davies1900hRedKnob : SvgWidget {};
template<typename T> struct MediumLight : SvgWidget {};
struct RedGreenBlueLight : SvgWidget {};

// clang-format off

} // namespace rack

