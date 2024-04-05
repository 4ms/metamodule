#include "metamodule/make_element.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

//
// Jacks
//

Element make_element_output(rack::app::SvgPort const *widget, BaseElement b) {
	return JackOutput{b, widget->svg_filename};
}

Element make_element_input(rack::app::SvgPort const *widget, BaseElement b) {
	return JackInput{b, widget->svg_filename};
}

//
// Pots/Sliders
//

//TODO: don't set box size here
// either have dedicated function refresh_widget_size()
// or in SvgWidget::setSvg, set its parents size recursively (if not set)
Element make_element(rack::app::SvgKnob *widget, BaseElement b) {
	// SvgKnobs have a base SVG, and sometimes have a bg svg.
	// If there is a bg svg, then use its name.
	if (widget->fb->_bg && widget->fb->_bg->svg_filename.length()) {
		if (widget->box.size == rack::math::Vec{})
			widget->box.size = widget->fb->_bg->box.size;
		return Knob{b, widget->fb->_bg->svg_filename};
	} else
		return Knob{b, widget->svg_filename};
}

Element make_element_slideswitch(rack::app::SvgSlider const *widget, BaseElement b) {
	//Note: num_pos and labels are filled in later
	if (widget->background->svg_filename.length()) {
		return SlideSwitch{{b, widget->background->svg_filename}, 2, widget->handle->svg_filename};
	} else {
		return SlideSwitch{{b, widget->svg_filename}, 2, widget->handle->svg_filename};
	}
}

Element make_element(rack::app::SvgSlider const *widget, BaseElement b) {
	if (widget->background->svg_filename.length()) {
		return Slider{{b, widget->background->svg_filename}, widget->handle->svg_filename};
	} else {
		return Slider{{b, widget->svg_filename}, widget->handle->svg_filename};
	}
}

Element make_element(rack::componentlibrary::Rogan const *widget, BaseElement b) {
	// Rogan knobs have a Rogan::bg svg, Rogan::fg svg, SvgKnob::sw svg, and SvgWidget::svg.
	// The fg and base svgs are always the same color and thus are combined into one PNG for the MetaModule.
	// The bg svg is lighting effect gradient and can be ignored for MetaModule's low-res screen.
	// The SvgKnob::sw rotates
	// The SvgWidget::svg is apparently not used?
	if (widget->sw)
		return Knob{b, widget->sw->svg_filename};
	else
		return Knob{b, widget->svg_filename};
}

//
// Switch/Button
//

Element make_element(rack::app::SvgSwitch const *widget, BaseElement b) {
	if (widget->frames.size() == 3) {
		return FlipSwitch{{b}, 3, {widget->frames[0], widget->frames[1], widget->frames[2]}};

	} else if (widget->frames.size() == 2) {
		if (widget->momentary)
			return MomentaryButton{{b, widget->frames[0]}, widget->frames[1]};
		else
			return FlipSwitch{{b}, 2, {widget->frames[0], widget->frames[1]}};

	} else if (widget->frames.size() == 1) {
		return MomentaryButton{{b, widget->frames[0]}};

	} else {
		pr_warn("make_element(): Unknown SvgSwitch, frames size is not 1, 2 or 3\n");
		return NullElement{};
	}
}

//
// Not supported
//

Element make_element(rack::app::SvgScrew const *widget, BaseElement) {
	return NullElement{};
}

Element make_element(rack::widget::SvgWidget const *widget, BaseElement el) {
	printf("Unknown SvgWidget\n");
	return NullElement{};
}
} // namespace MetaModule
