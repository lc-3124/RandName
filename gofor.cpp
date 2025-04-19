#include "used.hpp"
#include <chrono>

// 返回自系统启动/程序运行以来的毫秒时间戳（单调递增，不受系统时间调整影响）
int timepoint() {
	// 获取当前时间点（使用 steady_clock 保证时间单调递增）
	auto now = std::chrono::steady_clock::now();
	
	// 转换为毫秒时间间隔
	auto duration = now.time_since_epoch();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	
	// 返回整数型毫秒值
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
		//usleep(1);  // 更新频率控制
	}
}

