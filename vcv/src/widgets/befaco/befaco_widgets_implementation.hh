#include "befaco_widgets.hh"
#include "../vcv_widget_context.hh"

namespace MetaModule::VCVImplementation::Widget
{

	void do_create(Davies1900hWhiteKnob el, WidgetContext_t& context) {
		auto corner_pos = rack::Vec(el.x_mm, el.y_mm);
		context.module_widget->addParam(rack::createParam<rack::Davies1900hWhiteKnob>(corner_pos, context.module, el.idx));
	}

	void do_create(Davies1900hRedKnob el, WidgetContext_t& context) {
		auto corner_pos = rack::Vec(el.x_mm, el.y_mm);
		context.module_widget->addParam(rack::createParam<rack::Davies1900hRedKnob>(corner_pos, context.module, el.idx));
	}

	void do_create(BefacoTinyKnobWhite el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobWhite>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(BefacoTinyKnobRed el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobRed>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(BefacoTinyKnobDarkGrey el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobDarkGrey>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(BefacoTinyKnobLightGrey el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobLightGrey>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(BefacoTinyKnobBlack el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoTinyKnobBlack>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(Davies1900hLargeGreyKnob el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::Davies1900hLargeGreyKnob>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(Davies1900hLightGreyKnob el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::Davies1900hLightGreyKnob>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(Davies1900hDarkGreyKnob el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::Davies1900hDarkGreyKnob>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(CKSSNarrow el, WidgetContext_t& context) {
		context.module_widget->addParam(rack::createParam<Befaco::CKSSNarrow>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(Crossfader el, WidgetContext_t& context) {
		context.module_widget->addParam(rack::createParam<Befaco::Crossfader>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(BefacoSwitchHorizontal el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoSwitchHorizontal>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(CKSSHoriz2 el, WidgetContext_t& context) {
		context.module_widget->addParam(rack::createParam<Befaco::CKSSHoriz2>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(CKSSVert7 el, WidgetContext_t& context) {
		context.module_widget->addParam(rack::createParam<Befaco::CKSSVert7>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(CKSSHoriz4 el, WidgetContext_t& context) {
		context.module_widget->addParam(rack::createParam<Befaco::CKSSHoriz4>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(CKSSNarrow3 el, WidgetContext_t& context) {
		context.module_widget->addParam(rack::createParam<Befaco::CKSSNarrow3>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(Davies1900hLargeLightGreyKnob el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::Davies1900hLargeLightGreyKnob>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	void do_create(BefacoSlidePotSmall el, WidgetContext_t& context) {
		context.module_widget->addParam(
			rack::createParam<Befaco::BefacoSlidePotSmall>(rack::Vec(el.x_mm, el.y_mm), context.module, el.idx));
	}

	static const inline auto BefacoJackOffsetFix = rack::Vec{-10, -10};

	void do_create(BefacoInputPort el, WidgetContext_t& context) {
		context.module_widget->addInput(rack::createInput<Befaco::BananutBlack>(
			rack::Vec(el.x_mm, el.y_mm).plus(BefacoJackOffsetFix), context.module, el.idx));
	}

	void do_create(BefacoOutputPort el, WidgetContext_t& context) {
		context.module_widget->addOutput(rack::createOutput<Befaco::BananutRed>(
			rack::Vec(el.x_mm, el.y_mm).plus(BefacoJackOffsetFix), context.module, el.idx));
	}

}