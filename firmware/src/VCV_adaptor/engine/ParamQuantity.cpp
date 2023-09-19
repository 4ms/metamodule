#include "VCV_adaptor/engine/ParamQuantity.hpp"
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/engine/Param.hpp"
#include "VCV_adaptor/json.hpp"
#include <string>
#include <string_view>
#include <vector>

namespace rack::engine
{

void ParamQuantity::setImmediateValue(float displayValue) {
	module->params[paramId].setValue(displayValue);
}

} // namespace rack::engine
