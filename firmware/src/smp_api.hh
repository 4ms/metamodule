#pragma once
#include <cstdint>

namespace SMPCommand
{
static constexpr uint32_t UpdateModule = 1; // == SGI1_IRQn;
static constexpr uint32_t SetParam = 2;		// == SGI2_IRQn;
static constexpr uint32_t CallFunction = 3; // == SGI3_IRQn;
} // namespace SMPCommand

namespace SMPRegister
{
static constexpr uint32_t DoneZero = 0;
static constexpr uint32_t ModuleID = 0;
static constexpr uint32_t ParamID = 0;
static constexpr uint32_t ParamVal = 0;
static constexpr uint32_t FunctionAddress = 0;
} // namespace SMPRegister
