#include "../../stdafx.h"
#include "PressureEngine\Src\Math\Math.h"
#include <math.h>
#include <cmath>

namespace PressureEngineTest {

	using namespace Pressure;
	
	TEST_CLASS(_Math) {

		TEST_METHOD(_toRadians) {
			double d = 360;
			Assert::AreEqual(Math::toRadians(d), d / 180.0 * 3.14159265358979323846);
		}

		TEST_METHOD(_toDegrees) {
			double d = 3.14159265358979323846;
			Assert::AreEqual(Math::toDegrees(d), 180.0);
		}

		/*TEST_METHOD(x_toDegrees) {
			double d = 3;
			Assert::AreEqual(Math::toDegrees(d), 180.0);
		}*/

		TEST_METHOD(_fmax) {
			float f = 4, r = f;
			Math::fmax(f, f + 2);
			Math::fmax(f, f - 1);
			Assert::AreEqual(f, r - 1);
		}

		TEST_METHOD(_fmin) {
			float f = 4, r = f;
			Math::fmin(f, f - 2);
			Math::fmin(f, f + 1);
			Assert::AreEqual(f, r + 1);
		}

		TEST_METHOD(_frange) {
			float f = 4, r = f;
			Math::frange(f, f - 2, f + 1);
			Math::frange(f, f + 2, f + 3);
			Math::frange(f, f - 3, f - 1);
			Assert::AreEqual(f, r + 1);
		}

	};

}