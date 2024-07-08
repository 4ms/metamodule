#include <app/Knob.hpp>

namespace rack::app
{

void Knob::initParamQuantity() {
	ParamWidget::initParamQuantity();
	engine::ParamQuantity *pq = getParamQuantity();
	if (pq) {
		if (snap)
			pq->snapEnabled = true;
		// Only enable smoothing if snapping is disabled
		if (smooth && !pq->snapEnabled)
			pq->smoothEnabled = true;
	}
}

} // namespace rack::app
