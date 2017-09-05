#include <cmath>
#include "Vector2f.h"

namespace Pressure {

	/* CONSTRUCTORS */
	Vector2f::Vector2f() : x(0.f), y(0.f) { }

	Vector2f::Vector2f(float x, float y) : x(x), y(y) { }

	Vector2f::Vector2f(float d) : x(d), y(d) { }

	/* GETTERS */
	float Vector2f::getX() const {
		return x;
	}

	float Vector2f::getY() const {
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
		this->x = v.getX();
		this->y = v.getY();
		return *this;
	}

	Vector2f& Vector2f::setX(float x) {
		this->x = x;
		return *this;
	}

	Vector2f& Vector2f::setY(float y) {
		this->y = y;
		return *this;
	}

	/* ADDITION */
	Vector2f& Vector2f::add(float x, float y) {
		this->x += x;
		this->y += y;
		return *this;
	}

	Vector2f& Vector2f::add(float x, float y, Vector2f& dest) const {
		dest.x = this->x + x;
		dest.y = this->y + y;
		return dest;
	}

	Vector2f& Vector2f::add(const Vector2f& v) {
		this->x += v.getX();
		this->y += v.getY();
		return *this;
	}

	Vector2f& Vector2f::add(const Vector2f& v, Vector2f& dest) const {
		dest.x = this->x + v.getX();
		dest.y = this->y + v.getY();
		return dest;
	}

	/* SUBTRACTION */
	Vector2f& Vector2f::sub(float x, float y) {
		this->x -= x;
		this->y -= y;
		return *this;
	}

	Vector2f& Vector2f::sub(float x, float y, Vector2f& dest) const {
		dest.x = this->x - x;
		dest.y = this->y - y;
		return dest;
	}

	Vector2f& Vector2f::sub(const Vector2f& v) {
		this->x -= v.getX();
		this->y -= v.getY();
		return *this;
	}

	Vector2f& Vector2f::sub(const Vector2f& v, Vector2f& dest) const {
		dest.x = this->x - v.getX();
		dest.y = this->y - v.getY();
		return dest;
	}

	/* MULTIPLICATION */
	Vector2f& Vector2f::mul(float scalar) {
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	Vector2f& Vector2f::mul(float scalar, Vector2f& dest) const {
		dest.x = this->x * scalar;
		dest.y = this->y * scalar;
		return dest;
	}

	Vector2f& Vector2f::mul(float x, float y) {
		this->x *= x;
		this->y *= y;
		return *this;
	}

	Vector2f& Vector2f::mul(float x, float y, Vector2f& dest) const {
		dest.x = this->x * x;
		dest.y = this->y * y;
		return dest;
	}

	Vector2f& Vector2f::mul(const Vector2f& v) {
		this->x *= v.getX();
		this->y *= v.getY();
		return *this;
	}

	Vector2f& Vector2f::mul(const Vector2f& v, Vector2f& dest) const {
		dest.x = this->x * v.getX();
		dest.y = this->y * v.getY();
		return dest;
	}

	/* DIVISION */
	Vector2f& Vector2f::div(float scalar) {
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	Vector2f& Vector2f::div(float scalar, Vector2f& dest) const {
		dest.x = this->x / scalar;
		dest.y = this->y / scalar;
		return dest;
	}

	Vector2f& Vector2f::div(float x, float y) {
		this->x /= x;
		this->y /= y;
		return *this;
	}

	Vector2f& Vector2f::div(float x, float y, Vector2f& dest) const {
		dest.x = this->x / x;
		dest.y = this->y / y;
		return dest;
	}

	Vector2f& Vector2f::div(const Vector2f& v) {
		this->x /= v.getX();
		this->y /= v.getY();
		return *this;
	}

	Vector2f& Vector2f::div(const Vector2f& v, Vector2f& dest) const {
		dest.x = this->x / v.getX();
		dest.y = this->y / v.getY();
		return dest;
	}

	/* EQUALITY CHECK */
	bool Vector2f::equals(const Vector2f& v) const {
		return this->x == v.getX() && this->y == v.getY();
	}

	/* TRIGONOMETRY */
	float Vector2f::length() const {
		return std::sqrtf(x * x + y * y);
	}

	float Vector2f::distance(float x, float y) const {
		float dx = this->x - x;
		float dy = this->y - y;
		return std::sqrtf(dx * dx + dy * dy);
	}

	float Vector2f::distance(const Vector2f& v) const {
		return distance(v.getX(), v.getY());
	}

	float Vector2f::angle(const Vector2f& v) const {
		float dot = x * v.getX() + y * v.getY();
		float det = x * v.getY() - y * v.getX();
		return std::atan2f(det, dot);
	}

	/* VECTOR MATH */
	float Vector2f::dot(float x, float y) const {
		return this->x * x + this->y * y;
	}

	float Vector2f::dot(const Vector2f& v) const {
		return x * v.getX() + y * v.getY();
	}

	Vector2f& Vector2f::normalize() {
		float invLength = 1.f / std::sqrtf(x * x + y * y);
		x *= invLength;
		y *= invLength;
		return *this;
	}

	Vector2f& Vector2f::normalize(Vector2f& dest) const {
		float invLength = 1.f / std::sqrtf(x * x + y * y);
		dest.x = x * invLength;
		dest.y = y * invLength;
		return dest;
	}

	Vector2f& Vector2f::normalize(float length) {
		float invLength = (1.f / std::sqrtf(x * x + y * y)) * length;
		x *= invLength;
		y *= invLength;
		return *this;
	}

	Vector2f& Vector2f::normalize(float length, Vector2f& dest) const {
		float invLength = (1.f / std::sqrtf(x * x + y * y)) * length;
		dest.x = x * invLength;
		dest.y = y * invLength;
		return dest;
	}

	Vector2f& Vector2f::perpendicular() {
		return set(y, x * -1);
	}

	/* EXTRA FUNCTIONS */
	Vector2f& Vector2f::negate() {
		this->x = -x;
		this->y = -y;
		return *this;
	}

	Vector2f& Vector2f::negate(Vector2f& dest) const {
		dest.x = -x;
		dest.y = -y;
		return dest;
	}

	Vector2f& Vector2f::zero() {
		this->x = this->y = 0.f;
		return *this;
	}

	/* OPERATOR OVERLOADING */
	bool Vector2f::operator==(const Vector2f& other) const {
		return equals(other);
	}

	bool Vector2f::operator!=(const Vector2f& other) const {
		return !equals(other);
	}

}