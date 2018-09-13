#pragma once

#include "Vector.h"

namespace engine {

	class Distance {
	public:
		static double PointToLineSegment(Vector p, Vector v1, Vector v2);
	};

}


