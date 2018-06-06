#pragma once
#include <ctime>

struct Time {
	static float GetTime() {
		return std::clock() / (float)CLOCKS_PER_SEC;
	}
	static float GetDelta(float &lastframe_time, float &currframe_time) {
		lastframe_time = currframe_time;
		currframe_time = Time::GetTime();
		return currframe_time - lastframe_time;
	}
	static void Sleep(float time_in_sec) {
  		float start_clock = GetTime();
		while (true) {
			if ((GetTime() - start_clock) >= time_in_sec)
				break;
		}
	}
};