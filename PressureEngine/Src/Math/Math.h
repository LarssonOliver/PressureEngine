#pragma once

#include "Vectors\Vector2f.h"
#include "Vectors\Vector3f.h"
#include "Vectors\Vector4f.h"

#include "Matrices\Matrix4f.h"

namespace Pressure {

	struct Math {

		static float cosFromSin(float sin, float angle);

		static long getTimeMillis();
		static long getTimeNano();

		static double toRadians(const double v);

	};

}