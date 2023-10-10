/* Author: Lennart@binarylabs.dev */

#include "Deframer.h"

namespace Framing
{

Deframer::Deframer(const Configuration_t& config, const FUNC func_) : func(func_), Configuration(config)
{
	state = WAIT_HEADER;
}

void Deframer::reset()
{
	doReset();
	state = WAIT_HEADER;
}

void Deframer::parse(uint8_t thisByte)
{
	if (state == WAIT_HEADER)
	{
		if (thisByte == Configuration.start)
		{
			state = IN_MESSAGE;
		}
	}
	else if (state == IN_MESSAGE)
	{
		if (thisByte == Configuration.start)
		{
			doReset();
			state = WAIT_HEADER;
		}
		else if (thisByte == Configuration.end)
		{
			doComplete();
			doReset();
			state = WAIT_HEADER;
		}
		else if (thisByte == Configuration.escape)
		{
			state = ESCAPE;
		}
		else
		{
			doAdd(thisByte);
		}
	}
	else if (state == ESCAPE)
	{
		doAdd(thisByte);
		state = IN_MESSAGE;
	}
}


}
