#pragma once

#include <SDL.h>

class Timer
{
private:
		static Timer * sInstance;

		unsigned int m_StartTicks;
		unsigned int m_ElapsedTicks;
		float m_DeltaTime;
		float m_TimeScale;

public:

	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:
	Timer();
	~Timer();
};