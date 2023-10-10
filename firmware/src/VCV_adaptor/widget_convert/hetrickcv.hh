#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

struct CKSSRot;
struct HCVThemedRogan;

namespace rack
{

template<>
struct ElementConvert<::CKSSRot> {
	using ElementType = MetaModule::CKSSRot;
};

template<>
struct ElementConvert<HCVThemedRogan> {
	using ElementType = MetaModule::Rogan1PRed;
};

} // namespace rack
