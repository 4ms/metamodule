#pragma once
#include "vcv_creation_context.hh"
#include "base_modules_implemenation.hh"

namespace MetaModule::VCVImplementation::Module
{
	void do_config_element(BaseElement el, ModuleContext_t& context)
	{
		// Do nothing by default
		// FIXME: This should probably be replaced with more specific fallbacks
	};
}

namespace MetaModule
{

struct VCVModuleParamCreator {

	VCVModuleParamCreator(rack::Module *module)
		: context{module} {
	}

	template <typename ELEMENT>
	void config_element(ELEMENT element)
	{
		// forward to implementation togeher with current context
		// FIXME: do not allow implementation to freely alter the context but only change the context here
		VCVImplementation::Module::do_config_element(element, context);
	}

	
private:
	ModuleContext_t context;
};

} // namespace MetaModule
