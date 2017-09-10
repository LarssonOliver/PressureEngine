#pragma once
#include "Vector2f.h"
#include "Vector3f.h"

namespace Pressure {

	struct Vector4f {

		// Vectors x component.
		float x;
		// Vectors y component.
		float y;
		// Vectors z component.
		float z;
		// Vectors w component.
		float w;

		/* CONSTRUCTORS */
		Vector4f();
		Vector4f(float d);
		Vector4f(float x, float y, float z, float w);
		Vector4f(const Vector2f& v, float z, float w);
		Vector4f(const Vector3f& v, float w);

		/* GETTERS */
		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		/* SETTERS */
		Vector4f& set(float d);
		Vector4f& set(float x, float y, float z, float w);
		Vector4f& set(const Vector2f& v, float x, float w);
		Vector4f& set(const Vector3f& v, float w);
		Vector4f& set(const Vector4f& v);
		Vector4f& setX(float x);
		Vector4f& setY(float y);
		Vector4f& setZ(float z);
		Vector4f& setW(float w);

		/* ADDITION */
		Vector4f& add(float x, float y, float z, float w);
		Vector4f& add(float x, float y, float z, float w, Vector4f& dest) const;
		Vector4f& add(const Vector4f& v);
		Vector4f& add(const Vector4f&, Vector4f& dest) const;

		/* SUBTRACTION */
		Vector4f& sub(float x, float y, float z, float w);
		Vector4f& sub(float x, float y, float z, float w, Vector4f& dest) const;
		Vector4f& sub(const Vector4f& v);
		Vector4f& sub(const Vector4f& v, Vector4f& dest) const;

		/* MULTIPLICATION */
		Vector4f& mul(float scalar);
		Vector4f& mul(float scalar, Vector4f& dest) const;
		Vector4f& mul(float x, float y, float z, float w);
		Vector4f& mul(float x, float y, float z, float w, Vector4f& dest) const;
		Vector4f& mul(const Vector4f& v);
		Vector4f& mul(const Vector4f& v, Vector4f& dest) const;

		/* DIVISION */
		Vector4f& div(float scalar);
		Vector4f& div(float scalar, Vector4f& dest) const;
		Vector4f& div(float x, float y, float z, float w);
		Vector4f& div(float x, float y, float z, float w, Vector4f& dest) const;
		Vector4f& div(const Vector4f& v);
		Vector4f& div(const Vector4f& v, Vector4f& dest) const;

		/* EQUALITY CHECK */
		bool equals(const Vector4f& v) const;

		/* TRIGONOMETRY */
		float length() const;
		float distance(float x, float y, float z, float w) const;
		float distance(const Vector4f& v) const;

		/* VECTOR MATH */
		float dot(float x, float y, float z, float w) const;
		float dot(const Vector4f& v) const;
		Vector4f& normalize();
		Vector4f& normalize(Vector4f& dest) const;
		Vector4f& normalize(float length);
		Vector4f& normalize(float length, Vector4f& dest) const;
		Vector4f& normalize3();

		/* ROTATION */
		Vector4f& rotateX(float angle);
		Vector4f& rotateX(float angle, Vector4f& dest) const;
		Vector4f& rotateY(float angle);
		Vector4f& rotateY(float angle, Vector4f& dest) const;
		Vector4f& rotateZ(float angle);
		Vector4f& rotateZ(float angle, Vector4f& dest) const;

		/* EXTRA FUNCTIONS */
		Vector4f& negate();
		Vector4f& negate(Vector4f& dest) const;
		Vector4f& zero();

		/* OPERATOR OVERLOADING */
		bool operator==(const Vector4f& other) const;
		bool operator!=(const Vector4f& other) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector4f& vec);

	};

}