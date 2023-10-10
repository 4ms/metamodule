/* Author: Lennart@binarylabs.dev */

#include "Framer.h"

#include <console/pr_dbg.hh>

namespace Framing
{

Framer::Framer(const Configuration_t& config_,  const FUNC func_) : Configuration(config_), partialPacket(false), func(func_)
{};

void Framer::doStart()
{
	if (!partialPacket)
	{
		func(Configuration.start);
		partialPacket = true;
	}
	else
	{
		pr_err("Framer: Cannot start because already inside package");
	}
}
void Framer::doEnd()
{
	if (partialPacket)
	{
		func(Configuration.end);
		partialPacket = false;
	}
	else
	{
		pr_err("Framer: Cannot end because not inside package");
	}
}
void Framer::doPayload(uint8_t byte)
{
	if (partialPacket)
	{
		if (byte == Configuration.start || byte == Configuration.end || byte == Configuration.escape)
		{
			func(Configuration.escape);
		}

		func(byte);
	}
	else
	{
		pr_err("Framer: Cannot send payload because not inside package");
	}
}

}



