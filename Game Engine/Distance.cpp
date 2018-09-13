/*
-calculates minimal distance between line segment and point

-used on circle to polygon collision check
*/
#include "Distance.h"

namespace engine {

	double Distance::PointToLineSegment(Vector p, Vector v1, Vector v2) {
		Vector projection;
		Vector relativePosition;

		double lengthSquare = (v1 - v2).squareMagnitude();
		double t = fmax(0, fmin(1, (p - v1)*(v2 - v1) / lengthSquare));
		projection = v1 + (v2 - v1) * t;
		relativePosition = p - projection;
		return relativePosition.magnitude();
	}

}