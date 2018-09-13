#include "Circle.h"

namespace engine {

	Circle::Circle(double radius) :radius(radius) {
		_type = CircleType;
	}

	void Circle::draw(bool isFilled) {
		if (isFilled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);

		for (int i = 0; i < SEGMENT; i++) {
			double angle = 2 * PI * i / SEGMENT;
			glVertex2d(
				radius*cos(angle),
				radius*sin(angle)
			);
		}
		glEnd();
	}

	bool Circle::isInside(Vector position) {
		return position.magnitude() <= radius;
	}

}