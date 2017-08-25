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
float Matrix4f::get(int col, int row) const {
	if (col < 0 || col > 3 || row < 0 || row > 3)
		return -1;
	return val[col + row * 4];
}

float Matrix4f::get(int element) const {
	if (element < 0 || element > 15)
		return -1;
	return val[element];
}

/* SETTERS */
Matrix4f& Matrix4f::set(int col, int row, float value) {
	if (col < 0 || col > 3 || row < 0 || row > 3)
		return *this;
	val[col + row * 4] = value;
	return *this;
}

Matrix4f& Matrix4f::set(int element, float value) {
	if (element < 0 || element > 15)
		return *this;
	val[element] = value;
	return *this;
}

Matrix4f& Matrix4f::set(const Matrix4f& m) {
	for (int i = 0; i < 4 * 4; i++) {
		set(i, m.get(i));
	} return *this;
}

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

Matrix4f& Matrix4f::setColumn(int col, const Vector4f& v) {
	if (col < 0 || col > 4)
		return *this;
	val[0 + col * 4] = v.getX();
	val[1 + col * 4] = v.getY();
	val[2 + col * 4] = v.getZ();
	val[3 + col * 4] = v.getW();
	return *this;
}

/* ADDITION */
Matrix4f& Matrix4f::add(const Matrix4f& m) {
	for (int i = 0; i < 4 * 4; i++) {
		set(i, (val[i] + m.get(i)));
	} return *this;
}

Matrix4f& Matrix4f::add(const Matrix4f& m, Matrix4f& dest) const {
	for (int i = 0; i < 4 * 4; i++) {
		dest.set(i, (val[i] + m.get(i)));
	} return dest;
}

/* MULTIPLICATION */
Matrix4f& Matrix4f::mul(const Matrix4f& m) {
	return mul(m, *this);
}

Matrix4f& Matrix4f::mul(const Matrix4f& m, Matrix4f& dest) const {
	float nm00 = get(0, 0) * m.get(0, 0) + get(1, 0) * m.get(0, 1) + get(2, 0) * m.get(0, 2) + get(3, 0) * m.get(0, 3);
	float nm01 = get(0, 1) * m.get(0, 0) + get(1, 1) * m.get(0, 1) + get(2, 1) * m.get(0, 2) + get(3, 1) * m.get(0, 3);
	float nm02 = get(0, 2) * m.get(0, 0) + get(1, 2) * m.get(0, 1) + get(2, 2) * m.get(0, 2) + get(3, 2) * m.get(0, 3);
	float nm03 = get(0, 3) * m.get(0, 0) + get(1, 3) * m.get(0, 1) + get(2, 3) * m.get(0, 2) + get(3, 3) * m.get(0, 3);

	float nm10 = get(0, 0) * m.get(1, 0) + get(1, 0) * m.get(1, 1) + get(2, 0) * m.get(1, 2) + get(3, 0) * m.get(1, 3);
	float nm11 = get(0, 1) * m.get(1, 0) + get(1, 1) * m.get(1, 1) + get(2, 1) * m.get(1, 2) + get(3, 1) * m.get(1, 3);
	float nm12 = get(0, 2) * m.get(1, 0) + get(1, 2) * m.get(1, 1) + get(2, 2) * m.get(1, 2) + get(3, 2) * m.get(1, 3);
	float nm13 = get(0, 3) * m.get(1, 0) + get(1, 3) * m.get(1, 1) + get(2, 3) * m.get(1, 2) + get(3, 3) * m.get(1, 3);

	float nm20 = get(0, 0) * m.get(2, 0) + get(1, 0) * m.get(2, 1) + get(2, 0) * m.get(2, 2) + get(3, 0) * m.get(2, 3);
	float nm21 = get(0, 1) * m.get(2, 0) + get(1, 1) * m.get(2, 1) + get(2, 1) * m.get(2, 2) + get(3, 1) * m.get(2, 3);
	float nm22 = get(0, 2) * m.get(2, 0) + get(1, 2) * m.get(2, 1) + get(2, 2) * m.get(2, 2) + get(3, 2) * m.get(2, 3);
	float nm23 = get(0, 3) * m.get(2, 0) + get(1, 3) * m.get(2, 1) + get(2, 3) * m.get(2, 2) + get(3, 3) * m.get(2, 3);

	float nm30 = get(0, 0) * m.get(3, 0) + get(1, 0) * m.get(3, 1) + get(2, 0) * m.get(3, 2) + get(3, 0) * m.get(3, 3);
	float nm31 = get(0, 1) * m.get(3, 0) + get(1, 1) * m.get(3, 1) + get(2, 1) * m.get(3, 2) + get(3, 1) * m.get(3, 3);
	float nm32 = get(0, 2) * m.get(3, 0) + get(1, 2) * m.get(3, 1) + get(2, 2) * m.get(3, 2) + get(3, 2) * m.get(3, 3);
	float nm33 = get(0, 3) * m.get(3, 0) + get(1, 3) * m.get(3, 1) + get(2, 3) * m.get(3, 2) + get(3, 3) * m.get(3, 3);
	
	dest.set(0, 0, nm00);
	dest.set(0, 1, nm01);
	dest.set(0, 2, nm02);
	dest.set(0, 3, nm03);

	dest.set(1, 0, nm10);
	dest.set(1, 1, nm11);
	dest.set(1, 2, nm12);
	dest.set(1, 3, nm13);

	dest.set(2, 0, nm20);
	dest.set(2, 1, nm21);
	dest.set(2, 2, nm22);
	dest.set(2, 3, nm23);

	dest.set(3, 0, nm30);
	dest.set(3, 1, nm31);
	dest.set(3, 2, nm32);
	dest.set(3, 3, nm33);
	return dest;
}

/* EQUALITY  CHECK */
bool Matrix4f::equals(const Matrix4f& m) const {
	bool result = true;
	for (int i = 0; i < 4 * 4; i++) {
		if (get(i) != m.get(i)) {
			result = false;
			break;
		}
	}
}

/* OPERATOR OVERLOADING */
bool Matrix4f::operator==(const Matrix4f& other) const {
	return equals(other);
}

bool Matrix4f::operator!=(const Matrix4f& other) const {
	return !equals(other);
}