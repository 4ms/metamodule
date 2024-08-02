/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Configuration.h"

#include <span>

namespace Framing
{

template <typename IMPL>
class Deframer
{
public:
	Deframer(const Configuration_t&, IMPL*);

	template <typename FUNC>
	void parse(uint8_t, const FUNC&& func);
	void reset();

	bool isReceivingFrame()
	{
		return state != WAIT_HEADER;
	}

private:
	const Configuration_t Configuration;
	enum ParsingState_t {WAIT_HEADER, IN_MESSAGE, ESCAPE};
	ParsingState_t state;

private:
	IMPL* impl;
};

}

#include "Deframer.hpp"

