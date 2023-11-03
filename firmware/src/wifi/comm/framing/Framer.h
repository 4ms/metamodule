/* Author: Lennart@binarylabs.dev */

#pragma once

#include "Configuration.h"

namespace Framing
{

class Framer
{
public:
	Framer(const Configuration_t& conf) : Configuration(conf) {}

	template <typename CONTAINER, typename FUNC>
	void send(const CONTAINER& data, const FUNC&& func)
	{
		func(Configuration.start);

		for (auto& byte : data)
		{
			if (byte == Configuration.start || byte == Configuration.end || byte == Configuration.escape)
			{
				func(Configuration.escape);
			}

			func(byte);
		}

		func(Configuration.end);
	}

	template <typename FUNC>
	void sendStart(const FUNC&& func)
	{
		func(Configuration.start);
	}

	template <typename FUNC>
	void sendStop(const FUNC&& func)
	{
		func(Configuration.end);
	}

	template <typename FUNC>
	void sendPayload(uint8_t byte, const FUNC&& func)
	{
		if (byte == Configuration.start || byte == Configuration.end || byte == Configuration.escape)
		{
			func(Configuration.escape);
		}

		func(byte);
	}

private:
	const Configuration_t Configuration;
};

}


