#pragma once
#include <atomic>
#include <functional>
#include <type_traits>

#include "drivers/interrupt.hh"
#include "drivers/secondary_core_control.hh"
#include "drivers/stm32xx.h"

namespace MetaModule
{

// Synchronously run a function on Core 0 from Core 1, used to make sure
// SMP-using code runs on the core that drives Core 1 via SGI.
// Core 0 must call init() before any dispatches occur from Core 1.
struct RunOnCore0 {
	static constexpr IRQn_Type DispatchIRQn = SGI5_IRQn;

	static inline std::function<void()> work;
	static inline std::atomic<bool> done{false};

	static void init() {
		mdrivlib::InterruptManager::register_and_start_isr(DispatchIRQn, 0, 0, []() {
			if (work)
				work();
			done.store(true, std::memory_order_release);
		});
	}

	static bool is_core0() {
		return (__get_MPIDR() & 0b1) == 0;
	}

	template<typename Fn>
	static auto run(Fn fn) -> std::invoke_result_t<Fn> {
		using R = std::invoke_result_t<Fn>;

		if (is_core0())
			return fn();

		if constexpr (std::is_void_v<R>) {
			work = std::move(fn);
			done.store(false, std::memory_order_release);
			mdrivlib::MainCore::send_sgi(DispatchIRQn);
			while (!done.load(std::memory_order_acquire))
				;
		} else {
			R result{};
			work = [&]() {
				result = fn();
			};
			done.store(false, std::memory_order_release);
			mdrivlib::MainCore::send_sgi(DispatchIRQn);
			while (!done.load(std::memory_order_acquire))
				;
			return result;
		}
	}
};

} // namespace MetaModule
