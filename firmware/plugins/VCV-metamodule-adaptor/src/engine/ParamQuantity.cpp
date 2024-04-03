#include <engine/Module.hpp>
#include <engine/ParamQuantity.hpp>

namespace rack::engine
{

void ParamQuantity::setImmediateValue(float value) {
	if (!module)
		return;
	if ((unsigned)paramId >= module->params.size())
		return;

	module->params[paramId].setValue(value);
}

float ParamQuantity::getImmediateValue() {
	if (!module)
		return 0.f;
	if ((unsigned)paramId >= module->params.size())
		return 0.f;

	return module->params[paramId].getValue();
}

} // namespace rack::engine
