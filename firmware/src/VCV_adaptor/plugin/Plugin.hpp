#pragma once
#include "VCV_adaptor/plugin/Model.hpp"
#include <vector>

namespace rack::plugin
{

struct Plugin {
	std::string slug;

	// Owning pointers: TODO unique_ptr (or will that break the VCV API?)
	std::vector<Model *> models;

	void addModel(Model *model);
	~Plugin();
};

} // namespace rack::plugin
