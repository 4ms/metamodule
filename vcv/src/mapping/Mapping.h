#pragma once

#include "MappableObject.h"

struct Mapping {
	MappableObj src;
	MappableObj dst;
	float range_min = 0.f;
	float range_max = 1.f;
	std::string alias_name{""};

	void clear()
	{
		dst.moduleID = -1;
		src.moduleID = -1;
		dst.objID = -1;
		src.objID = -1;
		dst.objType = MappableObj::Type::None;
		src.objType = MappableObj::Type::None;
		range_min = 0.f;
		range_max = 1.f;
		alias_name = "";
	}
};