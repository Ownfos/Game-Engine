#pragma once

#pragma comment(lib,"GL/glut32.lib")
#include "GL/glut.h"

namespace engine {

	class Color {
	public:
		double r;
		double g;
		double b;
		double a;

		Color(double r, double g, double b, double a = 1);
		void set();
	};

}

