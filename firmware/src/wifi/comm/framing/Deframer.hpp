/* Author: Lennart@binarylabs.dev */

namespace Framing
{

template <typename IMPL>
Deframer<IMPL>::Deframer(const Configuration_t& config, IMPL* impl_) : Configuration(config), impl(impl_)
{
	state = WAIT_HEADER;
}

template <typename IMPL>
void Deframer<IMPL>::reset()
{
	impl->doReset();
	state = WAIT_HEADER;
}

template <typename IMPL>
template <typename FUNC>
void Deframer<IMPL>::parse(uint8_t thisByte, const FUNC&& func)
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
			impl->doReset();
			state = WAIT_HEADER;
		}
		else if (thisByte == Configuration.end)
		{
			impl->doComplete(func);
			impl->doReset();
			state = WAIT_HEADER;
		}
		else if (thisByte == Configuration.escape)
		{
			state = ESCAPE;
		}
		else
		{
			impl->doAdd(thisByte, func);
		}
	}
	else if (state == ESCAPE)
	{
		impl->doAdd(thisByte, func);
		state = IN_MESSAGE;
	}
}


}
