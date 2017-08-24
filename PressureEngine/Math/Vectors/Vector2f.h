#pragma once

struct Vector2f {

	// Vectors x component.
	float x;
	// Vectors y component.
	float y;

	/* CONSTRUCTORS */
	Vector2f();
	Vector2f(float d);
	Vector2f(float x, float y);

	/* GETTERS */
	float getX();
	float getY();

	/* SETTERS */
	Vector2f& set(float d);
	Vector2f& set(float x, float y);
	Vector2f& set(const Vector2f& v);

	/* ADDITION */
	Vector2f& add(float x, float y);
	Vector2f& add(float x, float y, Vector2f& dest);
	Vector2f& add(const Vector2f& v);
	Vector2f& add(const Vector2f&, Vector2f& dest);

	/* SUBTRACTION */
	Vector2f& sub(float x, float y);
	Vector2f& sub(float x, float y, Vector2f& dest);
	Vector2f& sub(const Vector2f& v);
	Vector2f& sub(const Vector2f& v, Vector2f& dest);

	/* MULTIPLICATION */
	Vector2f& mul(float scalar);
	Vector2f& mul(float scalar, Vector2f& dest);
	Vector2f& mul(float x, float y);
	Vector2f& mul(float x, float y, Vector2f& dest);
	Vector2f& mul(const Vector2f& v);
	Vector2f& mul(const Vector2f& v, Vector2f& dest);

	/* EQUALITY CHECK */
	bool equals(const Vector2f& v);

	/* TRIGONOMETRY */
	float length();
	float distance(float x, float y);
	float distance(const Vector2f& v);
	float angle(const Vector2f& v);

	/* VECTOR MATH */
	float dot(const Vector2f& v);
	Vector2f& normalize();
	Vector2f& normalize(float length);
	Vector2f& normalize(float length, Vector2f& dest);
	Vector2f& normalize(Vector2f& dest);
	Vector2f& perpendicular();

	/* EXTRA FUNCTIONS */
	Vector2f& negate();
	Vector2f& negate(Vector2f& dest);
	Vector2f& zero();
	//const char* toString(); //implement later?

	/* OPERATOR OVERLOADING */
	//friend Vector2f& operator+(Vector2f& left, const Vector2f& right);
	//friend Vector2f& operator-(Vector2f& left, const Vector2f& right);
	//friend Vector2f& operator*(Vector2f& left, const Vector2f& right);
	//friend Vector2f& operator/(Vector2f& left, const Vector2f& right);

	//friend bool operator==(Vector2f& left, const Vector2f& right);
	//friend bool operator!=(Vector2f& left, const Vector2f& right);

};