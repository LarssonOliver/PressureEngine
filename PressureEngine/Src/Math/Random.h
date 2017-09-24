#pragma once
#include <random>

namespace Pressure {

	template <typename T> 
	class Random {

	private:
		std::random_device rd;
		std::mt19937 mt;
		std::uniform_real_distribution<T> dist;

	public:
		Random();
		Random(T min, T max);

		T next();

	};

	template<typename T>
	inline Random<T>::Random() 
		: mt(rd()), dist((T)0.0, (T)1.0) {
	}

	template<typename T>
	inline Random<T>::Random(T min, T max) 
		: mt(rd()), dist(min, max) {
	}

	template<typename T>
	inline T Random<T>::next() {
		return dist(mt);
	}

}