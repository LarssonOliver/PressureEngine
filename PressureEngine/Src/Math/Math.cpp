#define _USE_MATH_DEFINES

#include "../Common.h"
#include <chrono>
#include <random>
#include "Math.h"

namespace Pressure {

	const float Math::PI = M_PI;

	long Math::getTimeMillis() {
		return (long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	long Math::getTimeNano() {
		return (long)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	constexpr double Math::toRadians(const double v) {
		return v * (M_PI / 180.0);
	}

	constexpr double Math::toDegrees(const double r) {
		return r * 180.0 / M_PI;
	}

	std::vector<std::string> Math::strSplit(const std::string& s, const char& c) {
		std::string buff{ "" };
		std::vector<std::string> v;

		for (auto n : s)
		{
			if (n != c) buff += n; else
				if (n == c && buff != "") { v.push_back(buff); buff = ""; }
		}
		if (buff != "") v.push_back(buff);

		return v;
	}

	bool Math::strStartsWith(const std::string& s, const char* c) {
		return (s.substr(0, strlen(c)) == c);
	}

	constexpr float Math::fmax(float& f, float max) {		
		return f = f < max ? f : max;
	}

	constexpr float Math::fmin(float& f, float min) {
		return f = f > min ? f : min;
	}

	constexpr float Math::frange(float& f, float min, float max) {
		fmin(f, min);
		return fmax(f, max);
	}

	float Math::easeInQuad(float time, float value, float change, float duration) {
		time /= duration;
		return change * time * time + value;
	}

	float Math::easeOutQuad(float time, float value, float change, float duration) {
		time /= duration;
		return -change * time * (time - 2) + value;
	}

}