#pragma once
#include <string>
#include <vector>

namespace MetaModule
{

struct BaseDynDraw {
	virtual ~BaseDynDraw() = default;
	virtual void draw() = 0;
};

} // namespace MetaModule
