#pragma once
#include "Vector2f.h"

namespace Pressure {

	struct Vector3f {

		// Vectors x component.
		float x;
		// Vectors y component.
		float y;
		// Vectors z component.
		float z;

		/* CONSTRUCTORS */
		Vector3f();
		Vector3f(float d);
		Vector3f(float x, float y, float z);
		Vector3f(const Vector2f& v, float z);

		/* GETTERS */
		float getX() const;
		float getY() const;
		float getZ() const;

		/* SETTERS */
		Vector3f& set(float d);
		Vector3f& set(float x, float y, float z);
		Vector3f& set(const Vector2f& v, float z);
		Vector3f& set(const Vector3f& v);
		Vector3f& setX(float x);
		Vector3f& setY(float y);
		Vector3f& setZ(float z);

		/* ADDITION */
		Vector3f& add(float x, float y, float z);
		Vector3f& add(float x, float y, float z, Vector3f& dest) const;
		Vector3f& add(const Vector3f& v);
		Vector3f& add(const Vector3f&, Vector3f& dest) const;

		/* SUBTRACTION */
		Vector3f& sub(float x, float y, float z);
		Vector3f& sub(float x, float y, float z, Vector3f& dest) const;
		Vector3f& sub(const Vector3f& v);
		Vector3f& sub(const Vector3f& v, Vector3f& dest) const;

		/* MULTIPLICATION */
		Vector3f& mul(float scalar);
		Vector3f& mul(float scalar, Vector3f& dest) const;
		Vector3f& mul(float x, float y, float z);
		Vector3f& mul(float x, float y, float z, Vector3f& dest) const;
		Vector3f& mul(const Vector3f& v);
		Vector3f& mul(const Vector3f& v, Vector3f& dest) const;

		/* DIVISION */
		Vector3f& div(float scalar);
		Vector3f& div(float scalar, Vector3f& dest) const;
		Vector3f& div(float x, float y, float z);
		Vector3f& div(float x, float y, float z, Vector3f& dest) const;
		Vector3f& div(const Vector3f& v);
		Vector3f& div(const Vector3f& v, Vector3f& dest) const;

		/* EQUALITY CHECK */
		bool equals(const Vector3f& v) const;

		/* TRIGONOMETRY */
		float length() const;
		float lengthSquared() const;
		float distance(float x, float y, float z) const;
		float distance(const Vector3f& v) const;
		Vector3f& scale(const float scalar);
		Vector3f& scale(const float scalar, Vector3f& dest) const;

		/* VECTOR MATH */
		float dot(float x, float y, float z) const;
		float dot(const Vector3f& v) const;
		Vector3f& normalize();
		Vector3f& normalize(Vector3f& dest) const;
		Vector3f& normalize(float length);
		Vector3f& normalize(float length, Vector3f& dest) const;
		Vector3f& reflect(float x, float y, float z);
		Vector3f& reflect(float x, float y, float z, Vector3f& dest) const;
		Vector3f& reflect(const Vector3f& normal);
		Vector3f& reflect(const Vector3f& normal, Vector3f& dest) const;

		/* ROTATION */
		Vector3f& rotateX(float angle);
		Vector3f& rotateX(float angle, Vector3f& dest) const;
		Vector3f& rotateY(float angle);
		Vector3f& rotateY(float angle, Vector3f& dest) const;
		Vector3f& rotateZ(float angle);
		Vector3f& rotateZ(float angle, Vector3f& dest) const;

		/* EXTRA FUNCTIONS */
		Vector3f& negate();
		Vector3f& negate(Vector3f& dest) const;
		Vector3f& zero();

		/* OPERATOR OVERLOADING */
		bool operator==(const Vector3f& other) const;
		bool operator!=(const Vector3f& other) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector3f& vec);

	};

}