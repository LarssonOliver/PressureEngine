#pragma once

#include "Vectors\Vector2f.h"
#include "Vectors\Vector3f.h"
#include "Vectors\Vector4f.h"

#include "Matrices\Matrix4f.h"

#include <vector>
#include <string>

namespace Pressure {

	struct Math {

		static long getTimeMillis();
		static long getTimeNano();

		static double toRadians(const double v);

		static std::vector<std::string> strSplit(const std::string& s, const char& c);
		static bool strStartsWith(const std::string& s, const char* c);

		static float fmax(float& f, float max);
		static float fmin(float& f, float min);
		static float frange(float&f, float min, float max);

	};

}