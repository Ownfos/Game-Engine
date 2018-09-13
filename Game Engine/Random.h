/*
-generates random number

-randomize() will set random seed

-random() and irandom() starts from 0

-all return values include min and max.
*/
#pragma once

#include <cstdlib>
#include <ctime>

namespace engine {

	class Random {
	public:
		static void randomize();
		static double random(double max);
		static double randomRange(double min, double max);
		static int irandom(int max);
		static int irandomRange(int min, int max);
	};

}