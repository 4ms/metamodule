/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Deframer.h"
#include <array>

#include <console/pr_dbg.hh>

namespace Framing
{

template <std::size_t SIZE>
class StaticDeframer : public Deframer
{
public:
	StaticDeframer(const Configuration_t& config_, const FUNC func_) : Deframer(config_, func_) {};
	~StaticDeframer() = default;

private:
	virtual void doReset() override
	{
		fillCount = 0;
	}
	virtual void doAdd(uint8_t byte) override
	{
		if (fillCount < SIZE)
		{
			receiveBuffer[fillCount++] = byte;
		}
		else
		{
			pr_err("StaticDeframer: Frame larger than maximum size");
			doReset();
		}
	}
	virtual void doComplete() override
	{
		func({receiveBuffer.data(), fillCount});
	}

private:
	std::array<uint8_t,SIZE> receiveBuffer;
	std::size_t fillCount = 0;
};

}


