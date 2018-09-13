#pragma once

#pragma comment(lib,"GL/glut32.lib")
#include "GL/glut.h"

#include "Vector.h"

namespace engine {

	enum ShapeType {
		PolygonType,
		CircleType
	};

	class Shape {
	public:
		virtual void draw(bool isFilled) = 0;
		virtual bool isInside(Vector position) = 0;
		ShapeType getType();
	protected:
		ShapeType _type;
	};

}