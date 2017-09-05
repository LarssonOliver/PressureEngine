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

		vector<Vector3f> vertices;
		vector<Vector2f> uvs;
		vector<Vector3f> normals;
		vector<int> indices;

		vector<float> textureArray;
		vector<float> normalsArray;

		unsigned short lineLength;
		unsigned int lineStart = 0;

		for (int i = 0; i < data.length(); i++) {
			char c = data[i];

			if (c == '\n') {
				lineLength = i - lineStart;

				string line(&data[lineStart], lineLength);
				lineStart = i + 1;

				if (line[0] == 'v' && line[1] == ' ') {	
					bool negative1, negative2, negative3;
					line[2] == '-' ? negative1 = true : negative1 = false;
					line[11 + negative1] == '-' ? negative2 = true : negative2 = false;
					line[20 + negative1 + negative2] == '-' ? negative3 = true : negative3 = false;	
					vertices.emplace_back(Vector3f(stof(line.substr(2, 8 + negative1)), stof(line.substr(11 + negative1, 8 + negative2)), stof(line.substr(20 + negative1 + negative2, 8 + negative3))));
				}
				else if (Math::strStartsWith(line, "vt ")) {
					uvs.emplace_back(Vector2f(stof(line.substr(3, 8)), stof(line.substr(12, 8))));
				}
				else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
					bool negative1, negative2, negative3;
					line[3] == '-' ? negative1 = true : negative1 = false;
					line[12 + negative1] == '-' ? negative2 = true : negative2 = false;
					line[21 + negative1 + negative2] == '-' ? negative3 = true : negative3 = false;
					normals.emplace_back(Vector3f(stof(line.substr(3, 8 + negative1)), stof(line.substr(12 + negative1, 8 + negative2)), stof(line.substr(21 + negative1 + negative2, 8 + negative3))));
				}
				else if (Math::strStartsWith(line, "f ")) {
					textureArray = vector<float>(vertices.size() * 2);
					normalsArray = vector<float>(vertices.size() * 3);
					system("PAUSE");
					break;
				}






			}
		}

		return nullptr;

	}

	void OBJLoader::handleLine(string& line) {



	}


//
//	//REWRITE BELOW
//
//
//	while (getline(file, line)) {
//
//	}
//	//std::cout << Math::getTimeMillis() - time << std::endl;
//	//time = Math::getTimeMillis()
//
//	while (getline(file, line)) {
//		//std::cout << Math::getTimeNano() - time << std::endl;
//		//time = Math::getTimeNano();
//		if (!Math::strStartsWith(line, "f ")) {
//			continue;
//		}
//		vector<string> currentLine{ Math::strSplit(line, ' ') };
//		vector<string> vertex1 = Math::strSplit(currentLine[1], '/');
//		vector<string> vertex2 = Math::strSplit(currentLine[2], '/');
//		vector<string> vertex3 = Math::strSplit(currentLine[3], '/');
//
//		processVertex(vertex1, indices, uvs, normals, textureArray, normalsArray);
//		processVertex(vertex2, indices, uvs, normals, textureArray, normalsArray);
//		processVertex(vertex3, indices, uvs, normals, textureArray, normalsArray);
//		//std::cout << Math::getTimeNano() - time << std::endl;
//		//time = Math::getTimeNano();
//	}
//
//	//std::cout << Math::getTimeMillis() - time << std::endl;
//
//	file.close();
//
//	vector<float> verticesArray(vertices.size() * 3);
//	vector<int> indicesArray(indices.size());
//
//	int vertexPointer = 0;
//	for (auto vertex : vertices) {
//		verticesArray[vertexPointer++] = vertex.getX();
//		verticesArray[vertexPointer++] = vertex.getY();
//		verticesArray[vertexPointer++] = vertex.getZ();
//	}
//
//	for (unsigned int i = 0; i < indices.size(); i++) {
//		indicesArray[i] = indices[i];
//	}
//
//	return loader.loadToVao(verticesArray, textureArray, indicesArray);
//}
//
//void OBJLoader::processVertex(std::vector<std::string>& vertexData, std::vector<int>& indices, std::vector<Vector2f>& textures,
//	std::vector<Vector3f>& normals, std::vector<float>& textureArray, std::vector<float>& normalsArray) {
//	int currentVertexPointer = stoi(vertexData[0]) - 1;
//	indices.emplace_back(currentVertexPointer);
//	Vector2f currentTex = textures[stoi(vertexData[1]) - 1];
//	textureArray[currentVertexPointer * 2] = currentTex.getX();
//	textureArray[currentVertexPointer * 2 + 1] = 1 - currentTex.getY();
//	Vector3f currentNorm = normals[stoi(vertexData[2]) - 1];
//	normalsArray[currentVertexPointer * 3] = currentNorm.getX();
//	normalsArray[currentVertexPointer * 3 + 1] = currentNorm.getY();
//	normalsArray[currentVertexPointer * 3 + 2] = currentNorm.getZ();
//}

}