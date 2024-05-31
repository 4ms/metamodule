#include "metamodule/make_element.hh"
#include "CoreModules/elements/units.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

static Element make_latching_rgb(std::string_view image, BaseElement const &el, LatchingButton::State_t defaultValue);
static Element
make_latching_mono(std::string_view image, NVGcolor c, BaseElement const &el, LatchingButton::State_t defaultValue);
static Element make_momentary_rgb(std::string_view image, BaseElement const &el);
static Element make_momentary_mono(std::string_view image, NVGcolor c, BaseElement const &el);

static float getScaledDefaultValue(rack::app::ParamWidget *widget) {
	if (!widget)
		return 0;
	auto pq = widget->getParamQuantity();
	float defaultValue = pq ? pq->toScaled(pq->getDefaultValue()) : 0.f;
	return defaultValue;
}

//
// Jacks
//

Element make_element_output(rack::app::SvgPort *widget, BaseElement b) {
	if (widget->sw->svg)
		return JackOutput{b, widget->sw->svg->filename};
	else
		return JackOutput{b, ""};
}

Element make_element_input(rack::app::SvgPort *widget, BaseElement b) {
	if (widget->sw->svg)
		return JackInput{b, widget->sw->svg->filename};
	else
		return JackInput{b, ""};
}

//
// Pots/Sliders
//
Element make_element(rack::app::Knob *widget, BaseElement b) {
	b.width_mm = to_mm(widget->box.size.x);
	b.height_mm = to_mm(widget->box.size.y);
	Knob::State_t defaultValue = getScaledDefaultValue(widget);
	return Knob{{{b, ""}, defaultValue}};
}

//TODO: don't set box size here
// either have dedicated function refresh_widget_size() which scans all children,
// or in SvgWidget::setSvg, set its parents size recursively (if not set)
Element make_element(rack::app::SvgKnob *widget, BaseElement b) {
	Knob::State_t defaultValue = getScaledDefaultValue(widget);

	// SvgKnobs have a base SVG, and sometimes have a bg svg.
	// If there is a bg svg, then use its name.
	if (widget->fb->_bg && widget->fb->_bg->svg && widget->fb->_bg->svg->filename.length()) {
		// TODO: are there some cases when a widget sets its box differently than the bg box?
		// if (widget->box.size.isFinite() && !widget->box.size.isZero())
		widget->box.size = widget->fb->_bg->box.size;
		return Knob{{{b, widget->fb->_bg->svg->filename}, defaultValue}};

	} else if (widget->sw->svg->filename.size()) {
		return Knob{{{b, widget->sw->svg->filename}, defaultValue}};

	} else {
		return Knob{{{b, widget->svg->filename}, defaultValue}};
	}
}

Element make_element(rack::app::SliderKnob *widget, BaseElement b) {
	b.width_mm = to_mm(widget->box.size.x);
	b.height_mm = to_mm(widget->box.size.y);
	Slider::State_t defaultValue = getScaledDefaultValue(widget);
	return Slider{{{b, ""}, defaultValue}, ""};
}

Element make_element_slideswitch(rack::app::SvgSlider *widget, BaseElement b) {
	//Note: num_pos and labels are filled in later
	if (widget->background->svg->filename.length()) {
		SlideSwitch::State_t defaultValue = getScaledDefaultValue(widget);
		return SlideSwitch{{{b, widget->background->svg->filename}, 2, defaultValue}, widget->handle->svg->filename};
	} else {
		SlideSwitch::State_t defaultValue = 0;
		return SlideSwitch{{{b, widget->svg->filename}, 2, defaultValue}, widget->handle->svg->filename};
	}
}

Element make_element(rack::app::SvgSlider *widget, BaseElement b) {
	Slider::State_t defaultValue = getScaledDefaultValue(widget);
	if (widget->background->svg->filename.length()) {
		return Slider{{{b, widget->background->svg->filename}, defaultValue}, widget->handle->svg->filename};
	} else {
		return Slider{{{b, widget->svg->filename}, defaultValue}, widget->handle->svg->filename};
	}
}

