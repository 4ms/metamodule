#ifndef _DRIVERS_ARCH_HH
#define _DRIVERS_ARCH_HH

namespace mdrivlib
{
enum SupportedTargets {
	simulator,
	stm32mp1_ca7,
};
}

namespace ScreenSimulator {
constexpr bool TARGET_FOUND = true;
constexpr auto TYPE = mdrivlib::SupportedTargets::simulator;
}
namespace target = ScreenSimulator;

#define __DSB()

#endif
