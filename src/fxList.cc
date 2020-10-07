#include "fxList.hh"
#include "processors/bit_crush.h"
#include "processors/lpf.h"
#include "processors/lpg.h"
#include "processors/reverb.h"
#include "processors/vca.h"
#include "processors/wavefold.h"

FXList::FXList()
	: fxList{new LowPassFilter, new Reverb, new VCA, new WaveFolder, new BitCrusher}
{}

AudioProcessor *FXList::operator[](unsigned int fxnum)
{
	while (fxnum >= NumFX)
		fxnum -= NumFX;
	return fxList[fxnum];
}

