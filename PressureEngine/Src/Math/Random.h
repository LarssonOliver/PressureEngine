#pragma once
#include <random>

using namespace std;

namespace Pressure {

	template <typename T = float> 
	class Random {

	private:
		random_device rd;
		mt19937 mt;
		uniform_real_distribution<T> dist;

	public:
		Random();
		Random(T min, T max);

		T next();

	};

}