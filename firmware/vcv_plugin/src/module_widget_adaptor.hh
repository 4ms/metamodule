#include "assign_element_fields.hh"
#include "console/pr_dbg.hh"
#include "make_element.hh"
#include "make_element_names.hh"
#include <app/ModuleWidget.hpp>

namespace MetaModule
{

struct ModuleWidgetAdaptor {

	ModuleWidgetAdaptor() {
		printf("ModuleWidgetAdaptor()\n");
	}
	~ModuleWidgetAdaptor() {
		printf("~ModuleWidgetAdaptor()\n");
	}

	std::vector<std::pair<MetaModule::Element, ElementCount::Indices>> elem_idx;

	void add_element(MetaModule::Element const &el, ElementCount::Indices &indices) {
		elem_idx.emplace_back(el, indices);
	}

	ElementCount::Indices clear() {
		auto None = ElementCount::Indices::NoElementMarker;
		return {None, None, None, None};
	}

	void log_widget(std::string_view type, unsigned index, rack::widget::Widget const *widget) {
		pr_trace("Add %.*s #%d '%.*s' to ModuleWidget\n\n",
				 type.size(),
				 type.data(),
				 index,
				 base_element(widget->element).short_name.size(),
				 base_element(widget->element).short_name.data());
	}

	template<typename ParamWidgetT>
	void addParam(ParamWidgetT *widget) requires(std::derived_from<ParamWidgetT, rack::app::ParamWidget>)
	{
		if (widget) {
			widget->element = make_element(widget);
			assign_element_fields(widget, getParamName(widget->module, widget->paramId));

			ElementCount::Indices indices = clear();
			indices.param_idx = widget->paramId;
			elem_idx.emplace_back(widget->element, indices);

			pr_dbg("Add param %d '%s' to MW\n\n", indices.param_idx, base_element(widget->element).short_name.data());
		} else
			pr_err("Error: can't add a null ParamWidget\n");
	}

	template<typename PortWidgetT>
	void addInput(PortWidgetT *widget)
	//TODO: requires derives from PortWidget
	{
		if (widget) {
			widget->element = make_element(widget);
			assign_element_fields(widget, getInputName(widget->module, widget->portId));

			ElementCount::Indices indices = clear();
			indices.input_idx = widget->portId;
			elem_idx.emplace_back(widget->element, indices);

			pr_dbg("Added input '%s' to MW\n\n", base_element(widget->element).short_name.data());
		} else
			pr_err("Error: can't add a null input PortWidget\n");
	}

	template<typename PortWidgetT>
	void addOutput(PortWidgetT *widget)
	//TODO: requires derives from PortWidget
	{
		if (widget) {
			widget->element = make_element(widget);
			assign_element_fields(widget, getOutputName(widget->module, widget->portId));

			ElementCount::Indices indices = clear();
			indices.output_idx = widget->portId;
			elem_idx.emplace_back(widget->element, indices);

			pr_dbg("Added output '%s' to MW\n\n", base_element(widget->element).short_name.data());
		} else
			pr_err("Error: can't add a null output PortWidget\n");
	}

	template<typename LightWidgetT>
	void addLight(LightWidgetT *widget)
	//TODO: requires derives from ModuleLightWidget
	{
		if (widget) {
			widget->element = make_element(widget);
			assign_element_fields(widget, getLightName(widget->module, widget->firstLightId));

			ElementCount::Indices indices = clear();
			indices.light_idx = widget->firstLightId;
			elem_idx.emplace_back(widget->element, indices);

			pr_dbg("Added light %d '%s' to MW\n\n", indices.light_idx, base_element(widget->element).short_name.data());
		} else
			pr_err("Error: can't add a null Light\n");
	}

	template<typename ParamWidgetT>
	inline void addLightParam(ParamWidgetT *widget, rack::app::ModuleLightWidget *light) {
		if (widget) {
			widget->element = make_element(widget, light);
			assign_element_fields(widget, getParamName(widget->module, widget->paramId));

			ElementCount::Indices indices = clear();
			indices.light_idx = light->firstLightId;
			indices.param_idx = widget->paramId;
			elem_idx.emplace_back(widget->element, indices);

			pr_dbg("Added light param widget '%s' (p:%d l:%d) to MW\n\n",
				   base_element(widget->element).short_name.data(),
		} else
			pr_err("Error: can't add a null Light Param widget\n");
	}

	void addSvgLight(rack::app::ModuleLightWidget *widget, std::string_view image) {
		if (widget) {
			widget->element = make_element(widget, image);
			assign_element_fields(widget, getParamName(widget->module, widget->firstLightId));

			ElementCount::Indices indices = clear();
			indices.light_idx = widget->firstLightId;
			elem_idx.emplace_back(widget->element, indices);

			log_widget("SvgLight:", indices.light_idx, widget);
		} else
			pr_err("Error: can't add a null Light Param widget\n");
	}

	void populate_elements_indices(std::vector<MetaModule::Element> &elements,
								   std::vector<ElementCount::Indices> &indices) {
		elements.clear();
		indices.clear();

		auto num_elems = elem_idx.size();
		elements.reserve(num_elems);
		indices.reserve(num_elems);

		for (auto &elemidx : elem_idx) {
			elements.push_back(elemidx.first);
			indices.push_back(elemidx.second);
		}
	}
};

} // namespace MetaModule
