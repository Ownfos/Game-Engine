#include "Projection.h"

namespace engine {

	Projection::Projection(Vector axis, Polygon* p, Vector position, double angle) {
		min = MAX;
		max = -MAX;
		
		double radian = radian(angle);
		double cos = std::cos(radian);
		double sin = std::sin(radian);

		int size = p->vertices.size();
		for (int i = 0; i < size; i++) {
			//double projection = axis * (p->vertices[i].rotated(angle));
			double projection = axis * (p->vertices[i].rotated(cos, sin));
			if (projection < min)
				min = projection;
			if (projection > max)
				max = projection;
		}
		min += axis * position;
		max += axis * position;
	}

}