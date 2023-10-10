/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Deframer.h"

#include <vector>

namespace Framing
{

class DynamicDeframer : public Deframer
{
public:
	DynamicDeframer(const Configuration_t& config_, const FUNC func_) : Deframer(config_, func_) {};
	~DynamicDeframer() = default;

private:
	virtual void doReset() override;
	virtual void doAdd(uint8_t) override;
	virtual void doComplete() override;

private:
	std::vector<uint8_t> receiveBuffer;
};

}

