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

	std::deque<std::string> temp_names;

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

	void addModuleWidget(int graphic_display_idx, rack::app::ModuleWidget *mw) {
		bool has_custom_draw = true;

#if defined(__GNUC__) && !defined(__clang__)
		// See if the the Widget overrides draw() or drawLayer().
		// We will only allocate the module-sized pixel buffer if the module needs it.
		// This uses a GCC extension, so for simulator we just always assume
		// the ModuleWidget uses a custom draw().
		//
		// See https://gcc.gnu.org/onlinedocs/gcc/Bound-member-functions.html

		bool custom_draw_func =
			(void *)((*mw).*(&rack::app::ModuleWidget::draw)) != (void *)(&rack::app::ModuleWidget::draw);

		bool custom_drawLayer_func =
			(void *)((*mw).*(&rack::app::ModuleWidget::drawLayer)) != (void *)(&rack::app::ModuleWidget::drawLayer);

		bool derives_from_leddisplay = (dynamic_cast<rack::app::LedDisplay *>(mw) != nullptr);

		has_custom_draw = custom_draw_func || custom_drawLayer_func || derives_from_leddisplay;

		if (has_custom_draw) {
			pr_trace("ModuleWidget has_custom_draw\n");
		}

#endif

		Element element = DynamicGraphicDisplay{.full_module = true};

		if (has_custom_draw) {
			// Use a blank name for the entire module widget so that it doesn't show up in the element roller
			// Make sure widget width or height is not 0, or else it won't be drawn.
			mw->box.size.x = std::max(1.f, mw->box.size.x);
			mw->box.size.y = std::max(1.f, mw->box.size.y);
			assign_element_fields(mw, "", element);

			pr_trace("Widget with size %g x %g has a custom draw() or drawLayer()\n", mw->box.size.x, mw->box.size.y);

		} else {
			// Set element's box a 0 size if it has no custom draw
			// This will ensure we call step() but don't allocate a pixel buffer

			rack::widget::Widget zero_size_widget;
			zero_size_widget.box = {{0, 0}, {0, 0}};
			assign_element_fields(&zero_size_widget, "", element);

			pr_trace(
				"Widget with size %g x %g has no draw() or drawLayer() override\n", mw->box.size.x, mw->box.size.y);
		}

		ElementCount::Indices indices = clear();
		indices.light_idx = graphic_display_idx;
		elem_idx.emplace_back(element, indices);

		log_widget("ModuleWidget:", graphic_display_idx, mw, element);
	}

	void addGraphicDisplay(int graphic_display_idx, rack::widget::Widget *widget) {
		if (widget) {
			Element element = DynamicGraphicDisplay{};

			if (widget->box.size.y > 400 || widget->box.size.y == 0) {
				pr_trace("Widget graph_disp_idx %d @ %f box size y invalid: %f. Fix=>%f - @\n",
						 graphic_display_idx,
						 widget->box.pos.y,
						 widget->box.size.y,
						 widget->parent->box.size.y);
				widget->box.size.y = widget->parent->box.size.y - widget->box.pos.y;
			}
			if (widget->box.size.x > 400 || widget->box.size.x == 0) {
				pr_trace("Widget graph_disp_idx %d @ %f box size x invalid: %f. Fix=>%f - @\n",
						 graphic_display_idx,
						 widget->box.pos.x,
						 widget->box.size.x,
						 widget->parent->box.size.x);
				widget->box.size.x = widget->parent->box.size.x - widget->box.pos.x;
			}

			auto &name = temp_names.emplace_back("Display " + std::to_string(graphic_display_idx));
			assign_element_fields(widget, name, element);

			ElementCount::Indices indices = clear();
			indices.light_idx = graphic_display_idx;
			elem_idx.emplace_back(element, indices);

			log_widget("Widget (as Graphic Display buffer):", graphic_display_idx, widget, element);
		}
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
