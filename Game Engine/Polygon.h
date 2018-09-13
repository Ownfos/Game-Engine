/*
-the polygon shape class

-Polygon(std::initializer_list<Vector> list) creates a custom polygon
-Polygon(double width, double height) creates a square
*/
#pragma once

#include <vector>

#include "Shape.h"
#include "Vector.h"

namespace engine {

	class Polygon :public Shape {
	public:
		std::vector<Vector> vertices;
		std::vector<Vector> edges;
		std::vector<Vector> normals;

		Polygon(std::initializer_list<Vector> list);
		Polygon(double width, double height);
		void initialize(std::initializer_list<Vector> list);
		virtual void draw(bool isFilled);
		virtual bool isInside(Vector position);
	};

}

