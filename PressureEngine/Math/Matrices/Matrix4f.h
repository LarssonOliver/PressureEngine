#pragma once
#include "../Vectors/Vector4f.h"

struct Matrix4f {

	/* COMPONENTS */
	// Formatted val[column + row * 4]
	float val[4 * 4];

	/* CONSTRUCTORS */
	Matrix4f();
	Matrix4f(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3);

	/* IDENTITY */
	Matrix4f& identity();

	/* GETTERS */
	float* getArray() const;
	float get(int col, int row) const;

	/* SETTERS */
	Matrix4f& set(const Matrix4f& m);
	Matrix4f& set(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3);
	Matrix4f& setColumn(int col, const Vector4f& v);

	/* ADDITION */
	Matrix4f& add(const Matrix4f& m);
	Matrix4f& add(const Matrix4f& m, Matrix4f& dest) const;

	/* MULTIPLICATION */
	Matrix4f& mul(const Matrix4f& m);
	Matrix4f& mul(const Matrix4f& m, Matrix4f& dest);

	/* EQUALITY CHECK */
	bool equals(const Matrix4f& m) const;

	/* OPERATOR OVERLOADING */
	bool operator==(const Matrix4f& other) const;
	bool operator!=(const Matrix4f& other) const;

};
