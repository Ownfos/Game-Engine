#include "Random.h"

namespace engine {

	void Random::randomize() {
		srand(time(NULL));
	}

	double Random::random(double max) {
		return (double)rand() / RAND_MAX * max;
	}

	double Random::randomRange(double min, double max) {
		return (double)rand() / RAND_MAX * (max - min) + min;
	}

	int Random::irandom(int max) {
		return rand() % (max + 1);
	}

	int Random::irandomRange(int min, int max) {
		//double works well without correcting range, but integer needs it(because of that +1).
		if (min > max) {
			int temp = min;
			min = max;
			max = temp;
		}
		return rand() % (max - min + 1) + min;
	}

}