Element make_element_lightslider(rack::app::SvgSlider *widget, BaseElement b) {
	SliderLight::State_t defaultValue = getScaledDefaultValue(widget);

	if (widget->background->svg->filename.length()) {
		return SliderLight{{{{b, widget->background->svg->filename}, defaultValue}, widget->handle->svg->filename},
						   Colors565::Red};
	} else {
		return SliderLight{{{{b, widget->svg->filename}, defaultValue}, widget->handle->svg->filename}, Colors565::Red};
	}
}

Element make_element(rack::componentlibrary::Rogan *widget, BaseElement b) {
	Knob::State_t defaultValue = getScaledDefaultValue(widget);

	// Rogan knobs have a Rogan::bg svg, Rogan::fg svg, SvgKnob::sw svg, and SvgWidget::svg.
	// The fg and base svgs are always the same color and thus are combined into one PNG for the MetaModule.
	// The bg svg is lighting effect gradient and can be ignored for MetaModule's low-res screen.
	// The SvgKnob::sw rotates
	// The SvgWidget::svg is not used (it's in MM only, not in Rack)
	if (widget->sw)
		return Knob{{{b, widget->sw->svg->filename}, defaultValue}};
	else
		return Knob{{{b, widget->svg->filename}, defaultValue}};
}

//
// Switch/Button
//

Element make_element(rack::app::SvgSwitch *widget, BaseElement b) {
	FlipSwitch::State_t defaultValue = getScaledDefaultValue(widget);

	if (widget->frames.size() == 3) {
		return FlipSwitch{
			{{b}, 3, defaultValue},
			{widget->frames[0]->filename, widget->frames[1]->filename, widget->frames[2]->filename},
		};

	} else if (widget->frames.size() == 2) {
		if (widget->momentary) {
			return MomentaryButton{{b, widget->frames[0]->filename}, widget->frames[1]->filename};
		} else {
			return FlipSwitch{
				{{b}, 2, defaultValue},
				{widget->frames[0]->filename, widget->frames[1]->filename},
			};
		}

	} else if (widget->frames.size() == 1) {
		return MomentaryButton{{b, widget->frames[0]->filename}};

	} else {
		pr_warn("make_element(): Unknown SvgSwitch, frames size is not 1, 2 or 3\n");
		b.width_mm = to_mm(widget->box.size.x);
		b.height_mm = to_mm(widget->box.size.y);
		return ParamElement{b};
	}
}

Element make_momentary_rgb(std::string_view image, BaseElement const &el) {
	return MomentaryButtonRGB{{{el, image}}};
}

Element make_latching_rgb(std::string_view image, BaseElement const &el, LatchingButton::State_t defaultValue) {
	pr_warn("Latching RGB button not supported yet. Using momentary\n");
	return MomentaryButtonRGB{{{el, image}}};
}

Element make_momentary_mono(std::string_view image, NVGcolor c, BaseElement const &el) {
	return MomentaryButtonLight{{{el, image}}, RGB565{c.r, c.g, c.b}};
}

Element
make_latching_mono(std::string_view image, NVGcolor c, BaseElement const &el, LatchingButton::State_t defaultValue) {
	return LatchingButton{{{el, image}}, defaultValue, RGB565{c.r, c.g, c.b}};
}

Element make_button_light(rack::app::MultiLightWidget *light, rack::app::SvgSwitch *widget, BaseElement const &el) {
	LatchingButton::State_t defaultValue =
		getScaledDefaultValue(widget) > 0.5f ? LatchingButton::State_t::UP : LatchingButton::State_t::DOWN;

	if (light->getNumColors() == 1) {
		auto c = light->baseColors[0];
		if (widget->momentary)
			return make_momentary_mono(widget->frames[0]->filename, c, el);
		else
			return make_latching_mono(widget->frames[0]->filename, c, el, defaultValue);
	}

	if (light->getNumColors() == 3) {
		if (widget->momentary)
			return make_momentary_rgb(widget->frames[0]->filename, el);
		else
			return make_latching_rgb(widget->frames[0]->filename, el, defaultValue);
	}

	pr_warn("make_element(): Unknown VCVLightBezel\n");
	return NullElement{};
}

