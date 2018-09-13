/*
-Circle shape
*/
#pragma once

#include "Shape.h"

#define SEGMENT 20

namespace engine {

	class Circle :public Shape {
	public:
		double radius;

		Circle(double radius);
		virtual void draw(bool isFilled);
		virtual bool isInside(Vector position);
	};

}
