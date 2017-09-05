#pragma once
#include <vector>
#include <string>
#include "Models\RawModel.h"
#include "Loader.h"
#include "../Math/Math.h"

namespace Pressure {

	class OBJLoader {

	public:
		static RawModel* loadObjModel(const char* fileName, Loader& loader);

	private:
		static void handleLine(std::string& line);


		//static void processVertex(std::vector<std::string>& vertexData, std::vector<int>& indices, std::vector<Vector2f>& textures,
		//	std::vector<Vector3f>& normals, std::vector<float>& textureArray, std::vector<float>& normalsArray);



	};

}