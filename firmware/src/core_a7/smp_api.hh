#pragma once
#include <cstdint>

namespace SMPCommand
{
static constexpr uint32_t ReadPatchGuiElements = 1; // == SGI1_IRQn;
static constexpr uint32_t NewModuleList = 2;		// == SGI2_IRQn;
static constexpr uint32_t ProcessCables = 3;		// == SGI3_IRQn;
static constexpr uint32_t PlayModuleList = 4;		// == SGI4_IRQn;
} // namespace SMPCommand

namespace SMPRegister
{
enum : uint32_t {
	DoneZero,
	NumModulesInPatch,
};
} // namespace SMPRegister
