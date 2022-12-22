#pragma once
#include "drivers/hsem.hh"
#include "drivers/callable.hh"

template<unsigned SemID>
class SemaphoreActionOnUnlock {
	using CallbackT = Callback;

public:
	SemaphoreActionOnUnlock(CallbackT &&callback)
	{
		mdrivlib::HWSemaphore<SemID>::clear_ISR();
		mdrivlib::HWSemaphore<SemID>::disable_channel_ISR();
		mdrivlib::HWSemaphoreGlobalBase::register_channel_ISR<SemID>(std::forward<CallbackT>(callback));
		mdrivlib::HWSemaphore<SemID>::enable_channel_ISR();
	}

	~SemaphoreActionOnUnlock()
	{
		mdrivlib::HWSemaphore<SemID>::clear_ISR();
		mdrivlib::HWSemaphore<SemID>::disable_channel_ISR();
	}
};
