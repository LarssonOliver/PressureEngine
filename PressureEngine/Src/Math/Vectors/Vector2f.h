#pragma once

#include "../../DllExport.h"
#include <ostream>

namespace Pressure {

	struct PRESSURE_API Vector2f {

		// Vectors x component.
		float x;
		// Vectors y component.
		float y;

		/* CONSTRUCTORS */
		Vector2f();
		Vector2f(float d);
		Vector2f(float x, float y);

		/* GETTERS */
		float getX() const;
		float getY() const;

		/* SETTERS */
		Vector2f& set(float d);
		Vector2f& set(float x, float y);
		Vector2f& set(const Vector2f& v);
		Vector2f& setX(float x);
		Vector2f& setY(float y);

		/* ADDITION */
		Vector2f& add(float x, float y);
		Vector2f& add(float x, float y, Vector2f& dest) const;
		Vector2f& add(const Vector2f& v);
		Vector2f& add(const Vector2f&, Vector2f& dest) const;

		/* SUBTRACTION */
		Vector2f& sub(float x, float y);
		Vector2f& sub(float x, float y, Vector2f& dest) const;
		Vector2f& sub(const Vector2f& v);
		Vector2f& sub(const Vector2f& v, Vector2f& dest) const;

		/* MULTIPLICATION */
		Vector2f& mul(float scalar);
		Vector2f& mul(float scalar, Vector2f& dest) const;
		Vector2f& mul(float x, float y);
		Vector2f& mul(float x, float y, Vector2f& dest) const;
		Vector2f& mul(const Vector2f& v);
		Vector2f& mul(const Vector2f& v, Vector2f& dest) const;

		/* DIVISION */
		Vector2f& div(float scalar);
		Vector2f& div(float scalar, Vector2f& dest) const;
		Vector2f& div(float x, float y);
		Vector2f& div(float x, float y, Vector2f& dest) const;
		Vector2f& div(const Vector2f& v);
		Vector2f& div(const Vector2f& v, Vector2f& dest) const;

		/* EQUALITY CHECK */
		bool equals(const Vector2f& v) const;

		/* TRIGONOMETRY */
		float length() const;
		float distance(float x, float y) const;
		float distance(const Vector2f& v) const;
		float angle(const Vector2f& v) const;

		/* VECTOR MATH */
		float dot(float x, float y) const;
		float dot(const Vector2f& v) const;
		Vector2f& normalize();
		Vector2f& normalize(Vector2f& dest) const;
		Vector2f& normalize(float length);
		Vector2f& normalize(float length, Vector2f& dest) const;
		Vector2f& perpendicular();

		/* EXTRA FUNCTIONS */
		Vector2f& negate();
		Vector2f& negate(Vector2f& dest) const;
		Vector2f& zero();

		/* OPERATOR OVERLOADING */
		bool operator==(const Vector2f& other) const;
		bool operator!=(const Vector2f& other) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector2f& vec);

	};

}