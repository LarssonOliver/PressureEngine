#include "Random.h"

namespace Pressure {

	template <typename T> 
	Random<T>::Random() 
		: mt(rd()), dist((T)0.0, (T)1.0) {
	}

	template<typename T>
	Random<T>::Random(T min, T max)
		: mt(rd()), dist(min, max) {
	}

	template<typename T>
	T Random<T>::next() {
		return dist(mt);
	}

}