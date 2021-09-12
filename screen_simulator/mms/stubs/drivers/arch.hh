#ifndef _DRIVERS_ARCH_HH
#define _DRIVERS_ARCH_HH

namespace mdrivlib
{
enum Targets {
	simulator,
	stm32mp1_ca7,
};

constexpr bool TargetIsFound = true;
constexpr auto TargetName = mdrivlib::Targets::simulator;
} // namespace mdrivlib

#define __DSB()

#endif
