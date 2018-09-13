/*
-checks collision
*/
#pragma once

#include "Object.h"
#include "Circle.h"
#include "Polygon.h"
#include "Distance.h"
#include "Projection.h"
#include "Radian.h"

namespace engine {

	class Collision {
	public:
		static bool isColliding(Object* object1, Object* object2);
		static bool circleToCircle(Object* object1, Object* object2);
		static bool circleToPolygon(Object* object1, Object* object2);
		static bool polygonToPolygon(Object* object1, Object* object2);
	};

}


