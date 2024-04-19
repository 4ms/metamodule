#include <math.h>

// This is needed when compiling with arm gcc 12.3 to satisfy C23 compliance
float roundevenf(float x) {
	return roundf(x);
}
