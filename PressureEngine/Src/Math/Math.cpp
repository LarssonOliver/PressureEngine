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

}