#include "metamodule/make_element.hh"
#include "CoreModules/elements/units.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

static Element make_latching_rgb(std::string_view image, BaseElement const &, LatchingButton::State_t);
static Element make_latching_mono(std::string_view image, NVGcolor c, BaseElement const &, LatchingButton::State_t);
static Element make_momentary_rgb(std::string_view image, BaseElement const &);
static Element make_momentary_mono(std::string_view image, NVGcolor c, BaseElement const &);

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

Element make_element(rack::app::SvgPort *widget, BaseElement) {
	pr_trace("make_element(Port %d) %d at %f %f\n", widget->type, widget->portId, widget->box.pos.x, widget->box.pos.y);

	if (widget->type == rack::engine::Port::Type::INPUT) {
		JackInput element{};
		if (widget->sw->svg)
			element.image = widget->sw->svg->filename;
		return element;

	} else {
		JackOutput element{};
		if (widget->sw->svg)
			element.image = widget->sw->svg->filename;
		return element;
	}
}

Element make_element(rack::app::PortWidget *widget, BaseElement) {
	pr_trace("make_element(Port %d) %d at %f %f\n", widget->type, widget->portId, widget->box.pos.x, widget->box.pos.y);

	if (widget->type == rack::engine::Port::Type::INPUT) {
		return JackInput{};
	} else {
		return JackOutput{};
	}
}

