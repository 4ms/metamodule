/* Author: Lennart@binarylabs.dev */

#pragma once

#include <cstdint>

namespace Framing
{

struct Configuration_t
{
	uint8_t start;
	uint8_t end;
	uint8_t escape;
};


}
