/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Configuration.h"

#include <functional>

namespace Framing
{

class Framer
{
public:
	using FUNC = std::function<void(uint8_t)>;

	Framer(const Configuration_t&, const FUNC);

	template <typename CONTAINER>
	void send(const CONTAINER& data)
	{
		doStart();

		for (auto& byte : data)
		{
			doPayload(byte);
		}

		doEnd();
	}

	void doStart();
	void doEnd();
	void doPayload(uint8_t);

private:
	const Configuration_t Configuration;
	bool partialPacket;
	FUNC func;

};

}


