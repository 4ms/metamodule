#include "assign_element_fields.hh"
#include "console/pr_dbg.hh"
#include "make_element.hh"
#include "make_element_names.hh"
#include <app/ModuleWidget.hpp>

namespace MetaModule
{

inline void place_at(std::vector<Element> &elements, int id, const Element &el);

template<typename ParamT>
void addParamImpl(rack::app::ModuleWidget *mw, ParamT *widget)
//TODO: requires derives from ParamWidget
{
	if (widget) {
		widget->element = make_element(widget, {});
		assign_element_fields(widget, getParamName(widget->module, widget->paramId));
		place_at(mw->paramElements, widget->paramId, widget->element);
		mw->Widget::addChild(widget);
		pr_dbg("Add param widget '%s' to MW\n\n", base_element(widget->element).short_name.data());
	} else
		pr_err("Error: can't add a null ParamWidget\n");
}

template<typename PortWidgetT>
void addInputImpl(rack::app::ModuleWidget *mw, PortWidgetT *widget)
//TODO: requires derives from PortWidget
{
	if (widget) {
		widget->element = make_element(widget, {});
		assign_element_fields(widget, getInputName(widget->module, widget->portId));
		place_at(mw->inputElements, widget->portId, widget->element);
		mw->Widget::addChild(widget);
		pr_dbg("Added input widget '%s' to MW\n\n", base_element(widget->element).short_name.data());
	} else
		pr_err("Error: can't add a null input PortWidget\n");
}

template<typename PortWidgetT>
void addOutputImpl(rack::app::ModuleWidget *mw, PortWidgetT *widget)
//TODO: requires derives from PortWidget
{
	if (widget) {
		widget->element = make_element(widget, {});
		assign_element_fields(widget, getOutputName(widget->module, widget->portId));
		place_at(mw->outputElements, widget->portId, widget->element);
		mw->Widget::addChild(widget);
		pr_dbg("Added output widget '%s' to MW\n\n", base_element(widget->element).short_name.data());
	} else
		pr_err("Error: can't add a null output PortWidget\n");
}

template<typename LightWidgetT>
void addLightImpl(rack::app::ModuleWidget *mw, LightWidgetT *widget)
//TODO: requires derives from ModuleLightWidget
{
	if (widget) {
		widget->element = make_element(widget, {});
		assign_element_fields(widget, getLightName(widget->module, widget->firstLightId));
		place_at(mw->lightElements, widget->firstLightId, widget->element);
		mw->Widget::addChild(widget);
		pr_dbg("Added light widget '%s' to MW\n\n", base_element(widget->element).short_name.data());
	} else
		pr_err("Error: can't add a null Light\n");
}

inline void
addLightSwitchImpl(rack::app::ModuleWidget *mw, rack::app::SvgSwitch *widget, rack::app::ModuleLightWidget *light) {
	if (widget) {
		widget->element = make_button_light(widget, light);
		assign_element_fields(widget, getParamName(widget->module, widget->paramId));
		place_at(mw->paramElements, widget->paramId, widget->element);
		mw->Widget::addChild(widget);
		pr_dbg("Add light button widget '%s' to MW\n\n", base_element(widget->element).short_name.data());
	} else
		pr_err("Error: can't add a null Light Button widget\n");
}

// Helpers

inline void place_at(std::vector<Element> &elements, int id, const Element &el) {
	if (id < 0)
		return;

	// Make sure vector is big enough, resize if not
	if (id >= (int)elements.size())
		elements.resize(id + 1);

	elements[id] = el;
}

} // namespace MetaModule
