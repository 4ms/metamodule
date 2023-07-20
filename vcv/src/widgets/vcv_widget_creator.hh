#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "vcv_creation_context.hh"
#include "widgets/4ms/4ms_widgets_implementation.hh"

namespace MetaModule::VCVImplementation::Widget
{

inline void do_create(BaseElement element, const ElementCount::Indices &, const WidgetContext_t &) {
	// Default: do nothing
	// FIXME: Maybe this should be replaced with more specific fallbacks
	printf("Widget not found\n");
}

} // namespace MetaModule::VCVImplementation::Widget

namespace MetaModule
{

template<typename INFO>
struct VCVWidgetCreator {

	VCVWidgetCreator(rack::ModuleWidget *module_widget, rack::Module *module)
		: context{module_widget, module} {
	}

	template<typename T>
	void create(const T &element) {
		// forward to implementation together with current context
		if (auto indices = ElementCount::get_indices<INFO>(element)) {
			VCVImplementation::Widget::do_create(element, indices.value(), context);
		}
	}

private:
	WidgetContext_t context;
};

} // namespace MetaModule
