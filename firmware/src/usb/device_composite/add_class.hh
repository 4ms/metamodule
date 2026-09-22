#pragma once
#include "console/pr_dbg.hh"
#include "device_composite/usbd_composite_builder.h"
#include "usbd_core.h"

namespace MetaModule::UsbComposite
{

// Add one class to the composite device, together with its interface ops.
//
// The two steps have conflicting requirements on pdev->classId, which is why
// they belong in one place:
//
//   USBD_RegisterClassComposite() stores the class at pdev->classId and then
//   advances classId to the next free slot -- that advance is how it knows
//   where to put the *next* class.
//
//   A class's RegisterInterface() stores its ops in pUserData[pdev->classId],
//   so it has to run with classId pointing back at the class just added.
//
// Doing the second without restoring afterwards makes the next class overwrite
// this one's slot, leaving a NULL entry below NumClasses -- which the device
// core walks without a NULL check when a host asks for a string descriptor.
template<typename RegisterInterfaceFn>
bool add_class(USBD_HandleTypeDef *pdev,
			   USBD_ClassTypeDef *pclass,
			   USBD_CompositeClassTypeDef classtype,
			   uint8_t *ep_addrs,
			   RegisterInterfaceFn &&register_interface) {

	if (USBD_RegisterClassComposite(pdev, pclass, classtype, ep_addrs) != USBD_OK) {
		pr_err("USB: failed to add class type %d to the composite device\n", static_cast<int>(classtype));
		return false;
	}

	const uint32_t next_free_slot = pdev->classId;

	pdev->classId = next_free_slot - 1; // the slot just filled
	register_interface();
	pdev->classId = next_free_slot; // where the next class goes

	return true;
}

} // namespace MetaModule::UsbComposite
