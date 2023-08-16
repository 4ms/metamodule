#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

struct CKSSRot;

namespace rack
{

template<>
struct ElementConvert<::CKSSRot> {
	using ElementType = MetaModule::CKSSRot;
};

} // namespace rack
