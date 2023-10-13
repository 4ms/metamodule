/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Deframer.h"

#include <vector>

namespace Framing
{

class DynamicDeframer : public Deframer<DynamicDeframer>
{
public:
	DynamicDeframer(const Configuration_t& config_) : Deframer<DynamicDeframer>(config_, this) {};
	~DynamicDeframer() = default;

private:
	template <typename FUNC>
	void doReset(const FUNC&&)
	{
		receiveBuffer.clear();
	}

	template <typename FUNC>
	void doAdd(uint8_t data, const FUNC&& func)
	{
		receiveBuffer.push_back(data);
	}

	template <typename FUNC>
	void doComplete(const FUNC&& func)
	{
		func({receiveBuffer.data(), receiveBuffer.size()});
	}

private:
	std::vector<uint8_t> receiveBuffer;

private:
	friend Deframer<DynamicDeframer>;
};

}