//
// Pots/Sliders
//
Element make_element(rack::app::Knob *widget, BaseElement) {
	pr_trace("make_element(Knob) %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

	Knob element{};
	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

Element make_element(rack::app::SvgKnob *widget, BaseElement b) {
	pr_trace("make_element(SvgKnob) %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

	Knob element{};
	element.DefaultValue = getScaledDefaultValue(widget);

	// Hack to support BefacoTinyKnobs:
	// The main SVG is just the dot, either BefacoTinyPointWhite or BefacoTinyPointBlack.
	// The bg SVG has the knob color: red, white, lightGray, darkGray, or black.
	// Therefore we can't ignore the bg SVG since it determines the knob color.
	// The bg SVG is a child of the FramebufferWidget (fb), but it's not part of the SvgKnob class.
	// In MM, we merged the Point (dot) and bg images and saved that in the bg PNG.
	// The Point PNG is not drawn, but it must have the right size because that's used to center the jack.
	// TODO: consider using a concept make_element like:
	// requires derived_form<T, SvgKnob> && !same_as<T, SvgKnob> && requires(...){w->bg->svg->filename;}
	auto find_inner_svg_widget = [](rack::widget::FramebufferWidget *fb) {
		for (auto child : fb->children) {
			if (auto svgw = dynamic_cast<rack::widget::SvgWidget *>(child)) {
				if (svgw->svg->filename.size() > 0 && !svgw->box.size.isZero() && svgw->box.size.isFinite()) {
					return std::string_view{svgw->svg->filename};
				}
			}
		}
		return std::string_view{""};
	};

	if (auto inner_img = find_inner_svg_widget(widget->fb); inner_img.size() > 0) {
		pr_trace("make_element(SvgKnob): found SvgWidget child of fb with an SVG %s\n", inner_img.data());
		element.image = inner_img;

	} else if (widget->sw->svg->filename.size()) {
		pr_trace("make_element(SvgKnob): use sw->svg %s\n", widget->sw->svg->filename.data());
		element.image = widget->sw->svg->filename;

	} else {
		pr_trace("make_element(SvgKnob): use svg %s\n", widget->svg->filename.data());
		element.image = widget->svg->filename;
	}

	return element;
}

Element make_element(rack::app::SliderKnob *widget, BaseElement b) {
	pr_trace("make_element(SliderKnob) %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

	Slider element{};
	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

static Element make_slideswitch(rack::app::SvgSlider *widget) {
	SlideSwitch element{};

	if (widget->background->svg->filename.length()) {
		element.image = widget->background->svg->filename;
	} else if (widget->svg->filename.length()) {
		element.image = widget->svg->filename;
	}

	element.DefaultValue = getScaledDefaultValue(widget);

	if (widget->handle->svg->filename.length())
		element.image_handle = widget->handle->svg->filename;

	auto pq = widget->getParamQuantity();

	element.num_pos = pq->maxValue - pq->minValue + 1;

	if (element.num_pos < 2 || element.num_pos > element.pos_names.size()) {
		pr_warn("Warning: SvgSlider (max - min + 1) is %d, but must be 2..8\n", element.num_pos);
		element.num_pos = std::clamp<size_t>(element.num_pos, 2, element.pos_names.size());
	}

	for (auto i = 0u; i < std::min<size_t>(element.num_pos, pq->labels.size()); i++) {
		element.pos_names[i] = pq->labels[i];
	}

	// This seems to be the default for VCV?
	if (widget->box.size.x < widget->box.size.y) //vertical
		element.direction = SlideSwitch::Ascend::UpLeft;
	else
		element.direction = SlideSwitch::Ascend::DownRight;
	return element;
}

Element make_element(rack::app::SvgSlider *widget, BaseElement b) {

	if (auto pq = widget->getParamQuantity(); pq && pq->snapEnabled) {
		pr_trace(
			"make_element(SvgSlider) switch %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);
		return make_slideswitch(widget);
	}

	else
	{
		pr_trace(
			"make_element(SvgSlider) slider %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

		Slider::State_t defaultValue = getScaledDefaultValue(widget);
		if (widget->background->svg->filename.length()) {
			return Slider{{{b, widget->background->svg->filename}, defaultValue}, widget->handle->svg->filename};
		} else {
			return Slider{{{b, widget->svg->filename}, defaultValue}, widget->handle->svg->filename};
		}
	}
}

Element make_element_lightslider(rack::app::SvgSlider *widget, BaseElement b) {
	pr_trace("Svg Light Slider %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

	SliderLight::State_t defaultValue = getScaledDefaultValue(widget);

	if (widget->background->svg->filename.length()) {
		return SliderLight{{{{b, widget->background->svg->filename}, defaultValue}, widget->handle->svg->filename},
						   Colors565::Red};
	} else {
		return SliderLight{{{{b, widget->svg->filename}, defaultValue}, widget->handle->svg->filename}, Colors565::Red};
	}
}

Element make_element(rack::componentlibrary::Rogan *widget, BaseElement b) {
	pr_trace("Rogan knob %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

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

MomentaryButton make_momentary(rack::app::SvgSwitch *widget) {
	MomentaryButton element{};

	if (widget->frames.size() > 0) {
		element.image = widget->frames[0]->filename;

		if (widget->frames.size() > 1)
			element.pressed_image = widget->frames[1]->filename;

		if (widget->frames.size() > 2)
			pr_info("Excess momentary button frames ignored\n");

	} else {
		pr_warn("Warning: SvgSwitch has no image frames\n");
	}

	return element;
}

FlipSwitch make_flipswitch(rack::app::SvgSwitch *widget) {
	FlipSwitch element{};

	if (auto pq = widget->getParamQuantity(); pq) {
		// Set the number of positions based on the max/min values set in configSwitch or configParam
		element.num_pos = pq->maxValue - pq->minValue + 1;

		if (element.num_pos < 2 || element.num_pos > 3) {
			pr_warn("Warning: SvgSwitch (max - min + 1) is %d, but must be 2 or 3\n", element.num_pos);
			element.num_pos = std::clamp<size_t>(widget->frames.size(), 2, 3);
		}

		for (auto i = 0u; i < std::min<size_t>(element.num_pos, pq->labels.size()); i++) {
			element.pos_names[i] = pq->labels[i];
		}
	} else {
		// Gracefully handle an unconfigured param:
		element.num_pos = std::clamp<size_t>(widget->frames.size(), 2, 3);
		pr_warn("Warning: SvgSwitch not configured with configParam or configSwitch\n");
	}

	for (unsigned i = 0; i < std::min<size_t>(element.num_pos, widget->frames.size()); i++) {
		element.frames[i] = widget->frames[i]->filename;
	}

	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

Element make_element(rack::app::SvgSwitch *widget, BaseElement) {
	pr_trace("make_element(SvgSwitch) %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

	bool momentary = widget->momentary;
	if (widget->frames.size() >= 3) {
		// Handle custom widgets that are not really momentary, like Befaco StereoStrip Mute switch
		momentary = false;
	}

	if (momentary) {
		return make_momentary(widget);
	} else {
		return make_flipswitch(widget);
	}
}

/////////////////////
////////////////////

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
	pr_trace("Button light %d at %f, %f\n", widget->paramId, widget->box.pos.x, widget->box.pos.y);

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
	pr_trace("Light with %d elem at %f %f\n", widget->getNumColors(), widget->box.pos.x, widget->box.pos.y);

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
	pr_trace("SVG Light with %d elem at %f %f\n", widget->getNumColors(), widget->box.pos.x, widget->box.pos.y);

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
	pr_trace("make_element(SvgScrew): skip\n");
	return NullElement{};
}

Element make_element(rack::widget::Widget *widget, BaseElement) {
	pr_trace("Unknown widget at %f, %f: skip\n", widget->getBox().pos.x, widget->getBox().pos.y);
	return NullElement{};
}

Element make_element(rack::app::ParamWidget *widget, BaseElement b) {
	if (widget->svg && widget->svg->filename.size()) {
		pr_warn("Unknown ParamWidget (param id %d)\n", widget->paramId);
		return ParamElement{b, widget->svg->filename};

	} else {
		pr_warn("ParamWidget (param id %d) without an SVG, using a blank ParamElement\n", widget->paramId);
		// b.width_mm = to_mm(widget->box.size.x);
		// b.height_mm = to_mm(widget->box.size.y);
		return ParamElement{b, ""};
	}
}

Element make_element(rack::widget::SvgWidget *widget, BaseElement b) {
	if (widget->svg->filename.size()) {
		pr_trace("Unknown SvgWidget, using image as a ImageElement\n");
		return ImageElement{b, widget->svg->filename};

	} else {
		pr_warn("Unknown SvgWidget\n");
		b.width_mm = to_mm(widget->box.size.x);
		b.height_mm = to_mm(widget->box.size.y);
		return NullElement{b};
	}
}

Element make_element(rack::app::SvgButton *widget, BaseElement b) {
	return make_element(widget->sw, b);
}

} // namespace MetaModule
