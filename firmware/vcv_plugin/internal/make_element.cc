#include "make_element.hh"
#include "CoreModules/elements/base_element.hh"
#include "CoreModules/elements/units.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

static inline constexpr bool LogWidgetTypeIds = false;

static void log_make_element(std::string_view type, unsigned id) {
	if constexpr (LogWidgetTypeIds) {
		pr_dbg("make_element(%s) idx=%d\n", type.data(), id);
	}
}

static void log_make_element_notes(std::string_view note1, std::string_view note2) {
	if constexpr (LogWidgetTypeIds) {
		pr_dbg("%s %s\n", note1.data(), note2.data());
	}
}

static float getScaledDefaultValue(rack::app::ParamWidget *widget);

//
// Jacks
//

Element make_element(rack::app::SvgPort *widget) {

	if (widget->type == rack::engine::Port::Type::INPUT) {
		log_make_element("SvgPort In", widget->portId);
		JackInput element{};
		if (widget->sw->svg)
			element.image = widget->sw->svg->filename;
		return element;

	} else {
		log_make_element("SvgPort Out", widget->portId);
		JackOutput element{};
		if (widget->sw->svg)
			element.image = widget->sw->svg->filename;
		return element;
	}
}

Element make_element(rack::app::PortWidget *widget) {
	if (widget->type == rack::engine::Port::Type::INPUT) {
		log_make_element("Port In", widget->portId);
		return JackInput{};
	} else {
		log_make_element("Port Out", widget->portId);
		return JackOutput{};
	}
}

//
// Pots
//

