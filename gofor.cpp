#include "used.hpp"
#include <chrono>

// return system timestamp
int timepoint() {
	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	
	return static_cast<int>(milliseconds.count());
}

int timepast(int begintime)
{
	return timepoint() - begintime;
}

void thgofora(float sta, float sto, int duration, std::atomic<float>& val) {
	int start = timepoint();
	float a = 2.0f * (sto - sta) / float((duration * duration));
	
	while (true) {
		int elapsed = timepast(start);
		float t = static_cast<float>(elapsed);
		
		if (t >= duration) {
			val.store(sto);
			break;
		}
		
		float current = sta + a * t * t / 2.0f;
		val.store(current);
		api_sleep(1);  // not sleep() , to avoid triggering ege's buffer swap
	}
}

