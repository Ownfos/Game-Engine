#pragma once

#include "Radian.h"

namespace engine {

	class Vector {
	public:
		double x;
		double y;
		double z;

		Vector();
		Vector(double x, double y, double z = 0);

		double magnitude();
		double squareMagnitude();
		void rotate(double angle);
		void rotate(double cos, double sin);
		void normalize();
		Vector rotated(double angle);
		Vector rotated(double cos, double sin);
		Vector normalized();
		Vector perpendicular(bool isRight);

		void operator+=(const Vector& other);
		void operator-=(const Vector& other);
		void operator*=(double value);
		void operator/=(double value);
		Vector operator+(const Vector& other);
		Vector operator-(const Vector& other);
		Vector operator^(const Vector& other);
		Vector operator*(double value);
		Vector operator/(double value);
		Vector operator-();
		double operator*(const Vector& other);
	};

}