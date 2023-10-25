/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Configuration.h"

#include <functional>
#include <span>

namespace Framing
{

class Deframer
{
public:
	using FUNC = std::function<void(std::span<uint8_t>)>;

	Deframer(const Configuration_t&, const FUNC);
	virtual ~Deframer() = default;

	void parse(uint8_t);
	void reset();

private:
	virtual void doReset() = 0;
	virtual void doAdd(uint8_t) = 0;
	virtual void doComplete() = 0;

protected:
	FUNC func;

private:
	const Configuration_t Configuration;
	enum ParsingState_t {WAIT_HEADER, IN_MESSAGE, ESCAPE};
	ParsingState_t state;
};

}

