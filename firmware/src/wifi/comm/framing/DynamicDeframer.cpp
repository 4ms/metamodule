/* Author: Lennart@binarylabs.dev */

#include "DynamicDeframer.h"

namespace Framing
{


void DynamicDeframer::doReset()
{
	receiveBuffer.clear();
}

void DynamicDeframer::doAdd(uint8_t data)
{
	receiveBuffer.push_back(data);
}

void DynamicDeframer::doComplete()
{
	func({receiveBuffer.data(), receiveBuffer.size()});
}

}

