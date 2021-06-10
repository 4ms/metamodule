#pragma once

namespace mdrivlib
{
enum class SupportedTargets {
	stm32mp1_ca7,
	TestProject,
};
namespace testproject
{
constexpr bool TARGET_FOUND = true;
constexpr auto TYPE = SupportedTargets::TestProject;
} // namespace testproject
namespace target = mdrivlib::testproject;
} // namespace mdrivlib
namespace target = mdrivlib::testproject;
