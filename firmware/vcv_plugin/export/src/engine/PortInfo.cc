#include <engine/PortInfo.hpp>

namespace rack::engine
{

std::string PortInfo::getName() {
	return name;
}

std::string PortInfo::getFullName() {
	return name;
}

std::string PortInfo::getDescription() {
	return description;
}

} // namespace rack::engine
