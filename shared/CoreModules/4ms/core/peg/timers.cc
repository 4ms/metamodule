//Todo: replace as many as possible with HAL_GetTicks() modulo some value
//
#include "main.hh"

namespace MetaModule::PEG
{

void MiniPEG::inc_tmrs(void) {
	systmr++;
	tapouttmr++;
	tapintmr++;
	pingtmr++;
	trigouttmr++;
}

}
