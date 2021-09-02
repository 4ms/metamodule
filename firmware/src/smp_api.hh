#pragma once
#include <cstdint>

namespace SMPCommand
{
static constexpr uint32_t UpdateModule = 1;		   // == SGI1_IRQn;
static constexpr uint32_t SetParam = 2;			   // == SGI2_IRQn;
static constexpr uint32_t CallFunction = 3;		   // == SGI3_IRQn;
static constexpr uint32_t UpdateListOfModules = 4; // == SGI4_IRQn;
} // namespace SMPCommand

namespace SMPRegister
{
enum : uint32_t {
	DoneZero,
	ModuleID,
	ParamID,
	ParamVal,
	FunctionAddress,
	NumModules,
	IndexIncrement,
	Unused,
};
} // namespace SMPRegister
