#include "Callbacks.h"
#include "Math\Math.h"
#include <iostream>

namespace Pressure {

	void Callbacks::error_callback(int error, const char* description) {
		fprintf(stderr, "Error: %s\n", description);
	}

}