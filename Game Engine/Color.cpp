/*
-stores color information

-can be used to set color with set()
*/
#include "Color.h"

namespace engine {

	Color::Color(double r, double g, double b, double a) :r(r), g(g), b(b), a(a) {

	}

	void Color::set() {
		glColor4d(r, g, b, a);
	}

}