Element make_element(rack::app::Knob *widget) {
	log_make_element("Knob", widget->paramId);

	Knob element{};
	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

Element make_element(rack::componentlibrary::Rogan *widget) {
	Knob element{};
	element.DefaultValue = getScaledDefaultValue(widget);

	if (widget->sw->svg->filename.size()) {
		element.image = widget->sw->svg->filename;

	} else {
		pr_err("make_element(Rogan): No svg was set\n");
	}

	return element;
}

Element make_element(rack::app::SvgKnob *widget) {
	log_make_element("SvgKnob", widget->paramId);

	Knob element{};
	element.DefaultValue = getScaledDefaultValue(widget);

	// Hack to support BefacoTinyKnobs:
	// The main SVG is just the dot, either BefacoTinyPointWhite or BefacoTinyPointBlack.
	// The bg SVG has the knob color: red, white, lightGray, darkGray, or black.
	// Therefore we can't ignore the bg SVG since it determines the knob color.
	// The bg SVG is a child of the FramebufferWidget (fb), but it's not part of the SvgKnob class.
	// In MM, we merged the Point (dot) and bg images and saved that in the bg PNG.
	// The Point PNG is not drawn, but it must have the right size because that's used to center the jack.
	//
	// TODO: consider using a concept make_element like:
	// requires derived_form<T, SvgKnob> && !same_as<T, SvgKnob> && requires(...){w->bg->svg->filename;}
	//
	// This does not work for Rogan knobs
	auto find_inner_svg_widget = [](rack::widget::FramebufferWidget *fb) {
		for (auto child : fb->children) {
			if (auto svgw = dynamic_cast<rack::widget::SvgWidget *>(child)) {
				if (!svgw->box.size.isZero() && svgw->box.size.isFinite()) {
					if (svgw->svg && svgw->svg->filename.size() > 0) {
						return std::string_view{svgw->svg->filename};
					}
				}
			}
		}
		return std::string_view{""};
	};

	if (auto inner_img = find_inner_svg_widget(widget->fb); inner_img.size() > 0) {
		log_make_element_notes("...found SvgWidget child of fb with an SVG %s\n", inner_img.data());
		element.image = inner_img;

	} else if (widget->sw->svg->filename.size() && widget->sw->box.size.isFinite() && !widget->sw->box.size.isZero()) {
		log_make_element_notes("...use sw->svg %s\n", widget->sw->svg->filename.data());
		element.image = widget->sw->svg->filename;

	} else {
		pr_err("SvgKnob with no sw->svg or inner child of fb\n");
	}

	return element;
}

//
// Sliders
//

Element make_element(rack::app::SliderKnob *widget) {
	log_make_element("SliderKnob", widget->paramId);

	Slider element{};
	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

static Element make_slideswitch(rack::app::SvgSlider *widget) {
	SlideSwitch element{};

	if (widget->background->svg->filename.length()) {
		element.image = widget->background->svg->filename;
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

Element make_element(rack::app::SvgSlider *widget) {

	if (auto pq = widget->getParamQuantity(); pq && pq->snapEnabled) {
		log_make_element("SvgSlider switch", widget->paramId);
		return make_slideswitch(widget);
	}

	else
	{
		log_make_element("SvgSlider slider", widget->paramId);

		Slider element{};
		element.DefaultValue = getScaledDefaultValue(widget);
		element.image_handle = widget->handle->svg->filename;

		if (widget->background->svg->filename.length()) {
			element.image = widget->background->svg->filename;
			// Modify the widget's box to match the background
			widget->box.pos = widget->box.pos + widget->background->box.pos;
		}

		return element;
	}
}

Element make_element(rack::app::SvgSlider *widget, rack::app::MultiLightWidget *light) {
	log_make_element("SvgSlider, Light", widget->paramId);

	SliderLight element;
	element.DefaultValue = getScaledDefaultValue(widget);
	element.image_handle = widget->handle->svg->filename;
	auto color = light->baseColors.size() ? light->baseColors[0] : light->color;
	element.color = RGB565{color.r, color.g, color.b};

	if (widget->background->svg->filename.length()) {
		element.image = widget->background->svg->filename;
	}

	return element;
}

//
// Switch/Button
//

static MomentaryButton make_momentary(rack::app::SvgSwitch *widget) {
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

static SlideSwitch make_slideswitch(rack::app::SvgSwitch *widget) {
	SlideSwitch element{};

	if (auto pq = widget->getParamQuantity(); pq) {
		// Set the number of positions based on the max/min values set in configSwitch or configParam
		element.num_pos = pq->maxValue - pq->minValue + 1;

		if (element.num_pos < 2 || element.num_pos > element.pos_names.size()) {
			pr_warn("Warning: SvgSwitch as SlideSwitch (max - min + 1) is %d, but must be 2 - 8\n", element.num_pos);
			element.num_pos = std::clamp<size_t>(widget->frames.size(), 2, element.pos_names.size());
		}

		for (auto i = 0u; i < std::min<size_t>(element.num_pos, pq->labels.size()); i++) {
			element.pos_names[i] = pq->labels[i];
		}

	} else {
		// Gracefully handle an unconfigured param:
		element.num_pos = std::clamp<size_t>(widget->frames.size(), 2, element.pos_names.size());
		pr_warn("Warning: SvgSwitch as SlideSwitch not configured with configParam or configSwitch\n");
	}

	element.image_handle = "no-image";
	element.image = widget->frames[0]->filename;
	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

static FlipSwitch make_flipswitch(rack::app::SvgSwitch *widget) {
	FlipSwitch element{};

	if (auto pq = widget->getParamQuantity(); pq) {
		// Set the number of positions based on the max/min values set in configSwitch or configParam
		element.num_pos = pq->maxValue - pq->minValue + 1;

		if (element.num_pos < 2 || element.num_pos > FlipSwitch::MaxPositions) {
			pr_warn("Warning: SvgSwitch (max - min + 1) is %d, but must be 2 - 4\n", element.num_pos);
			element.num_pos = std::clamp<size_t>(widget->frames.size(), 2, FlipSwitch::MaxPositions);
		}

		for (auto i = 0u; i < std::min<size_t>(element.num_pos, pq->labels.size()); i++) {
			element.pos_names[i] = pq->labels[i];
		}
	} else {
		// Gracefully handle an unconfigured param:
		element.num_pos = std::clamp<size_t>(widget->frames.size(), 2, element.pos_names.size());
		pr_warn("Warning: SvgSwitch not configured with configParam or configSwitch\n");
	}

	for (unsigned i = 0; i < std::min<size_t>(FlipSwitch::MaxPositions, widget->frames.size()); i++) {
		element.frames[i] = widget->frames[i]->filename;
	}

	element.DefaultValue = getScaledDefaultValue(widget);
	return element;
}

Element make_element(rack::app::SvgSwitch *widget) {

	bool momentary = widget->momentary;
	if (widget->frames.size() >= 3) {
		// Handle custom widgets that are not really momentary, like Befaco StereoStrip Mute switch
		momentary = false;
	}

	if (momentary) {
		log_make_element("SvgSwitch mom", widget->paramId);
		return make_momentary(widget);
	} else {
		if (auto pq = widget->getParamQuantity(); pq) {
			if ((pq->maxValue - pq->minValue + 1) > FlipSwitch::MaxPositions) {
				log_make_element("SvgSwitch slide", widget->paramId);
				return make_slideswitch(widget);
			}
		}
		log_make_element("SvgSwitch flip", widget->paramId);
		return make_flipswitch(widget);
	}
}

static Element make_momentary_rgb(std::string_view image) {
	MomentaryButtonRGB element;
	element.image = image;
	log_make_element_notes("make_momentary_rgb()", "");
	return element;
}

static Element make_latching_rgb(std::string_view image, LatchingButton::State_t defaultValue) {
	pr_warn("Latching RGB button not supported yet. Using momentary\n");
	MomentaryButtonRGB element;
	element.image = image;
	log_make_element_notes("make_latching_rgb()", "");
	return element;
}

static Element make_momentary_mono(std::string_view image, NVGcolor c) {
	MomentaryButtonLight element;
	element.image = image;
	element.color = RGB565{c.r, c.g, c.b};
	log_make_element_notes("make_momentary_mono()", "");
	return element;
}

static Element make_latching_mono(std::string_view image, NVGcolor c, LatchingButton::State_t defaultValue) {
	LatchingButton element;
	element.image = image;
	element.color = RGB565{c.r, c.g, c.b};
	element.DefaultValue = defaultValue;
	log_make_element_notes("make_latching_mono()", "");
	return element;
}

Element make_element(rack::app::SvgSwitch *widget, rack::app::MultiLightWidget *light) {
	log_make_element("SvgSwitch, Light", widget->paramId);

	LatchingButton::State_t defaultValue =
		getScaledDefaultValue(widget) > 0.5f ? LatchingButton::State_t::UP : LatchingButton::State_t::DOWN;

	if (light->getNumColors() != 1 && light->getNumColors() != 3) {
		pr_warn("SvgSwitch with MultiLightWidget with %d colors: only 1 and 3 colors are supported.\n",
				light->getNumColors());
	}
	if (widget->frames.size() == 0) {
		pr_err("Error: SvgSwitch with no frames\n");
		widget->addFrame({});
	}

	// Treat 0, 1, or 2 lights as a mono light
	if (light->getNumColors() < 3) {

		auto c = light->baseColors[0];
		if (widget->momentary)
			return make_momentary_mono(widget->frames[0]->filename, c);
		else
			return make_latching_mono(widget->frames[0]->filename, c, defaultValue);

		// Treat 3 or more lights as an RGB light
	} else {
		if (widget->momentary)
			return make_momentary_rgb(widget->frames[0]->filename);
		else
			return make_latching_rgb(widget->frames[0]->filename, defaultValue);
	}
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

static Element make_mono_led_element(std::string_view image, rack::app::MultiLightWidget const *widget) {
	MonoLight element{};
	auto c = widget->baseColors[0];
	element.color = RGB565{c.r, c.g, c.b};
	element.image = image;
	return element;
}

static Element make_dual_led_element(std::string_view image, rack::app::MultiLightWidget const *widget) {
	DualLight element{};
	auto c1 = widget->baseColors[0];
	auto c2 = widget->baseColors[1];
	element.color = {RGB565{c1.r, c1.g, c1.b}, RGB565{c2.r, c2.g, c2.b}};
	element.image = image;
	return element;
}

static Element make_rgb_led_element(std::string_view image, rack::app::MultiLightWidget const *widget) {
	RgbLight element{};
	element.image = image;
	return element;
}

Element make_element(rack::app::MultiLightWidget *widget) {
	log_make_element("MultiLightWidget has #colors:", widget->getNumColors());

	auto image = get_led_image_by_size(widget);

	if (widget->getNumColors() == 1) {
		return make_mono_led_element(image, widget);

	} else if (widget->getNumColors() == 2) {
		return make_dual_led_element(image, widget);

	} else if (widget->getNumColors() == 3) {
		return make_rgb_led_element(image, widget);

	} else {
		pr_warn("Light widget not handled (%d colors)\n", widget->getNumColors());
		return NullElement{};
	}
}

Element make_element(rack::app::MultiLightWidget *widget, std::string_view image) {
	log_make_element("MultiLightWidget + image has #colors:", widget->getNumColors());

	if (widget->getNumColors() <= 0) {
		pr_warn("SVGLight widget has no colors, skipping\n");
		return NullElement{};

	} else if (widget->getNumColors() == 1) {
		return make_mono_led_element(image, widget);

	} else if (widget->getNumColors() == 2) {
		return make_dual_led_element(image, widget);

	} else {
		if (widget->getNumColors() > 3)
			pr_warn("SVGLight widget has %d colors, limiting to 3\n", widget->getNumColors());

		return make_rgb_led_element(image, widget);
	}
}

//
// Image Elements
//

Element make_element(rack::widget::SvgWidget *widget) {
	if (widget->svg->filename.size()) {
		pr_trace("SvgWidget: using image as a ImageElement\n");
		ImageElement element{};
		element.image = widget->svg->filename;
		return element;

	} else {
		pr_warn("Unknown SvgWidget without an svg\n");
		ImageElement element{};
		element.width_mm = to_mm(widget->box.size.x);
		element.height_mm = to_mm(widget->box.size.y);
		return element;
	}
}

Element make_element(rack::app::SvgButton *widget) {
	return make_element(widget->sw);
}

//
// Not supported
//

Element make_element(rack::app::SvgScrew *widget) {
	// pr_trace("make_element(SvgScrew): skip\n");
	return NullElement{};
}

Element make_element(rack::widget::Widget *widget) {
	pr_trace("Unknown widget at %f, %f: skip\n", widget->getBox().pos.x, widget->getBox().pos.y);
	return NullElement{};
}

Element make_element(rack::app::ParamWidget *widget) {
	pr_warn("ParamWidget (param id %d) without an SVG, using a blank ParamElement\n", widget->paramId);
	ParamElement element{};
	element.width_mm = to_mm(widget->box.size.x);
	element.height_mm = to_mm(widget->box.size.y);
	return element;
}

static float getScaledDefaultValue(rack::app::ParamWidget *widget) {
	if (!widget)
		return 0;
	auto pq = widget->getParamQuantity();
	float defaultValue = pq ? pq->toScaled(pq->getDefaultValue()) : 0.f;
	return defaultValue;
}

} // namespace MetaModule
