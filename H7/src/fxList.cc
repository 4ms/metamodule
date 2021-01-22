#include "fxList.hh"
#include "processors/bit_crush.h"
#include "processors/flanger.h"
#include "processors/resonator.h"
#include "processors/karplus.h"
#include "processors/lpf.h"
#include "processors/lpg.h"
#include "processors/reverb.h"
#include "processors/vca.h"
#include "processors/wavefold.h"

FXList::FXList()
	: fxList{new VCA, new Resonator, new Karplus, new Flanger, new BitCrusher}
{}

AudioProcessor *FXList::operator[](unsigned int fxnum)
{
	while (fxnum >= NumFX)
		fxnum -= NumFX;
	return fxList[fxnum];
}
