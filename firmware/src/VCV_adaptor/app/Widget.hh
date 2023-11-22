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
	widget::SvgWidget *sw = nullptr;

	void setSvg(std::shared_ptr<window::Svg> svg) {
	}
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}
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

	widget::SvgWidget *fg = &_bg;
	widget::SvgWidget *bg = &_bg;

	engine::ParamQuantity *getParamQuantity() {
		if (!module)
			return nullptr;
		return module->getParamQuantity(paramId);
	}

private:
	widget::SvgWidget _bg;
};

struct SvgSlider : ParamWidget {
	math::Vec minHandlePos;
	math::Vec maxHandlePos;
	bool horizontal;
	widget::SvgWidget *background = &_background;

	void setBackgroundSvg(auto) {
	}
	void setHandleSvg(auto) {
	}
	void setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos) {
	}
	void setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered) {
	}

private:
	widget::SvgWidget _background;
};

struct SvgSwitch : ParamWidget {
	bool momentary;
	void addFrame(std::shared_ptr<window::Svg>) {
	}
};

} // namespace rack::app
