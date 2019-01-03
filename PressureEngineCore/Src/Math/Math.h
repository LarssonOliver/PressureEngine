#pragma once

#include "../DllExport.h"

#include "Vectors\Vector2f.h"
#include "Vectors\Vector3f.h"
#include "Vectors\Vector4f.h"

#include "Matrices\Matrix4f.h"

#include "Random.h"

#include <vector>
#include <string>

namespace Pressure {

	class PRESSURE_API Math {

	private:
		Math() = delete;

	public:

		static const float PI;
		
		static long getTimeMillis();
		static long getTimeNano();

		constexpr static double toRadians(const double v) { return v * (PI / 180.0); }
		constexpr static double toDegrees(const double r) { return r * (180.0 / PI); }

		static std::vector<std::string> strSplit(const std::string& s, const char& c);
		static bool strStartsWith(const std::string& s, const char* c);

		constexpr static float fmax(float&f, float max) { return f = f < max ? f : max; }
		constexpr static float fmin(float&f, float min) { return f = f > min ? f : min; }
		constexpr static float frange(float&f, float min, float max) {
			fmin(f, min);
			return fmax(f, max);
		}

		//**************** EASING SOURCE: http://gizma.com/easing/ ****************//
		// Acceleration.
		static float easeInQuad(float time, float value, float change, float duration);
		// Deceleration to 0 velocity.
		static float easeOutQuad(float time, float value, float change, float duration);

	};

}