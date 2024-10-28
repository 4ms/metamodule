#include "../../internal/make_element.hh"
#include "CoreModules/elements/element_sort.hh"
#include "CoreModules/elements/units.hh"
#include "console/pr_dbg.hh"
#include "make_element_names.hh"
#include <app/ModuleWidget.hpp>

namespace MetaModule
{

struct ModuleWidgetAdaptor {

	static constexpr inline bool LogWidgetNames = false;

	std::vector<std::pair<MetaModule::Element, ElementCount::Indices>> elem_idx;

	ElementCount::Indices clear() {
		auto None = ElementCount::Indices::NoElementMarker;
		return {None, None, None, None};
	}

	void log_widget(std::string_view type, unsigned index, rack::widget::Widget const *widget, Element const &element) {
		if constexpr (LogWidgetNames) {
			pr_trace("Add %.*s #%d '%.*s' to ModuleWidget\n\n",
					 type.size(),
					 type.data(),
					 index,
					 base_element(element).short_name.size(),
					 base_element(element).short_name.data());
		}
	}

	template<typename ParamWidgetT>
	void addParam(ParamWidgetT *widget) requires(std::derived_from<ParamWidgetT, rack::app::ParamWidget>)
	{
		if (widget) {
			Element element = make_element(widget);
			assign_element_fields(widget, getParamName(widget->module, widget->paramId), element);

			ElementCount::Indices indices = clear();
			indices.param_idx = widget->paramId;
			elem_idx.emplace_back(element, indices);

			log_widget("param", indices.param_idx, widget, element);
		} else
			pr_err("Error: can't add a null ParamWidget\n");
	}

	template<typename PortWidgetT>
	void addInput(PortWidgetT *widget) requires(std::derived_from<PortWidgetT, rack::app::PortWidget>)
	{
		if (widget) {
			Element element = make_element(widget);
			assign_element_fields(widget, getInputName(widget->module, widget->portId), element);

			ElementCount::Indices indices = clear();
			indices.input_idx = widget->portId;
			elem_idx.emplace_back(element, indices);

			log_widget("input", indices.input_idx, widget, element);
		} else
			pr_err("Error: can't add a null input PortWidget\n");
	}

	template<typename PortWidgetT>
	void addOutput(PortWidgetT *widget) requires(std::derived_from<PortWidgetT, rack::app::PortWidget>)
	{
		if (widget) {
			Element element = make_element(widget);
			assign_element_fields(widget, getOutputName(widget->module, widget->portId), element);

			ElementCount::Indices indices = clear();
			indices.output_idx = widget->portId;
			elem_idx.emplace_back(element, indices);

			log_widget("output", indices.output_idx, widget, element);
		} else
			pr_err("Error: can't add a null output PortWidget\n");
	}

	template<typename LightWidgetT>
	void addLight(LightWidgetT *widget) requires(std::derived_from<LightWidgetT, rack::app::ModuleLightWidget>)
	{
		if (widget) {
			Element element = make_element(widget);
			assign_element_fields(widget, getLightName(widget->module, widget->firstLightId), element);

			ElementCount::Indices indices = clear();
			indices.light_idx = widget->firstLightId;
			elem_idx.emplace_back(element, indices);

			log_widget("light", indices.light_idx, widget, element);
		} else
			pr_err("Error: can't add a null Light\n");
	}

	template<typename ParamWidgetT>
	void addLightParam(ParamWidgetT *widget, rack::app::ModuleLightWidget *light)
		requires(std::derived_from<ParamWidgetT, rack::app::ParamWidget>)
	{
		if (widget) {
			Element element = make_element(widget, light);
			assign_element_fields(widget, getParamName(widget->module, widget->paramId), element);

			ElementCount::Indices indices = clear();
			indices.light_idx = light->firstLightId;
			indices.param_idx = widget->paramId;
			elem_idx.emplace_back(element, indices);

			log_widget("light param: param", indices.param_idx, widget, element);
			log_widget("light param: light", indices.light_idx, widget, element);
		} else
			pr_err("Error: can't add a null Light Param widget\n");
	}

	void addSvgLight(rack::app::ModuleLightWidget *widget, std::string_view image) {
		if (widget) {
			Element element = make_element(widget, image);
			assign_element_fields(widget, getLightName(widget->module, widget->firstLightId), element);

			ElementCount::Indices indices = clear();
			indices.light_idx = widget->firstLightId;
			elem_idx.emplace_back(element, indices);

			log_widget("SvgLight:", indices.light_idx, widget, element);
		} else
			pr_err("Error: can't add a null Light Param widget\n");
	}

	void addImage(rack::widget::SvgWidget *widget) {
		if (widget) {
			Element element = make_element(widget);
			assign_element_fields(widget, "", element);

			ElementCount::Indices indices = clear();
			elem_idx.emplace_back(element, indices);

			log_widget("SvgWidget (image):", 0, widget, element);
		} else
			pr_err("Error: can't add a null SvgWidget\n");
	}

	void addTextDisplay(MetaModule::VCVTextDisplay *widget) {
		if (widget) {
			if (widget->firstLightId >= 0) {
				Element element = make_element(widget);
				assign_element_fields(widget, "", element);

				ElementCount::Indices indices = clear();
				indices.light_idx = widget->firstLightId;
				elem_idx.emplace_back(element, indices);

				log_widget("VCVTextDisplay:", widget->firstLightId, widget, element);
			} else {
				pr_err("Error: VCVTextDisplay needs a non-negative firstLightId\n");
			}
		} else
			pr_err("Error: can't add a null VCVTextDisplay\n");
	}

	void populate_elements_indices(std::vector<MetaModule::Element> &elements,
								   std::vector<ElementCount::Indices> &indices) {

		populate_sorted_elements_indices(elem_idx, elements, indices);
	}

	static void assign_element_fields(rack::widget::Widget *widget, std::string_view name, Element &element) {
		std::visit(
			[&name, &widget](BaseElement &el) {
				el.x_mm = to_mm(widget->box.pos.x);
				el.y_mm = to_mm(widget->box.pos.y);
				el.width_mm = to_mm(widget->box.size.x);
				el.height_mm = to_mm(widget->box.size.y);
				el.coords = Coords::TopLeft;
				el.short_name = name;
				el.long_name = name;
			},
			element);
	}
};

} // namespace MetaModule
