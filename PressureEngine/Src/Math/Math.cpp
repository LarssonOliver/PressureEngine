#define _USE_MATH_DEFINES

#include "../Common.h"
#include <chrono>
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

	long Math::getTimeMillis() {
		return (long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	long Math::getTimeNano() {
		return (long)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	double Math::toRadians(const double v) {
		return v * (M_PI / 180.0);
	}

}