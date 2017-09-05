#include "OBJLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace Pressure {

	RawModel* OBJLoader::loadObjModel(const char* fileName, Loader& loader) {

		ifstream file("res/" + string(fileName) + ".obj");
		
		if (!file.is_open())
			return nullptr;

		stringstream sstr;
		sstr << file.rdbuf();
		string data = sstr.str();

		//REWRITE BELOW

		vector<Vector3f> vertices;
		vector<Vector2f> uvs;
		vector<Vector3f> normals;
		vector<int> indices;

		vector<float> textureArray;
		vector<float> normalsArray;

		while (getline(file, line)) {
			vector<string> currentLine{ Math::strSplit(line, ' ') };
			if (Math::strStartsWith(line, "v ")) {
				//Vector3f vertex(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3]));
				vertices.emplace_back(Vector3f(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3])));
			}
			else if (Math::strStartsWith(line, "vt ")) {
				//Vector2f uv(stof(currentLine[1]), stof(currentLine[2]));
				uvs.emplace_back(Vector2f(stof(currentLine[1]), stof(currentLine[2])));
			}
			else if (Math::strStartsWith(line, "vn ")) {
				//Vector3f normal(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3]));
				normals.emplace_back(Vector3f(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3])));
			}
			else if (Math::strStartsWith(line, "f ")) {
				textureArray = vector<float>(vertices.size() * 2);
				normalsArray = vector<float>(vertices.size() * 3);
				break;
			}
		}
		//std::cout << Math::getTimeMillis() - time << std::endl;
		//time = Math::getTimeMillis()

		while (getline(file, line)) {
			//std::cout << Math::getTimeNano() - time << std::endl;
			//time = Math::getTimeNano();
			if (!Math::strStartsWith(line, "f ")) {
				continue;
			}
			vector<string> currentLine{ Math::strSplit(line, ' ') };
			vector<string> vertex1 = Math::strSplit(currentLine[1], '/');
			vector<string> vertex2 = Math::strSplit(currentLine[2], '/');
			vector<string> vertex3 = Math::strSplit(currentLine[3], '/');

			processVertex(vertex1, indices, uvs, normals, textureArray, normalsArray);
			processVertex(vertex2, indices, uvs, normals, textureArray, normalsArray);
			processVertex(vertex3, indices, uvs, normals, textureArray, normalsArray);
			//std::cout << Math::getTimeNano() - time << std::endl;
			//time = Math::getTimeNano();
		}

		//std::cout << Math::getTimeMillis() - time << std::endl;

		file.close();

		vector<float> verticesArray(vertices.size() * 3);
		vector<int> indicesArray(indices.size());

		int vertexPointer = 0;
		for (auto vertex : vertices) {
			verticesArray[vertexPointer++] = vertex.getX();
			verticesArray[vertexPointer++] = vertex.getY();
			verticesArray[vertexPointer++] = vertex.getZ();
		}

		for (unsigned int i = 0; i < indices.size(); i++) {
			indicesArray[i] = indices[i];
		}

		return loader.loadToVao(verticesArray, textureArray, indicesArray);
	}

	void OBJLoader::processVertex(std::vector<std::string>& vertexData, std::vector<int>& indices, std::vector<Vector2f>& textures,
		std::vector<Vector3f>& normals, std::vector<float>& textureArray, std::vector<float>& normalsArray) {
		int currentVertexPointer = stoi(vertexData[0]) - 1;
		indices.emplace_back(currentVertexPointer);
		Vector2f currentTex = textures[stoi(vertexData[1]) - 1];
		textureArray[currentVertexPointer * 2] = currentTex.getX();
		textureArray[currentVertexPointer * 2 + 1] = 1 - currentTex.getY();
		Vector3f currentNorm = normals[stoi(vertexData[2]) - 1];
		normalsArray[currentVertexPointer * 3] = currentNorm.getX();
		normalsArray[currentVertexPointer * 3 + 1] = currentNorm.getY();
		normalsArray[currentVertexPointer * 3 + 2] = currentNorm.getZ();
	}

}