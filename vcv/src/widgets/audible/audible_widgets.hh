#include <rack.hpp>

template<typename Base>
struct Rogan6PSLight : Base {
	Rogan6PSLight() {
		this->box.size = rack::mm2px(rack::Vec(23.04, 23.04));
		this->borderColor = nvgRGBA(0, 0, 0, 0);
	}
};
