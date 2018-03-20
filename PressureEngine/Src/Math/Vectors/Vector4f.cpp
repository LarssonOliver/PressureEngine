#include "Vector4f.h"

#include <array>
#include <cmath>
#include "../Math.h"

namespace Pressure {

	/* CONSTRUCTORS */
	Vector4f::Vector4f() : x(0.f), y(0.f), z(0.f), w(0.f) { }

	Vector4f::Vector4f(float d) : x(d), y(d), z(d), w(d) { }

	Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

	Vector4f::Vector4f(const Vector2f& v, float z, float w) : x(v.getX()), y(v.getY()), z(z), w(w) { }

	Vector4f::Vector4f(const Vector3f& v, float w) : x(v.getX()), y(v.getY()), z(v.getZ()), w(w) { }

	/* GETTERS */
	float Vector4f::getX() const {
		return x;
	}

	float Vector4f::getY() const {
		return y;
	}

	float Vector4f::getZ() const {
		return z;
	}

	float Vector4f::getW() const {
		return w;
	}

	Vector2f Vector4f::getXY() const {
		return Vector2f(x, y);
	}

	Vector3f Vector4f::getXYZ() const {
		return Vector3f(x, y, z);
	}

	/* SETTERS */
	Vector4f& Vector4f::set(float d) {
		this->x = d;
		this->y = d;
		this->z = d;
		this->w = d;
		return *this;
	}

	Vector4f& Vector4f::set(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return *this;
	}

	Vector4f& Vector4f::set(const Vector2f& v, float x, float w) {
		this->x = v.getX();
		this->y = v.getY();
		this->z = z;
		this->w = w;
		return *this;
	}

	Vector4f& Vector4f::set(const Vector3f& v, float w) {
		this->x = v.getX();
		this->y = v.getY();
		this->z = v.getZ();
		this->w = w;
		return *this;
	}

	Vector4f& Vector4f::set(const Vector4f& v) {
		this->x = v.getX();
		this->y = v.getY();
		this->z = v.getZ();
		this->w = v.getW();
		return *this;
	}

	Vector4f& Vector4f::setX(float x) {
		this->x = x;
		return *this;
	}

	Vector4f& Vector4f::setY(float y) {
		this->y = y;
		return *this;
	}

	Vector4f& Vector4f::setZ(float z) {
		this->z = z;
		return *this;
	}

	Vector4f& Vector4f::setW(float w) {
		this->w = w;
		return *this;
	}

	/* ADDITION */
	Vector4f& Vector4f::add(float x, float y, float z, float w) {
		this->x += x;
		this->y += y;
		this->z += z;
		this->w += w;
		return *this;
	}

	Vector4f& Vector4f::add(float x, float y, float z, float w, Vector4f& dest) const {
		dest.x = this->x + x;
		dest.y = this->y + y;
		dest.z = this->z + z;
		dest.w = this->w + w;
		return dest;
	}

	Vector4f& Vector4f::add(const Vector4f& v) {
		this->x += v.getX();
		this->y += v.getY();
		this->z += v.getZ();
		this->w += v.getW();
		return *this;
	}

	Vector4f& Vector4f::add(const Vector4f& v, Vector4f& dest) const {
		dest.x = this->x + v.getX();
		dest.y = this->y + v.getY();
		dest.z = this->z + v.getZ();
		dest.w = this->w + v.getW();
		return dest;
	}

	/* SUBTRACTION */
	Vector4f& Vector4f::sub(float x, float y, float z, float w) {
		this->x -= x;
		this->y -= y;
		this->z -= z;
		this->w -= w;
		return *this;
	}

	Vector4f& Vector4f::sub(float x, float y, float z, float w, Vector4f& dest) const {
		dest.x = this->x - x;
		dest.y = this->y - y;
		dest.z = this->z - z;
		dest.w = this->w - w;
		return dest;
	}

	Vector4f& Vector4f::sub(const Vector4f& v) {
		this->x -= v.getX();
		this->y -= v.getY();
		this->z -= v.getZ();
		this->w -= v.getW();
		return *this;
	}

	Vector4f& Vector4f::sub(const Vector4f& v, Vector4f& dest) const {
		dest.x = this->x - v.getX();
		dest.y = this->y - v.getY();
		dest.z = this->z - v.getZ();
		dest.w = this->w - v.getW();
		return dest;
	}

	/* MULTIPLICATION */
	Vector4f& Vector4f::mul(float scalar) {
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		this->w *= scalar;
		return *this;
	}

	Vector4f& Vector4f::mul(float scalar, Vector4f& dest) const {
		dest.x = this->x * scalar;
		dest.y = this->y * scalar;
		dest.z = this->z * scalar;
		dest.w = this->w * scalar;
		return dest;
	}

	Vector4f& Vector4f::mul(float x, float y, float z, float w) {
		this->x *= x;
		this->y *= y;
		this->z *= z;
		this->w *= w;
		return *this;
	}

	Vector4f& Vector4f::mul(float x, float y, float z, float w, Vector4f& dest) const {
		dest.x = this->x * x;
		dest.y = this->y * y;
		dest.z = this->z * z;
		dest.w = this->w * w;
		return dest;
	}

	Vector4f& Vector4f::mul(const Vector4f& v) {
		this->x *= v.getX();
		this->y *= v.getY();
		this->z *= v.getZ();
		this->w *= v.getW();
		return *this;
	}

	Vector4f& Vector4f::mul(const Vector4f& v, Vector4f& dest) const {
		dest.x = this->x * v.getX();
		dest.y = this->y * v.getY();
		dest.z = this->z * v.getZ();
		dest.w = this->w * v.getW();
		return dest;
	}

	/* DIVISION */
	Vector4f& Vector4f::div(float scalar) {
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		this->w /= scalar;
		return *this;
	}

