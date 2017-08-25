#include <iostream>
#include <GLFW\glfw3.h>
#include "src\Math\Math.h"

using namespace Pressure;

int main() {
	
	if (!glfwInit()) {
		std::cout << "GLFW INIT ERROR!" << std::endl;
	}

	//TESTAR GIT

	Vector2f vec(2);
	Vector3f vec3(vec, 4);

	std::cout << vec.x << ", " << vec.y << std::endl;
	std::cout << vec3.x << ", " << vec3.y << ", " << vec3.z << std::endl;
	std::cout << 3 / 4 << std::endl;


	std::cin.get();
	return 0;
}