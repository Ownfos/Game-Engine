#pragma once

#include "Polygon.h"
#include "Circle.h"

#define MAX 9999999

namespace engine {

	class Projection {
	public:
		double min;
		double max;

		Projection(Vector axis, Polygon* p, Vector position, double angle);
	};

}