	Vector4f& Vector4f::div(float scalar, Vector4f& dest) const {
		dest.x = this->x / scalar;
		dest.y = this->y / scalar;
		dest.z = this->z / scalar;
		dest.w = this->w / scalar;
		return dest;
	}

	Vector4f& Vector4f::div(float x, float y, float z, float w) {
		this->x /= x;
		this->y /= y;
		this->z /= z;
		this->w /= w;
		return *this;
	}

	Vector4f& Vector4f::div(float x, float y, float z, float w, Vector4f& dest) const {
		dest.x = this->x / x;
		dest.y = this->y / y;
		dest.z = this->z / z;
		dest.w = this->w / w;
		return dest;
	}

	Vector4f& Vector4f::div(const Vector4f& v) {
		this->x /= v.getX();
		this->y /= v.getY();
		this->z /= v.getZ();
		this->w /= v.getW();
		return *this;
	}

	Vector4f& Vector4f::div(const Vector4f& v, Vector4f& dest) const {
		dest.x = this->x / v.getX();
		dest.y = this->y / v.getY();
		dest.z = this->z / v.getZ();
		dest.w = this->w / v.getW();
		return dest;
	}

	/* EQUALITY CHECK */
	bool Vector4f::equals(const Vector4f& v) const {
		return this->x == v.getX()
			&& this->y == v.getY()
			&& this->z == v.getZ()
			&& this->w == v.getW();
	}

	/* TRIGONOMETRY */
	float Vector4f::length() const {
		return std::sqrtf(lengthSquared());
	}

	float Vector4f::lengthSquared() const {
		return x * x + y * y + z * z + w * w;
	}

	float Vector4f::distance(float x, float y, float z, float w) const {
		float dx = this->x - x;
		float dy = this->y - y;
		float dz = this->z - z;
		float dw = this->w - w;
		return std::sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
	}

	float Vector4f::distance(const Vector4f& v) const {
		float dx = v.getX() - x;
		float dy = v.getY() - y;
		float dz = v.getZ() - z;
		float dw = v.getZ() - w;
		return std::sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
	}

	/* VECTOR MATH */
	float Vector4f::dot(float x, float y, float z, float w) const {
		return this->x * x + this->y * y + this->z * z + this->w * w;
	}

	float Vector4f::dot(const Vector4f& v) const {
		return v.getX() * x + v.getY() * y + v.getZ() * z + v.getW() * w;
	}

	Vector4f& Vector4f::normalize() {
		float invLength = 1.f / length();
		x *= invLength;
		y *= invLength;
		z *= invLength;
		w *= invLength;
		return *this;
	}

	Vector4f& Vector4f::normalize(Vector4f& dest) const {
		float invLength = 1.f / length();
		dest.x = x * invLength;
		dest.y = y * invLength;
		dest.z = z * invLength;
		dest.w = w * invLength;
		return dest;
	}

	Vector4f& Vector4f::normalize(float length) {
		float invLength = 1.f / this->length() * length;
		x *= invLength;
		y *= invLength;
		z *= invLength;
		w *= invLength;
		return *this;
	}

	Vector4f& Vector4f::normalize(float length, Vector4f& dest) const {
		float invLength = 1.f / this->length() * length;
		dest.x = x * invLength;
		dest.y = y * invLength;
		dest.z = z * invLength;
		dest.w = w * invLength;
		return dest;
	}

	Vector4f& Vector4f::normalize3() {
		float invLength = 1.f / std::sqrtf(x * x + y * y + z * z);
		x *= invLength;
		y *= invLength;
		z *= invLength;
		w *= invLength;
		return *this;
	}

	/* ROTATION */
	Vector4f& Vector4f::rotateX(float angle) {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		this->y = y * cos - z * sin;
		this->z = y * sin + z * cos;
		return *this;
	}

	Vector4f& Vector4f::rotateX(float angle, Vector4f& dest) const {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		dest.x = x;
		dest.y = y * cos - z * sin;
		dest.z = y * sin + z * cos;
		dest.w = w;
		return dest;
	}

	Vector4f& Vector4f::rotateY(float angle) {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		this->x = x * cos + z * sin;
		this->z = -x * sin + z * cos;
		return *this;
	}

	Vector4f& Vector4f::rotateY(float angle, Vector4f& dest) const {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		dest.x = x * cos + z * sin;
		dest.y = y;
		dest.z = -x * sin + z * cos;
		dest.w = w;
		return dest;
	}

	Vector4f& Vector4f::rotateZ(float angle) {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		this->x = x * cos - y * sin;
		this->y = x * sin + y * cos;
		return *this;
	}

	Vector4f& Vector4f::rotateZ(float angle, Vector4f& dest) const {
		float sin = std::sinf(angle * 0.5f);
		float cos = std::cosf(angle * 0.5f);
		dest.x = x * cos - y * sin;
		dest.y = x * sin + y * cos;
		dest.z = z;
		dest.w = w;
		return dest;
	}

	/* EXTRA FUNCTIONS */
	Vector4f& Vector4f::negate() {
		return set(-x, -y, -z, -w);
	}

	Vector4f& Vector4f::negate(Vector4f& dest) const {
		return dest.set(-x, -y, -z, -w);
	}

	Vector4f& Vector4f::zero() {
		return set(0);
	}

	/* OPERATOR OVERLOADING */
	bool Vector4f::operator==(const Vector4f& other) const {
		return equals(other);
	}

	bool Vector4f::operator!=(const Vector4f& other) const {
		return !equals(other);
	}

	float& Vector4f::operator[](int id) {
		return std::array<float, 4>{ x, y, z, w }[id];
	}

	std::ostream& operator<<(std::ostream& os, const Vector4f& vec) {
		os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
		return os;
	}

}