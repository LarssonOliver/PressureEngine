#include "Vector3f.h"

#include <cmath>
#include <array>
#include "../Math.h"

namespace Pressure {

	/* CONSTRUCTORS */
	Vector3f::Vector3f() : x(0.f), y(0.f), z(0.f) { }

	Vector3f::Vector3f(float d) : x(d), y(d), z(d) { }

	Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) { }

	Vector3f::Vector3f(const Vector2f& v, float z) : x(v.getX()), y(v.getY()), z(z) { }

	/* GETTERS */
	float Vector3f::getX() const {
		return x;
	}

	float Vector3f::getY() const {
		return y;
	}

	float Vector3f::getZ() const {
		return z;
	}

	Vector2f Vector3f::getXY() const {
		return Vector2f(x, y);
	}

	/* SETTERS */
	Vector3f& Vector3f::set(float d) {
		this->x = d;
		this->y = d;
		this->z = d;
		return *this;
	}

	Vector3f& Vector3f::set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

	Vector3f& Vector3f::set(const Vector2f& v, float z) {
		this->x = v.getX();
		this->y = v.getY();
		this->z = z;
		return *this;
	}

	Vector3f& Vector3f::set(const Vector3f& v) {
		this->x = v.getX();
		this->y = v.getY();
		this->z = v.getZ();
		return *this;
	}

	Vector3f& Vector3f::setX(float x) {
		this->x = x;
		return *this;
	}

	Vector3f& Vector3f::setY(float y) {
		this->y = y;
		return *this;
	}

	Vector3f& Vector3f::setZ(float z) {
		this->z = z;
		return *this;
	}

	/* ADDITION */
	Vector3f& Vector3f::add(float x, float y, float z) {
		this->x += x;
		this->y += y;
		this->z += z;
		return *this;
	}

	Vector3f& Vector3f::add(float x, float y, float z, Vector3f& dest) const {
		dest.x = this->x + x;
		dest.y = this->y + y;
		dest.z = this->z + z;
		return dest;
	}

	Vector3f& Vector3f::add(const Vector3f& v) {
		this->x += v.getX();
		this->y += v.getY();
		this->z += v.getZ();
		return *this;
	}

	Vector3f& Vector3f::add(const Vector3f& v, Vector3f& dest) const {
		dest.x = this->x + v.getX();
		dest.y = this->y + v.getY();
		dest.z = this->z + v.getZ();
		return dest;
	}

	/* SUBTRACTION */
	Vector3f& Vector3f::sub(float x, float y, float z) {
		this->x -= x;
		this->y -= y;
		this->z -= z;
		return *this;
	}

	Vector3f& Vector3f::sub(float x, float y, float z, Vector3f& dest) const {
		dest.x = this->x - x;
		dest.y = this->y - y;
		dest.z = this->z - z;
		return dest;
	}

	Vector3f& Vector3f::sub(const Vector3f& v) {
		this->x -= v.getX();
		this->y -= v.getY();
		this->z -= v.getZ();
		return *this;
	}

	Vector3f& Vector3f::sub(const Vector3f& v, Vector3f& dest) const {
		dest.x = this->x - v.getX();
		dest.y = this->y - v.getY();
		dest.z = this->z - v.getZ();
		return dest;
	}

	/* MULTIPLICATION */
	Vector3f& Vector3f::mul(float scalar) {
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	Vector3f& Vector3f::mul(float scalar, Vector3f& dest) const {
		dest.x = this->x * scalar;
		dest.y = this->y * scalar;
		dest.z = this->z * scalar;
		return dest;
	}

	Vector3f& Vector3f::mul(float x, float y, float z) {
		this->x *= x;
		this->y *= y;
		this->z *= z;
		return *this;
	}

	Vector3f& Vector3f::mul(float x, float y, float z, Vector3f& dest) const {
		dest.x = this->x * x;
		dest.y = this->y * y;
		dest.z = this->z * z;
		return dest;
	}

	Vector3f& Vector3f::mul(const Vector3f& v) {
		this->x *= v.getX();
		this->y *= v.getY();
		this->z *= v.getZ();
		return *this;
	}

	Vector3f& Vector3f::mul(const Vector3f& v, Vector3f& dest) const {
		dest.x = this->x * v.getX();
		dest.y = this->y * v.getY();
		dest.z = this->z * v.getZ();
		return dest;
	}

	/* DIVISION */
	Vector3f& Vector3f::div(float scalar) {
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	Vector3f& Vector3f::div(float scalar, Vector3f& dest) const {
		dest.x = this->x / scalar;
		dest.y = this->y / scalar;
		dest.z = this->z / scalar;
		return dest;
	}

	Vector3f& Vector3f::div(float x, float y, float z) {
		this->x /= x;
		this->y /= y;
		this->z /= z;
		return *this;
	}

	Vector3f& Vector3f::div(float x, float y, float z, Vector3f& dest) const {
		dest.x = this->x / x;
		dest.y = this->y / y;
		dest.z = this->z / z;
		return dest;
	}

	Vector3f& Vector3f::div(const Vector3f& v) {
		this->x /= v.getX();
		this->y /= v.getY();
		this->z /= v.getZ();
		return *this;
	}

	Vector3f& Vector3f::div(const Vector3f& v, Vector3f& dest) const {
		dest.x = this->x / v.getX();
		dest.y = this->y / v.getY();
		dest.z = this->z / v.getZ();
		return dest;
	}

	/* EQUALITY CHECK */
	bool Vector3f::equals(const Vector3f& v) const {
		return this->x == v.getX()
			&& this->y == v.getY()
			&& this->z == v.getZ();
	}

	/* TRIGONOMETRY */
	float Vector3f::length() const {
		return std::sqrtf(x * x + y * y + z * z);
	}

	float Vector3f::lengthSquared() const {
		return x * x + y * y + z * z;
	}

	float Vector3f::distance(float x, float y, float z) const {
		float dx = this->x - x;
		float dy = this->y - y;
		float dz = this->z - z;
		return std::sqrtf(dx * dx + dy * dy + dz * dz);
	}

	float Vector3f::distance(const Vector3f& v) const {
		return distance(v.getX(), v.getY(), v.getZ());
	}

	float Vector3f::angle(const Vector3f& v) const {
		float dot = x * v.getX() + y * v.getY() + z * v.getZ();
		float det = x * v.getY() - y * v.getX() - z * v.getZ();
		return std::atan2f(det, dot);
	}

	/* VECTOR MATH */
	float Vector3f::dot(float x, float y, float z) const {
		return this->x * x + this->y * y + this->z * x;
	}

	float Vector3f::dot(const Vector3f& v) const {
		return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
	}

	Vector3f& Vector3f::normalize() {
		float invLength = 1.f / length();
		x *= invLength;
		y *= invLength;
		z *= invLength;
		return *this;
	}

	Vector3f& Vector3f::normalize(Vector3f& dest) const {
		float invLength = 1.f / length();
		dest.x = x * invLength;
		dest.y = y * invLength;
		dest.z = z * invLength;
		return dest;
	}

	Vector3f& Vector3f::normalize(float length) {
		float invLength = 1.f / this->length() * length;
		x *= invLength;
		y *= invLength;
		z *= invLength;
		return *this;
	}

	Vector3f& Vector3f::normalize(float length, Vector3f& dest) const {
		float invLength = 1.f / this->length() * length;
		dest.x = x * invLength;
		dest.y = y * invLength;
		dest.z = z * invLength;
		return dest;
	}

	Vector3f& Vector3f::reflect(float x, float y, float z) {
		float dot = this->dot(x, y, z);
		this->x = this->x - (dot + dot) * x;
		this->y = this->y - (dot + dot) * y;
		this->z = this->z - (dot + dot) * z;
		return *this;
	}

	Vector3f& Vector3f::reflect(float x, float y, float z, Vector3f& dest) const {
		float dot = this->dot(x, y, z);
		dest.x = this->x - (dot + dot) * x;
		dest.y = this->y - (dot + dot) * y;
		dest.z = this->z - (dot + dot) * z;
		return dest;
	}

	Vector3f& Vector3f::reflect(const Vector3f& normal) {
		float dot = this->dot(normal);
		this->x = this->x - (dot + dot) * normal.getX();
		this->y = this->y - (dot + dot) * normal.getY();
		this->z = this->z - (dot + dot) * normal.getZ();
		return *this;
	}

	Vector3f& Vector3f::reflect(const Vector3f& normal, Vector3f& dest) const {
		float dot = this->dot(normal);
		dest.x = this->x - (dot + dot) * normal.getX();
		dest.y = this->y - (dot + dot) * normal.getY();
		dest.z = this->z - (dot + dot) * normal.getZ();
		return dest;
	}

	Vector3f& Vector3f::cross(const Vector3f& v) {
		return cross(v, *this);
	}

	Vector3f& Vector3f::cross(const Vector3f& v, Vector3f& dest) const {
		return dest.set(
			y * v.getZ() - z * v.getY(),
			z * v.getX() - x * v.getZ(),
			x * v.getY() - y * v.getX()
		);
	}

	/* ROTATION */
	Vector3f& Vector3f::rotateX(float angle) {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		this->y = y * cos - z * sin;
		this->z = y * sin + z * cos;
		return *this;
	}

	Vector3f& Vector3f::rotateX(float angle, Vector3f& dest) const {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		dest.x = x;
		dest.y = y * cos - z * sin;
		dest.z = y * sin + z * cos;
		return dest;
	}

	Vector3f& Vector3f::rotateY(float angle) {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		this->x = x * cos + z * sin;
		this->z = -x * sin + z * cos;
		return *this;
	}

	Vector3f& Vector3f::rotateY(float angle, Vector3f& dest) const {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		dest.x = x * cos + z * sin;
		dest.y = y;
		dest.z = -x * sin + z * cos;
		return dest;
	}

	Vector3f& Vector3f::rotateZ(float angle) {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		this->x = x * cos - y * sin;
		this->y = x * sin + y * cos;
		return *this;
	}

	Vector3f& Vector3f::rotateZ(float angle, Vector3f& dest) const {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		dest.x = x * cos - y * sin;
		dest.y = x * sin + y * cos;
		dest.z = z;
		return dest;
	}

	/* EXTRA FUNCTIONS */
	Vector3f& Vector3f::negate() {
		this->x = -x;
		this->y = -y;
		this->z = -z;
		return *this;
	}

	Vector3f& Vector3f::negate(Vector3f& dest) const {
		return dest.set(-x, -y, -z);
	}

	Vector3f& Vector3f::zero() {
		return set(0.f);
	}

	/* OPERATOR OVERLOADING */
	bool Vector3f::operator==(const Vector3f& other) const {
		return equals(other);
	}

	bool Vector3f::operator!=(const Vector3f& other) const {
		return !equals(other);
	}

	bool Vector3f::operator<(const Vector3f& other) const {
		return (x < other.x && y < other.y && z < other.z);
	}

	bool Vector3f::operator>(const Vector3f& other) const {
		return (x > other.x && y > other.y && z > other.z);
	}

	float& Vector3f::operator[](int id) {
		return std::array<float, 3>{ x, y, z }[id];
	}

	std::ostream& operator<<(std::ostream& os, const Vector3f& vec) {
		os << vec.x << ", " << vec.y << ", " << vec.z;
		return os;
	}

}