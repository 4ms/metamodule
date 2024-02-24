#pragma once
#include "VCV_adaptor/plugin/Model.hpp"
#include <vector>

namespace rack::plugin
{

struct Plugin {
	std::vector<Model *> models;

	void addModel(Model *model) {
		models.push_back(model);
	}
};

} // namespace rack::plugin
