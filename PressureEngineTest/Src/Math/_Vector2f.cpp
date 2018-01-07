#include "../../stdafx.h"
#include "PressureEngine\Src\Math\Vectors\Vector2f.h"

namespace PressureEngineTest {

	using namespace Pressure;

	TEST_CLASS(_Vector2f) {

		TEST_METHOD(_constructor_0) {
			Vector2f v;
			Assert::IsTrue(v.x == 0 && v.y == 0);		
		}

		TEST_METHOD(_constructor_1) {
			Vector2f v(2, 3);
			Assert::IsTrue(v.x == 2 && v.getX() == 2 && v.y == 3 && v.getY() == 3);
		}

		TEST_METHOD(_constructor_2) {
			Vector2f v(4);
			Assert::IsTrue(v.x == 4 && v.y == 4);
		}

		TEST_METHOD(_set_0) {
			Vector2f v(3);
			v.set(4);
			Assert::IsTrue(v.x == 4 && v.y == 4);
		}

		TEST_METHOD(_set_1) {
			Vector2f v(3);
			v.set(4, 5);
			Assert::IsTrue(v.x == 4 && v.y == 5);
		}

		TEST_METHOD(_set_2) {
			Vector2f v(3);
			Vector2f w(2, 4);
			v.set(w);
			Assert::IsTrue(v.x == 2 && v.y == 4 && v == w);
		}

		TEST_METHOD(_setX) {
			Vector2f v(3);
			v.setX(4);
			Assert::IsTrue(v.x == 4 && v.y == 3);
		}

		TEST_METHOD(_setY) {
			Vector2f v(3);
			v.setY(4);
			Assert::IsTrue(v.x == 3 && v.y == 4);
		}

		TEST_METHOD(_equals_0) {
			Vector2f v(3, 4);
			Vector2f w(3, 4);
			Assert::IsTrue(v.equals(w));
		}

		TEST_METHOD(_equals_1) {
			Vector2f v(3, 4);
			Vector2f w(3, 4);
			Assert::IsTrue(v == w);
		}

		TEST_METHOD(_equals_2) {
			Vector2f v(3, 4);
			Vector2f w(3, 4);
			Assert::IsFalse(v != w);
		}

		TEST_METHOD(_add_0) {
			Vector2f v(2, 3);
			v.add(3, 5);
			Assert::IsTrue(v == Vector2f(5, 8));
		}

		TEST_METHOD(_add_1) {
			Vector2f v(2, 3);
			Vector2f d;
			v.add(3, 5, d);
			Assert::IsTrue(d == Vector2f(5, 8) && v == Vector2f(2, 3));		
		}

		TEST_METHOD(_add_2) {
			Vector2f v(2, 3);
			Vector2f w(3, 5);
			v.add(w);
			Assert::IsTrue(v == Vector2f(5, 8) && w == Vector2f(3, 5));
		}

		TEST_METHOD(_add_3) {
			Vector2f v(2, 3);
			Vector2f w(3, 5);
			Vector2f d;
			v.add(w, d);
			Assert::IsTrue(d == Vector2f(5, 8) && v == Vector2f(2, 3) && w == Vector2f(3, 5));
		}

		TEST_METHOD(_sub_0) {
			Vector2f v(2, 3);
			v.sub(3, 5);
			Assert::IsTrue(v == Vector2f(-1, -2));
		}

		TEST_METHOD(_sub_1) {
			Vector2f v(2, 3);
			Vector2f d;
			v.sub(3, 5, d);
			Assert::IsTrue(d == Vector2f(-1, -2) && v == Vector2f(2, 3));
		}

		TEST_METHOD(_sub_2) {
			Vector2f v(2, 3);
			Vector2f w(3, 5);
			v.sub(w);
			Assert::IsTrue(v == Vector2f(-1, -2) && w == Vector2f(3, 5));
		}

		TEST_METHOD(_sub_3) {
			Vector2f v(2, 3);
			Vector2f w(3, 5);
			Vector2f d;
			v.sub(w, d);
			Assert::IsTrue(d == Vector2f(-1, -2) && v == Vector2f(2, 3) && w == Vector2f(3, 5));
		}

		TEST_METHOD(_mul_0) {
			Vector2f v(4, 8);
			v.mul(2);
			Assert::IsTrue(v == Vector2f(8, 16));
		}

		TEST_METHOD(_mul_1) {
			Vector2f v(4, 8);
			Vector2f d;
			v.mul(2, d);
			Assert::IsTrue(d == Vector2f(8, 16) && v == Vector2f(4, 8));
		}

		TEST_METHOD(_mul_2) {
			Vector2f v(4, 8);
			v.mul(2, 3);
			Assert::IsTrue(v == Vector2f(8, 24));
		}

		TEST_METHOD(_mul_3) {
			Vector2f v(4, 8);
			Vector2f d;
			v.mul(2, 3, d);
			Assert::IsTrue(d == Vector2f(8, 24) && v == Vector2f(4, 8));
		}

		TEST_METHOD(_mul_4) {
			Vector2f v(4, 8);
			Vector2f w(2, 3);
			v.mul(2, 3);
			Assert::IsTrue(v == Vector2f(8, 24) && w == Vector2f(2, 3));
		}

		TEST_METHOD(_mul_5) {
			Vector2f v(4, 8);
			Vector2f w(2, 3);
			Vector2f d;
			v.mul(w, d);
			Assert::IsTrue(d == Vector2f(8, 24) && v == Vector2f(4, 8) && w == Vector2f(2, 3));
		}

		TEST_METHOD(_div_0) {
			Vector2f v(4, 8);
			v.div(2);
			Assert::IsTrue(v == Vector2f(2, 4));
		}

		TEST_METHOD(_div_1) {
			Vector2f v(4, 8);
			Vector2f d;
			v.div(2, d);
			Assert::IsTrue(d == Vector2f(2, 4) && v == Vector2f(4, 8));
		}

		TEST_METHOD(_div_2) {
			Vector2f v(4, 8);
			v.div(2, 8);
			Assert::IsTrue(v == Vector2f(2, 1));
		}

		TEST_METHOD(_div_3) {
			Vector2f v(4, 8);
			Vector2f d;
			v.div(2, 8, d);
			Assert::IsTrue(d == Vector2f(2, 1) && v == Vector2f(4, 8));
		}

		TEST_METHOD(_div_4) {
			Vector2f v(4, 8);
			Vector2f w(2, 8);
			v.div(w);
			Assert::IsTrue(v == Vector2f(2, 1) && w == Vector2f(2, 8));
		}

		TEST_METHOD(_div_5) {
			Vector2f v(4, 8);
			Vector2f w(2, 8);
			Vector2f d;
			v.div(w, d);
			Assert::IsTrue(d == Vector2f(2, 1) && v == Vector2f(4, 8) && w == Vector2f(2, 8));
		}

		TEST_METHOD(_length) {
			Vector2f v(6, 8);
			Assert::AreEqual(v.length(), 10.f);
		}

		TEST_METHOD(_distance_0) {
			Vector2f v(2, 3);
			Assert::AreEqual(v.distance(4, 5), std::sqrtf(8));
		}

		TEST_METHOD(_distance_1) {
			Vector2f v(2, 3);
			Vector2f w(4, 5);
			Assert::AreEqual(v.distance(w), std::sqrtf(8));
		}

		TEST_METHOD(_angle) {
			Vector2f v(1, 0);
			Vector2f w(0, 1);
			Assert::AreEqual(v.angle(w), 3.14159265358979323846f / 2);
		}

		TEST_METHOD(_dot_0) {
			Vector2f v(2, 4);
			Assert::AreEqual(v.dot(3, 5), (float)2 * 3 + 4 * 5);
		}

		TEST_METHOD(_dot_1) {
			Vector2f v(2, 4);
			Vector2f w(3, 5);
			Assert::AreEqual(v.dot(w), (float)2 * 3 + 4 * 5);
		}

		TEST_METHOD(_normalize_0) {
			Vector2f v(8, 6);
			Assert::IsTrue(v.normalize() == Vector2f(.8, .6));
		}

		TEST_METHOD(_normalize_1) {
			Vector2f v(8, 6);
			Vector2f d;
			v.normalize(d);
			Assert::IsTrue(v == Vector2f(8, 6) && d == Vector2f(.8, .6));
		}

		TEST_METHOD(_normalize_2) {
			Vector2f v(8, 6);
			Assert::IsTrue(v.normalize(2) == Vector2f(1.6, 1.2));
		}

		TEST_METHOD(_normalize_3) {
			Vector2f v(8, 6);
			Vector2f d;
			v.normalize(2, d);
			Assert::IsTrue(v == Vector2f(8, 6) && d == Vector2f(1.6, 1.2));
		}

		TEST_METHOD(_negate_0) {
			Vector2f v(2);
			Assert::IsTrue(v.negate() == Vector2f(-2));
		}

		TEST_METHOD(_negate_1) {
			Vector2f v(2);
			Vector2f d;
			v.negate(d);
			Assert::IsTrue(v == Vector2f(2) && d == Vector2f(-2));
		}
	};

}