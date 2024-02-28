#pragma once
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/engine/PortInfo.hpp"
#include "VCV_adaptor/widget/Widget.hh"

namespace rack::app
{

// Ports
struct PortWidget : widget::Widget {
	int portId = -1;
	engine::Port::Type type = engine::Port::INPUT;
	engine::Module *module = nullptr;

	engine::PortInfo *getPortInfo() {
		if (!module)
			return nullptr;
		if (type == engine::Port::INPUT)
			return (size_t)portId < module->inputInfos.size() ? module->inputInfos[portId].get() : nullptr;
		else
			return (size_t)portId < module->outputInfos.size() ? module->outputInfos[portId].get() : nullptr;
	}
};

struct SvgPort : PortWidget {
	widget::FramebufferWidget *fb = nullptr;
	// CircularShadow* shadow;
	widget::SvgWidget *sw = &_sw;

	void setSvg(std::shared_ptr<window::Svg> svg) {
	}
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}

private:
	widget::SvgWidget _sw;
};

struct ThemedSvgPort : SvgPort {
	std::shared_ptr<window::Svg> lightSvg;
	std::shared_ptr<window::Svg> darkSvg;

	void setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
	}

	void step() override {
	}
};

// Lights

struct ModuleLightWidget : widget::Widget {
	engine::Module *module;
	int firstLightId = -1;
	NVGcolor bgColor = nvgRGBA(0, 0, 0, 0);
	NVGcolor color = nvgRGBA(0, 0, 0, 0);
	NVGcolor borderColor = nvgRGBA(0, 0, 0, 0);

	std::vector<NVGcolor> baseColors;
	int getNumColors() {
		return 0;
	}
	void addBaseColor(NVGcolor baseColor) {
	}
	void setBrightnesses(const std::vector<float> &brightnesses) {
	}
};

// Params
struct ParamWidget : widget::SvgWidget {
	int paramId = -1;
	engine::Module *module = nullptr;

	engine::ParamQuantity *getParamQuantity() {
		if (!module)
			return nullptr;
		return module->getParamQuantity(paramId);
	}

private:
};

struct Knob : ParamWidget {
	bool horizontal = false;
	bool smooth = true;
	bool snap = false;
	float speed = 1.f;
	bool forceLinear = false;
	float minAngle = -M_PI;
	float maxAngle = M_PI;
};

struct SvgKnob : Knob {
	widget::FramebufferWidget *fb;
	// CircularShadow* shadow;
	widget::SvgWidget *sw;
	widget::TransformWidget *tw;
};

struct SvgSlider : Knob {
	std::unique_ptr<widget::FramebufferWidget> fb{new widget::FramebufferWidget};
	std::unique_ptr<widget::SvgWidget> background{new widget::SvgWidget};
	std::unique_ptr<widget::SvgWidget> handle{new widget::SvgWidget};

	math::Vec minHandlePos, maxHandlePos;

	void setBackgroundSvg(std::shared_ptr<window::Svg> svg) {
		background->svg_filename = svg->filename;
	}
	void setHandleSvg(std::shared_ptr<window::Svg> svg) {
		handle->svg_filename = svg->filename;
	}
	void setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos) {
	}
	void setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered) {
	}

private:
	widget::SvgWidget _background;
};

struct CircularShadow : widget::TransparentWidget {};

struct SvgSwitch : ParamWidget {
	widget::FramebufferWidget *fb;
	CircularShadow *shadow;
	widget::SvgWidget *sw;
	bool latch = false;

	// std::vector<std::shared_ptr<window::Svg>> frames;
	std::vector<std::string> frames;

	bool momentary;

	void addFrame(std::shared_ptr<window::Svg> svg) {
		frames.push_back(svg->filename);
	}
};

} // namespace rack::app
