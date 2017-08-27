#pragma once

namespace Pressure {

	class RawModel {

	private:
		unsigned int vaoID;
		int vertexCount;

	public:
		RawModel(const unsigned int vaoID, const int vertexCount);
		unsigned int getVaoID() const;
		int getVertexCount() const;

	};

}
