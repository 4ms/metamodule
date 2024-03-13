#pragma once
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/engine/PortInfo.hpp"
#include "VCV_adaptor/widget/Widget.hh"

namespace rack::app
{

struct CircularShadow : widget::TransparentWidget {};

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
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;
	std::string svg_filename;

	void setSvg(std::shared_ptr<window::Svg> svg) {
		if (svg->filename.size()) {
			svg_filename = svg->filename;
			// printf("SvgPort:svg_filename %s\n", svg_filename.c_str());
		} else
			printf("SvgPort: svg with empty name\n");
	}
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
};

struct ThemedSvgPort : SvgPort {
	std::shared_ptr<window::Svg> lightSvg;
	std::shared_ptr<window::Svg> darkSvg;

	void setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
		svg_filename = lightSvg->filename;
		this->lightSvg = lightSvg;
		this->darkSvg = darkSvg;
	}

	void step() override {
	}
};

// Lights

struct LightWidget : widget::Widget {
	NVGcolor bgColor = nvgRGBA(0, 0, 0, 0);
	NVGcolor color = nvgRGBA(0, 0, 0, 0);
	NVGcolor borderColor = nvgRGBA(0, 0, 0, 0);
};

struct MultiLightWidget : LightWidget {
	std::vector<NVGcolor> baseColors;

	int getNumColors() const {
		return baseColors.size();
	}

	void addBaseColor(NVGcolor baseColor) {
		baseColors.push_back(baseColor);
	}

	void setBrightnesses(const std::vector<float> &brightnesses) {
		//TODO
	}
};

struct ModuleLightWidget : MultiLightWidget {
	engine::Module *module = nullptr;
	int firstLightId = -1;

	engine::Light *getLight(int colorId) {
		if (!module || firstLightId < 0)
			return nullptr;
		return &module->lights[firstLightId + colorId];
	}

	engine::LightInfo *getLightInfo() {
		if (!module || firstLightId < 0)
			return nullptr;
		return module->lightInfos[firstLightId].get();
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

// construct fb with SvgKnob *(this)
// call to fb->addChildBelow uses b
struct SvgKnob : Knob {
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;
	widget::TransformWidget *tw = &_tw;

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
	widget::TransformWidget _tw;
};

struct SvgSlider : Knob {
	std::unique_ptr<widget::FramebufferWidget> fb{new widget::FramebufferWidget};
	std::unique_ptr<widget::SvgWidget> background{new widget::SvgWidget};
	std::unique_ptr<widget::SvgWidget> handle{new widget::SvgWidget};
	math::Vec minHandlePos, maxHandlePos;

	void setBackgroundSvg(std::shared_ptr<window::Svg> svg) {
		if (svg->filename.size())
			background->svg_filename = svg->filename;
		else
			printf("Svgslider: Svg bg with empty name\n");
	}

	void setHandleSvg(std::shared_ptr<window::Svg> svg) {
		if (svg->filename.size())
			handle->svg_filename = svg->filename;
		else
			printf("Svgslider: Svg with empty name\n");
	}

	void setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos) {
	}

	void setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered) {
	}
};

struct SvgSwitch : ParamWidget {
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;

	bool latch = false;
	bool momentary = false;

	std::vector<std::string> frames;

	void addFrame(std::shared_ptr<window::Svg> svg) {
		frames.push_back(svg->filename);
	}

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
};

} // namespace rack::app
