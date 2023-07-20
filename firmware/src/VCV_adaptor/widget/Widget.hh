#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/engine/ParamQuantity.hpp"
#include "VCV_adaptor/events.hh"
#include "VCV_adaptor/math.hpp"
#include "VCV_adaptor/nanovg.h"
#include "VCV_adaptor/window.hpp"

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

	virtual ~Widget() = default;

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
	virtual void onDoubleClick(const DoubleClickEvent &e) {
	}

	MetaModule::Element element;

	void hide() {
	}
};

struct OpaqueWidget : Widget {};
struct TransparentWidget : Widget {};
struct FramebufferWidget : Widget {};

// Should be called SvgParamWidget
struct SvgWidget : Widget {
	SvgWidget *bg /*= this*/;
	NVGcolor bgColor;
	bool visible;
	engine::ParamQuantity *pq = &_pq;

	void setSvg(std::shared_ptr<window::Svg>) {
	}

	void setSVG(std::shared_ptr<window::Svg>) {
	}

	engine::ParamQuantity *getParamQuantity() {
		return pq;
	}

private:
	engine::ParamQuantity _pq;
};

} // namespace widget
} // namespace rack
