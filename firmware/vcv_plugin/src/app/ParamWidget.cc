#include <app/ParamWidget.hpp>
#include <engine/Module.hpp>

namespace rack::app
{

engine::ParamQuantity *ParamWidget::getParamQuantity() {
	if (!module)
		return nullptr;
	return module->getParamQuantity(paramId);
}

} // namespace rack::app
