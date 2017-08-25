#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include "Math.h"

namespace Pressure {

	float Math::cosFromSin(float sin, float angle) {
		float cos = std::sqrtf(1.f - sin * sin);
		float a = angle + ((float)M_PI * 0.5f);
		float b = a - (int)(a / M_2_PI) * (float)M_2_PI;
		if (b < 0.f)
			b = (float)M_2_PI + b;
		if (b >= M_PI)
			return -cos;
		return cos;
	}

}