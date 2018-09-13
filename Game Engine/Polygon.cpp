#include "Polygon.h"

namespace engine {

	Polygon::Polygon(std::initializer_list<Vector> list) {
		_type = PolygonType;
		initialize(list);
	}

	Polygon::Polygon(double width, double height) {
		double halfWidth = width / 2;
		double halfHeight = height / 2;
		std::initializer_list<Vector> list = {
			Vector(halfWidth, halfHeight),
			Vector(-halfWidth, halfHeight),
			Vector(-halfWidth, -halfHeight),
			Vector(halfWidth, -halfHeight),
		};
		initialize(list);
	}

	void Polygon::initialize(std::initializer_list<Vector> list) {
		vertices = list;
		for (int i = 0; i < vertices.size(); i++) {
			int j = (i + 1) % vertices.size();

			Vector edge = vertices[j] - vertices[i];
			edges.push_back(edge);

			Vector normal = edge.perpendicular(true);
			normal.normalize();
			normals.push_back(normal);
		}
	}

	void Polygon::draw(bool isFilled) {
		if (isFilled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);

		for (int i = 0; i < vertices.size(); i++) {
			glVertex2d(vertices[i].x, vertices[i].y);
		}
		glEnd();
	}

	bool Polygon::isInside(Vector position) {
		for (int i = 0; i < edges.size(); i++) {
			if ((edges[i] ^ (position - vertices[i])).z < 0)
				return false;
		}
		return true;
	}

}