#include <iostream>
#include "Math\Vectors.h"

int main() {
	
	//TESTAR GIT

	Vector2f vec(2);
	Vector3f vec3(vec, 4);

	std::cout << vec.x << ", " << vec.y << std::endl;
	std::cout << vec3.x << ", " << vec3.y << ", " << vec3.z << std::endl;
	std::cout << sizeof(float) << std::endl;


	std::cin.get();
	return 0;
}