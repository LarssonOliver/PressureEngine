#include "../stdafx.h"
#include "PressureEngine\Src\Math\Math.h"
using namespace Pressure;

namespace PressureEngineTest {
	TEST_CLASS(_Math) {

	public: 

		TEST_METHOD(_fmax) {			

			float a = 4;
			float b = a + 3;
			Math::fmax(b, a);
			Assert::AreEqual(b, a);

		}

	};
}