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

	public:
		static long getTimeMillis();
		static long getTimeNano();

		static double toRadians(const double v);
		static double toDegrees(const double r);

		static std::vector<std::string> strSplit(const std::string& s, const char& c);
		static bool strStartsWith(const std::string& s, const char* c);

		static float fmax(float&f, float max);
		static float fmin(float&f, float min);
		static float frange(float&f, float min, float max);

		//**************** EASING SOURCE: http://gizma.com/easing/ ****************//
		// Acceleration.
		static float easeInQuad(float time, float value, float change, float duration);
		// Deceleration to 0 velocity.
		static float easeOutQuad(float time, float value, float change, float duration);

	};

}