#include <LightInfo.hpp>

namespace rack::engine
{

std::string LightInfo::getName() {
	return name;
}

std::string LightInfo::getDescription() {
	return description;
}
} // namespace rack::engine
