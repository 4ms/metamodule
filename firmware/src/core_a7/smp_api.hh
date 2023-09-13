#pragma once
#include <cstdint>

namespace SMPCommand
{
static constexpr uint32_t PlayOneModule = 1;  // == SGI1_IRQn;
static constexpr uint32_t NewModuleList = 2;  // == SGI2_IRQn;
static constexpr uint32_t CallFunction = 3;	  // == SGI3_IRQn;
static constexpr uint32_t PlayModuleList = 4; // == SGI4_IRQn;
} // namespace SMPCommand

namespace SMPRegister
{
enum : uint32_t {
	DoneZero,
	ModuleID,
	ParamID,
	ParamVal,
	FunctionAddress,
	NumModulesInPatch,
	UpdateModuleOffset,
	Unused,
};
} // namespace SMPRegister
