#include "Collision.h"

namespace engine {

	bool Collision::isColliding(Object* object1, Object* object2) {
		ShapeType shape1 = object1->_shape->getType();
		ShapeType shape2 = object2->_shape->getType();
		if (shape1 == CircleType && shape2 == CircleType) return circleToCircle(object1, object2);
		if (shape1 == CircleType && shape2 == PolygonType) return circleToPolygon(object1, object2);
		if (shape1 == PolygonType && shape2 == CircleType) return circleToPolygon(object2, object1);
		if (shape1 == PolygonType && shape2 == PolygonType) return polygonToPolygon(object1, object2);
	}

	bool Collision::circleToCircle(Object* object1, Object* object2) {
		Circle* A = (Circle*)object1->_shape;
		Circle* B = (Circle*)object2->_shape;

		double distance = (object1->_position-object2->_position).squareMagnitude();
		double limit = A->radius + B->radius;
		return distance <= limit * limit;
	}

	bool Collision::circleToPolygon(Object* object1, Object* object2) {
		Circle* A = (Circle*)object1->_shape;
		Polygon* B = (Polygon*)object2->_shape;

		if (object2->isInside(object1->_position)) {
			return true;
		}
		else {
			int size = B->vertices.size();
			for (int i = 0; i < size; i++) {
				double distance = Distance::PointToLineSegment(
					object1->_position,
					object2->_position + B->vertices[i].rotated(object2->_angle),
					object2->_position + (B->vertices[i] + B->edges[i]).rotated(object2->_angle)
				);
				if (distance <= A->radius)
					return true;
			}
		}
		return false;
	}

	bool Collision::polygonToPolygon(Object* object1, Object* object2) {
		Polygon* A = (Polygon*)object1->_shape;
		Polygon* B = (Polygon*)object2->_shape;
		
		int size;

		size = A->normals.size();
		for (int i = 0; i < size; i++) {
			Vector axis = A->normals[i].rotated(object1->_angle);
			Projection pa = Projection(axis, A, object1->_position, object1->_angle);
			Projection pb = Projection(axis, B, object2->_position, object2->_angle);
			if (pa.min > pb.max || pa.max < pb.min)
				return false;
		}
		size = B->normals.size();
		for (int i = 0; i < size; i++) {
			Vector axis = B->normals[i].rotated(object2->_angle);
			Projection pa = Projection(axis, A, object1->_position, object1->_angle);
			Projection pb = Projection(axis, B, object2->_position, object2->_angle);
			if (pa.min > pb.max || pa.max < pb.min)
				return false;
		}
		return true;
	}

}