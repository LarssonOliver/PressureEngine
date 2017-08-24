#include <cmath>
#include "Vector2f.h"

/* CONSTRUCTORS */
Vector2f::Vector2f() {
	this->x = 0.f;
	this->y = 0.f;
}

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::Vector2f(float d) {
	this->x = this->y = d;
}

/* GETTERS */
float Vector2f::getX() {
	return x;
}

float Vector2f::getY() {
	return y;
}

/* SETTERS */
Vector2f& Vector2f::set(float d) {
	this->x = this->y = d;
	return *this;
}

Vector2f& Vector2f::set(float x, float y) {
	this->x = x;
	this->y = y;
	return *this;
}

Vector2f& Vector2f::set(const Vector2f& v) {
	this->x = v.x;
	this->y = v.y;
	return *this;
}

/* ADDITION */
Vector2f& Vector2f::add(float x, float y) {
	this->x += x;
	this->y += y;
	return *this;
}

Vector2f& Vector2f::add(float x, float y, Vector2f& dest) {
	dest.x = this->x + x;
	dest.y = this->y + y;
	return dest;
}

Vector2f& Vector2f::add(const Vector2f& v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2f& Vector2f::add(const Vector2f& v, Vector2f& dest) {
	dest.x = this->x + v.x;
	dest.y = this->y + v.y;
	return dest;
}

/* SUBTRACTION */
Vector2f& Vector2f::sub(float x, float y) {
	this->x -= x;
	this->y -= y;
	return *this;
}

Vector2f& Vector2f::sub(float x, float y, Vector2f& dest) {
	dest.x = this->x - x;
	dest.y = this->y - y;
	return dest;
}

Vector2f& Vector2f::sub(const Vector2f& v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2f& Vector2f::sub(const Vector2f& v, Vector2f& dest) {
	dest.x = this->x - v.x;
	dest.y = this->y - v.y;
	return dest;
}

/* MULTIPLICATION */
Vector2f& Vector2f::mul(float scalar) {
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Vector2f& Vector2f::mul(float scalar, Vector2f& dest) {
	dest.x = this->x * scalar;
	dest.y = this->y * scalar;
	return dest;
}

Vector2f& Vector2f::mul(float x, float y) {
	this->x *= x;
	this->y *= y;
	return *this;
}

Vector2f& Vector2f::mul(float x, float y, Vector2f& dest) {
	dest.x = this->x * x;
	dest.y = this->y * y;
	return dest;
}

Vector2f& Vector2f::mul(const Vector2f& v) {
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Vector2f& Vector2f::mul(const Vector2f& v, Vector2f& dest) {
	dest.x = this->x * v.x;
	dest.y = this->y * v.y;
	return dest;
}

/* EQUALITY CHECK */
bool Vector2f::equals(const Vector2f& v) {
	return this->x == v.x && this->y == v.y;
}

/* TRIGONOMETRY */
//TODO: length, distance x2, angle

/* VECTOR MATH */
//TODO: EVERYTHING HERE

/* EXTRA FUNCTIONS */
Vector2f& Vector2f::negate() {
	this->x = -x;
	this->y = -y;
	return *this;
}

Vector2f& Vector2f::negate(Vector2f& dest) {
	dest.x = -x;
	dest.y = -y;
	return dest;
}

Vector2f& Vector2f::zero() {
	this->x = this->y = 0.f;
	return *this;
}

/* OPERATOR OVERLOADING */
//Vector2f& operator+(Vector2f& left, const Vector2f& right) {
//	return left.add(right);
//}
//
//Vector2f& operator-(Vector2f& left, const Vector2f& right) {
//	return left.sub(right);
//}
//
//Vector2f& operator*(Vector2f& left, const Vector2f& right) {
//	return left.mul(right);
//}
//
//Vector2f& operator/(Vector2f& left, const Vector2f& right) {
//	left.x /= right.x;
//	left.y /= right.y;
//	return left;
//}
//
//bool operator==(Vector2f& left, const Vector2f& right) {
//	return left.equals(right);
//}
//
//bool operator!=(Vector2f& left, const Vector2f& right) {
//	return !left.equals(right);
//}