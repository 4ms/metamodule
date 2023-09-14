#pragma once
#include "VCV_adaptor/widget/Widget.hh"

namespace rack::app
{

// Ports
struct PortWidget : widget::Widget {
	int portId = -1;
};

struct SvgPort : PortWidget {
	widget::FramebufferWidget *fb;
	// CircularShadow* shadow;
	widget::SvgWidget *sw;

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
	// NVGcolor bgColor = nvgRGBA(0, 0, 0, 0);
	// NVGcolor color = nvgRGBA(0, 0, 0, 0);
	// NVGcolor borderColor = nvgRGBA(0, 0, 0, 0);

	// std::vector<NVGcolor> baseColors;
	// int getNumColors(){ return 0;}
	// void addBaseColor(NVGcolor baseColor){}
	// void setBrightnesses(const std::vector<float>& brightnesses){}
};

// Params
struct ParamWidget : widget::SvgWidget {
	int paramId = -1;
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

private:
	widget::SvgWidget _background;
};

struct SvgSwitch : ParamWidget {
	bool momentary;
	void addFrame(std::shared_ptr<window::Svg>) {
	}
};

} // namespace rack::app
