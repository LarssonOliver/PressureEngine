#define _USE_MATH_DEFINES

#include "../Common.h"
#include <chrono>
#include "Math.h"

namespace Pressure {

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