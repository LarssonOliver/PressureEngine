#include "Matrix4f.h"

/* CONSTRUCTORS */
Matrix4f::Matrix4f() {
	identity();
}

Matrix4f::Matrix4f(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3) {
	set(col0, col1, col2, col3);
}

/* IDENTITY */
Matrix4f& Matrix4f::identity() {
	// [1 0 0 0]
	// [0 1 0 0]
	// [0 0 1 0]
	// [0 0 0 1]

	// Col0
	val[0 + 0 * 4] = 1.f;
	val[1 + 0 * 4] = 0.f;
	val[2 + 0 * 4] = 0.f;
	val[3 + 0 * 4] = 0.f;

	// Col1
	val[0 + 1 * 4] = 0.f;
	val[1 + 1 * 4] = 1.f;
	val[2 + 1 * 4] = 0.f;
	val[3 + 1 * 4] = 0.f;

	// Col2
	val[0 + 2 * 4] = 0.f;
	val[1 + 2 * 4] = 0.f;
	val[2 + 2 * 4] = 1.f;
	val[3 + 2 * 4] = 0.f;

	// Col3
	val[0 + 3 * 4] = 0.f;
	val[1 + 3 * 4] = 0.f;
	val[2 + 3 * 4] = 0.f;
	val[3 + 3 * 4] = 1.f;
	
	return *this;
}

/* GETTERS */


/* SETTERS */
//Matrix4f& Matrix4f::set(const Matrix4f& m) {
//	
//}

Matrix4f& Matrix4f::set(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3) {
	// Col0
	val[0 + 0 * 4] = col0.getX();
	val[1 + 0 * 4] = col0.getY();
	val[2 + 0 * 4] = col0.getZ();
	val[3 + 0 * 4] = col0.getW();

	// Col1
	val[0 + 1 * 4] = col1.getX();
	val[1 + 1 * 4] = col1.getY();
	val[2 + 1 * 4] = col1.getZ();
	val[3 + 1 * 4] = col1.getW();

	// Col2
	val[0 + 2 * 4] = col2.getX();
	val[1 + 2 * 4] = col2.getY();
	val[2 + 2 * 4] = col2.getZ();
	val[3 + 2 * 4] = col2.getW();

	// Col3
	val[0 + 3 * 4] = col3.getX();
	val[1 + 3 * 4] = col3.getY();
	val[2 + 3 * 4] = col3.getZ();
	val[3 + 3 * 4] = col3.getW();
	
	return *this;
}