//
// LEDS
//

std::string_view get_led_image_by_size(rack::widget::Widget const *widget) {
	auto size = to_mm(widget->box.size.x);

	std::string_view image = size <= 2.6f ? "rack-lib/SmallLight.png" : //4px => 2.14mm
							 size <= 3.7f ? "rack-lib/MediumLight.png" : //6px => 3.21mm
							 size <= 4.5f ? "rack-lib/Light8px.png" : //8px => 4.28mm
							 size <= 5.3f ? "rack-lib/LargeLight.png" : //9px => 4.82mm
							 size <= 6.5f ? "rack-lib/VCVBezelLight.png" : //11px => 5.89mm
							 size <= 18.f ? "rack-lib/VCVBezel.png" : //14px => 7.5mm
											"rack-lib/Rogan6PSLight.png"; //44px

	return image;
}

Element
make_mono_led_element(std::string_view image, rack::app::MultiLightWidget const *widget, BaseElement const &el) {
	auto c = widget->baseColors[0];
	return MonoLight{{el, image}, RGB565{c.r, c.g, c.b}};
}

Element
make_dual_led_element(std::string_view image, rack::app::MultiLightWidget const *widget, BaseElement const &el) {
	auto c1 = widget->baseColors[0];
	auto c2 = widget->baseColors[1];
	return DualLight{{el, image}, {RGB565{c1.r, c1.g, c1.b}, RGB565{c2.r, c2.g, c2.b}}};
}

Element make_rgb_led_element(std::string_view image, rack::app::MultiLightWidget const *widget, BaseElement const &el) {
	return RgbLight{el, image};
}

Element make_element(rack::app::MultiLightWidget *widget, BaseElement el) {
	auto image = get_led_image_by_size(widget);

	if (widget->getNumColors() == 1) {
		return make_mono_led_element(image, widget, el);

	} else if (widget->getNumColors() == 2) {
		return make_dual_led_element(image, widget, el);

	} else if (widget->getNumColors() == 3) {
		return make_rgb_led_element(image, widget, el);

	} else {
		pr_warn("Light widget not handled (%d colors)\n", widget->getNumColors());
		return NullElement{};
	}
}

Element make_multi_led_element(std::string_view image, rack::app::MultiLightWidget *widget, BaseElement const &el) {
	if (widget->getNumColors() == 1) {
		return make_mono_led_element(image, widget, el);
	}
	if (widget->getNumColors() == 2) {
		return make_dual_led_element(image, widget, el);
	}
	if (widget->getNumColors() == 3) {
		return make_rgb_led_element(image, widget, el);
	}

	pr_warn("SVG Light widget not handled (%d colors)\n", widget->getNumColors());
	return NullElement{};
}

//
// Not supported
//

Element make_element(rack::app::SvgScrew *widget, BaseElement) {
	return NullElement{};
}

Element make_element(rack::widget::Widget *widget, BaseElement) {
	return NullElement{};
}

Element make_element(rack::app::ParamWidget *widget, BaseElement b) {
	if (widget->svg && widget->svg->filename.size()) {
		pr_dbg("Unknown ParamWidget, using image as a ParamElement\n");
		return ParamElement{b, widget->svg->filename};

	} else {
		pr_dbg("ParamWidget without an SVG, using a blank ParamElement\n");
		b.width_mm = to_mm(widget->box.size.x);
		b.height_mm = to_mm(widget->box.size.y);
		return ParamElement{b, ""};
	}
}

Element make_element(rack::widget::SvgWidget *widget, BaseElement b) {
	if (widget->svg->filename.size()) {
		pr_dbg("Unknown SvgWidget, using image as a ImageElement\n");
		return ImageElement{b, widget->svg->filename};

	} else {
		pr_warn("Unknown SvgWidget\n");
		b.width_mm = to_mm(widget->box.size.x);
		b.height_mm = to_mm(widget->box.size.y);
		return NullElement{b};
	}
}
} // namespace MetaModule
