/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Deframer.h"
#include <array>

#include <console/pr_dbg.hh>

namespace Framing
{

class StaticDeframer : public Deframer<StaticDeframer>
{
public:
	StaticDeframer(const Configuration_t& config_, std::span<uint8_t> scratchBuffer) 
		: Deframer<StaticDeframer>(config_, this)
		, receiveBuffer(scratchBuffer)
		{};

private:
	template <typename FUNC>
	void doReset(const FUNC&& func)
	{
		fillCount = 0;
	}

	template <typename FUNC>
	void doAdd(uint8_t byte, const FUNC&& func)
	{
		if (fillCount < receiveBuffer.size())
		{
			receiveBuffer[fillCount++] = byte;
		}
		else
		{
			pr_err("StaticDeframer: Frame larger than maximum size\n");
			doReset(func);
		}
	}
	template <typename FUNC>
	void doComplete(const FUNC&& func)
	{
		func({receiveBuffer.data(), fillCount});
	}

private:
	std::span<uint8_t> receiveBuffer;
	std::size_t fillCount = 0;

private:
	friend Deframer<StaticDeframer>;
};

template <std::size_t SIZE>
class StaticDeframerInclusive : public StaticDeframer
{
public:
	StaticDeframerInclusive(const Configuration_t& config_) : StaticDeframer(config_, std::span(receiveBuffer)) {};
private:
	std::array<uint8_t,SIZE> receiveBuffer;
};

}


