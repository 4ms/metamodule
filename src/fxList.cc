#include "fxList.hh"

FXList::FXList()
	: fxList{new LowPassFilter, new VCA, new Karplus, new WaveFolder, new BitCrusher}
	//: fxList{&fx1, &fx2, &fx3, &fx4, &fx5}
{}

AudioProcessor *FXList::operator[](unsigned int fxnum)
{
	while (fxnum >= NumFX)
		fxnum -= NumFX;
	return fxList[fxnum];
}
