#include "../../internal/make_element.hh"
#include "CoreModules/elements/units.hh"
#include "console/pr_dbg.hh"
#include "make_element_names.hh"
#include <app/ModuleWidget.hpp>

namespace MetaModule
{

struct ModuleWidgetAdaptor {

	static constexpr inline bool LogWidgetNames = false;

	using WidgetType = std::variant<rack::app::ParamWidget *,
									rack::app::PortWidget *,
									rack::app::ModuleLightWidget *,
									rack::widget::Widget *>;

	std::vector<std::tuple<MetaModule::Element, ElementCount::Indices, WidgetType>> elem_idx;

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

			ElementCount::Indices indices = clear();
			indices.param_idx = widget->paramId;
			elem_idx.emplace_back(element, indices, widget);

			log_widget("param", indices.param_idx, widget, element);
		} else
			pr_err("Error: can't add a null ParamWidget\n");
	}

	template<typename PortWidgetT>
	void addInput(PortWidgetT *widget) requires(std::derived_from<PortWidgetT, rack::app::PortWidget>)
	{
		if (widget) {
			Element element = make_element(widget);

			ElementCount::Indices indices = clear();
			indices.input_idx = widget->portId;
			elem_idx.emplace_back(element, indices, widget);

			log_widget("input", indices.input_idx, widget, element);
		} else
			pr_err("Error: can't add a null input PortWidget\n");
	}

	template<typename PortWidgetT>
	void addOutput(PortWidgetT *widget) requires(std::derived_from<PortWidgetT, rack::app::PortWidget>)
	{
		if (widget) {
			Element element = make_element(widget);

			ElementCount::Indices indices = clear();
			indices.output_idx = widget->portId;
			elem_idx.emplace_back(element, indices, widget);

			log_widget("output", indices.output_idx, widget, element);
		} else
			pr_err("Error: can't add a null output PortWidget\n");
	}

	template<typename LightWidgetT>
	void addLight(LightWidgetT *widget) requires(std::derived_from<LightWidgetT, rack::app::ModuleLightWidget>)
	{
		if (widget) {
			Element element = make_element(widget);

			ElementCount::Indices indices = clear();
			indices.light_idx = widget->firstLightId;
			elem_idx.emplace_back(element, indices, widget);

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

			ElementCount::Indices indices = clear();
			indices.light_idx = light->firstLightId;
			indices.param_idx = widget->paramId;
			elem_idx.emplace_back(element, indices, widget);

			log_widget("light param: param", indices.param_idx, widget, element);
			log_widget("light param: light", indices.light_idx, widget, element);
		} else
			pr_err("Error: can't add a null Light Param widget\n");
	}

	void addSvgLight(rack::app::ModuleLightWidget *widget, std::string_view image) {
		if (widget) {
			Element element = make_element(widget, image);

			ElementCount::Indices indices = clear();
			indices.light_idx = widget->firstLightId;
			elem_idx.emplace_back(element, indices, widget);

			log_widget("SvgLight:", indices.light_idx, widget, element);
		} else
			pr_err("Error: can't add a null Light Param widget\n");
	}

	void addImage(rack::widget::SvgWidget *widget) {
		if (widget) {
			Element element = make_element(widget);

			ElementCount::Indices indices = clear();
			elem_idx.emplace_back(element, indices, widget);

			log_widget("SvgWidget (image):", 0, widget, element);
		} else
			pr_err("Error: can't add a null SvgWidget\n");
	}

	void addTextDisplay(MetaModule::VCVTextDisplay *widget) {
		if (widget) {
			if (widget->firstLightId >= 0) {
				Element element = make_element(widget);

				ElementCount::Indices indices = clear();
				indices.light_idx = widget->firstLightId;
				elem_idx.emplace_back(element, indices, widget);

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

			ElementCount::Indices indices = clear();
			indices.light_idx = graphic_display_idx;
			elem_idx.emplace_back(element, indices, mw);

			pr_trace("Widget with size %g x %g has a custom draw() or drawLayer()\n", mw->box.size.x, mw->box.size.y);

		} else {
			// Set element's box a 0 size if it has no custom draw
			// This will ensure we call step() but don't allocate a pixel buffer

			rack::widget::Widget zero_size_widget;
			zero_size_widget.box = {{0, 0}, {0, 0}};

			ElementCount::Indices indices = clear();
			indices.light_idx = graphic_display_idx;

			// Assign a zero sized box
			assign_element_fields(&zero_size_widget, "", element);
			// nullptr ==> Do not call assign_element_fields later, we already did it
			elem_idx.emplace_back(element, indices, (rack::widget::Widget *)nullptr);

			pr_trace(
				"Widget with size %g x %g has no draw() or drawLayer() override\n", mw->box.size.x, mw->box.size.y);
		}

		log_widget("ModuleWidget:", graphic_display_idx, mw, element);
	}

	void addGraphicDisplay(int graphic_display_idx, int first_graphic_idx, rack::widget::Widget *widget) {
		if (widget) {
			Element element = DynamicGraphicDisplay{};

			if (widget->box.size.y > 400 || widget->box.size.y == 0) {
				pr_trace("Widget graph_disp_idx %d box size.y invalid: %f\n", graphic_display_idx, widget->box.size.y);
				widget->box.size.y = widget->parent->box.size.y - widget->box.pos.y;
			}
			if (widget->box.size.x > 400 || widget->box.size.x == 0) {
				pr_trace("Widget graph_disp_idx %d box size.x invalid: %f\n", graphic_display_idx, widget->box.size.x);
				widget->box.size.x = widget->parent->box.size.x - widget->box.pos.x;
			}

			auto &name = temp_names.emplace_back("Display " + std::to_string(graphic_display_idx - first_graphic_idx));
			// Set the name now, because it won't be set later
			assign_element_fields(widget, name, element);

			ElementCount::Indices indices = clear();
			indices.light_idx = graphic_display_idx;
			elem_idx.emplace_back(element, indices, widget);

			log_widget("Widget (as Graphic Display buffer):", graphic_display_idx, widget, element);
		}
	}

	void populate_elements_indices(std::vector<MetaModule::Element> &elements,
								   std::vector<ElementCount::Indices> &indices) {

		for (auto &[element, idx, widget] : elem_idx) {
			std::visit(overloaded{
						   [&](rack::app::ParamWidget *w) {
							   assign_element_fields(w, getParamName(w->module, w->paramId), element);
						   },
						   [&](rack::app::PortWidget *w) {
							   if (w->type == rack::engine::Port::Type::INPUT)
								   assign_element_fields(w, getInputName(w->module, w->portId), element);

							   else if (w->type == rack::engine::Port::Type::OUTPUT)
								   assign_element_fields(w, getOutputName(w->module, w->portId), element);
						   },
						   [&](rack::app::ModuleLightWidget *w) {
							   assign_element_fields(w, getLightName(w->module, w->firstLightId), element);
						   },
						   [&](rack::widget::Widget *w) {
							   if (w) {
								   // Don't change the name: Graphic displays already set their name and all others have no name
								   assign_element_fields(w, std::nullopt, element);
							   }
						   },
					   },
					   widget);
		}

		// populate_sorted_elements_indices(elem_idx, elements, indices);
		std::sort(elem_idx.begin(), elem_idx.end(), [](auto const &a, auto const &b) {
			auto const &aidx = std::get<1>(a);
			auto const &bidx = std::get<1>(b);

			if (aidx.param_idx < bidx.param_idx)
				return true;
			else if (aidx.param_idx > bidx.param_idx)
				return false;

			else if (aidx.input_idx < bidx.input_idx)
				return true;
			else if (aidx.input_idx > bidx.input_idx)
				return false;

			else if (aidx.output_idx < bidx.output_idx)
				return true;
			else if (aidx.output_idx > bidx.output_idx)
				return false;

			else if (aidx.light_idx < bidx.light_idx)
				return true;

			else
				return false;
		});

		elements.clear();
		indices.clear();

		auto num_elems = elem_idx.size();
		elements.reserve(num_elems);
		indices.reserve(num_elems);

		for (auto &elemidx : elem_idx) {
			elements.push_back(std::get<0>(elemidx));
			indices.push_back(std::get<1>(elemidx));
		}
	}

	static void
	assign_element_fields(rack::widget::Widget const *widget, std::optional<std::string_view> name, Element &element) {
		std::visit(
			[&name, &widget](BaseElement &el) {
				el.x_mm = to_mm(widget->box.pos.x);
				el.y_mm = to_mm(widget->box.pos.y);
				el.width_mm = to_mm(widget->box.size.x);
				el.height_mm = to_mm(widget->box.size.y);
				el.coords = Coords::TopLeft;

				if (name) {
					el.short_name = *name;
					el.long_name = *name;
				}
			},
			element);
	}
};

} // namespace MetaModule
