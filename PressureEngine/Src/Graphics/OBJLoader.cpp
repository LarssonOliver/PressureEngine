#include "OBJLoader.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

namespace Pressure {

	RawModel* OBJLoader::loadObjModel(const char* fileName, Loader& loader) {

		ifstream file("res/" + string(fileName) + ".obj");

		if (!file.is_open())
			return nullptr;

		//TODO: handle files larger than memory.

		stringstream sstr;
		sstr << file.rdbuf();
		string data = sstr.str();
		file.close();

		vector<float> vertices;
		vector<Vector2f> uvs;
		vector<Vector3f> normals;
		vector<int> indices;

		vector<float> textureArray;
		vector<float> normalsArray;

		unsigned short lineLength;
		unsigned int lineStart = 0;

		for (unsigned int i = 0; i < data.length(); i++) {
			if (data[i] == '\n') {
				lineLength = i - lineStart;

				if (data[lineStart] == 'v' && data[lineStart + 1] == ' ') {
					char* next;
					vertices.emplace_back(strtof(&data[lineStart + 2], &next));
					vertices.emplace_back(strtof(next, &next));
					vertices.emplace_back(strtof(next, NULL));
				}

				else if (data[lineStart] == 'v' && data[lineStart + 1] == 't' && data[lineStart + 2] == ' ') {
					char* next = &data[lineStart + 3];
					Vector2f uv(strtof(next, &next));
					uvs.push_back(uv.setY(strtof(next, NULL)));
				}

				else if (data[lineStart] == 'v' && data[lineStart + 1] == 'n' && data[lineStart + 2] == ' ') {
					char* next = &data[lineStart + 3];
					Vector3f normal(strtof(next, &next));
					normal.setY(strtof(next, &next));
					normals.push_back(normal.setZ(strtof(next, NULL)));
				}

				else if (data[lineStart] == 'f' && data[lineStart + 1] == ' ') {
					textureArray = vector<float>(vertices.size() * 2);
					normalsArray = vector<float>(vertices.size() * 3);

					//Adds some texture coords if none are present.
					if (uvs.size() == 0) {
						uvs.emplace_back(0.f);
						uvs.emplace_back(1.f, 0.f);
						uvs.emplace_back(1.f);
					}

					processFaces(data, lineStart, indices, uvs, normals, textureArray, normalsArray);
					break;
				}

				lineStart = i + 1;
			}
		}

		return loader.loadToVao(vertices, textureArray, normalsArray, indices);

	}


	void OBJLoader::processFaces(std::string& data, unsigned int lineStart, vector<int>& indices, vector<Vector2f>& uvs,
		std::vector<Vector3f>& normals, std::vector<float>& textureArray, std::vector<float>& normalsArray) {

		unsigned short lineLength;
		for (unsigned int i = lineStart; i < data.length(); i++) {
			if (data[i] == '\n') {
				lineLength = i - lineStart;

				// Skip this line if it is not a face. (starts with f)
				if (data[lineStart] != 'f') {
					lineStart = i + 1;
					continue;
				}

				char* next;
				for (int i = 0; i < 3; i++) {								
					int currentVertexPointer = i == 0 ? strtol(&data[lineStart + 2], &next, 10) - 1 : strtol(next, &next, 10) - 1;
					indices.push_back(currentVertexPointer);

					Vector2f currentUV = uvs[strtol(++next, &next, 10) - 1];
					textureArray[currentVertexPointer * 2] = currentUV.getX();
					textureArray[currentVertexPointer * 2 + 1] = 1 - currentUV.getY();

					Vector3f currentNorm = normals[strtol(++next, &next, 10) - 1];
					normalsArray[currentVertexPointer * 3] = currentNorm.getX();
					normalsArray[currentVertexPointer * 3 + 1] = currentNorm.getY();
					normalsArray[currentVertexPointer * 3 + 2] = currentNorm.getZ();
				}

				lineStart = i + 1;
			}
		}
	}

}