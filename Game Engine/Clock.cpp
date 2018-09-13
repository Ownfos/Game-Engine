#include "Clock.h"

namespace engine {

	long long Clock::getCurrentTime() {
		//std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		//return ms.count();


		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

		long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now).count();

		return microseconds;
	}

}