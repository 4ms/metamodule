#pragma once
#include "vcv_widget_context.hh"
#include "widgets/4ms/4ms_widgets_implementation.hh"
#include "widgets/befaco/befaco_widgets_implementation.hh"


namespace MetaModule::VCVImplementation::Widget
{
	// Default: do nothing
	// FIXME: Maybe this should be replaced with more specific fallbacks
	void do_create(BaseElement element, WidgetContext_t&) {
	}
}

namespace MetaModule
{

struct VCVWidgetCreator {

	VCVWidgetCreator(rack::ModuleWidget *module_widget, rack::Module *module)
		: context(module_widget, module)
	{}

	template <typename T>
	void create(T element)
	{
		// forward to implementation togeher with current context
		// FIXME: do not allow implementation to freely alter the context but only change the context here
		VCVImplementation::Widget::do_create(element, context);
	}

private:
	WidgetContext_t context;
};

} // namespace MetaModule
