/*
-gets current time
*/
#pragma once

#include <chrono>

namespace engine {

	class Clock {
	public:
		static long long getCurrentTime();
	};

}


