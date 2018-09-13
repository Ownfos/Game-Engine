#include "Vector.h"

namespace engine {

	Vector::Vector() :x(0), y(0), z(0) {

	}

	Vector::Vector(double x, double y, double z) :x(x), y(y), z(z) {

	}

	double Vector::magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	double Vector::squareMagnitude() {
		return x * x + y * y + z * z;
	}

	void Vector::rotate(double angle) {
		double radian = radian(angle);
		double tempX = x * cos(radian) - y * sin(radian);
		double tempY = y * cos(radian) + x * sin(radian);
		x = tempX;
		y = tempY;
	}

	void Vector::rotate(double cos, double sin) {
		double tempX = x * cos - y * sin;
		double tempY = y * cos + x * sin;
		x = tempX;
		y = tempY;
	}

	void Vector::normalize() {
		double m = magnitude();
		x /= m;
		y /= m;
		z /= m;
	}

	Vector Vector::rotated(double angle) {
		double radian = radian(angle);
		return Vector(x * cos(radian) - y * sin(radian), y * cos(radian) + x * sin(radian));
	}

	Vector Vector::rotated(double cos, double sin) {
		return Vector(x * cos - y * sin, y * cos + x * sin);
	}

	Vector Vector::normalized() {
		double m = magnitude();
		return Vector(x / m, y / m, z / m);
	}

	Vector Vector::perpendicular(bool isRight) {
		if (isRight)
			return Vector(y, -x);
		else
			return Vector(-y, x);
	}

	void Vector::operator+=(const Vector& other) {
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void Vector::operator-=(const Vector& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	void Vector::operator*=(double value) {
		x *= value;
		y *= value;
		z *= value;
	}

	void Vector::operator/=(double value) {
		x /= value;
		y /= value;
		z /= value;
	}

	Vector Vector::operator+(const Vector& other) {
		return Vector(x + other.x, y + other.y, z + other.z);
	}

	Vector Vector::operator-(const Vector& other) {
		return Vector(x - other.x, y - other.y, z - other.z);
	}

	Vector Vector::operator^(const Vector& other) {
		return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	Vector Vector::operator*(double value) {
		return Vector(x * value, y * value, z * value);
	}

	Vector Vector::operator/(double value) {
		return Vector(x / value, y / value, z / value);
	}

	Vector Vector::operator-() {
		return Vector(-x, -y, -z);
	}

	double Vector::operator*(const Vector& other) {
		return x * other.x + y * other.y + z * other.z;
	}

}