#include "../../stdafx.h"
#include "PressureEngine\Src\Math\Random.h"

namespace PressureEngineTest {

	using namespace Pressure;

	TEST_CLASS(_Random) {

		TEST_METHOD(_random1) {
			Random<double> r;
			double d = r.next();
			double e = r.next();
			Assert::AreNotEqual(d, e);
		}

		TEST_METHOD(_random2) {
			Random<double> r(2, 4);
			double d = r.next();
			Assert::IsTrue(d >= 2 && d <= 4);
		}
	
	};

}