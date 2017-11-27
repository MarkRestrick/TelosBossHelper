#include "Timer.h"
#include <iostream>
#include <string>

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Timer();

	}

	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = NULL;
}

Timer::Timer()
{
	Reset();
	m_TimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	m_StartTicks = SDL_GetTicks();
	m_ElapsedTicks = 0;
	m_DeltaTime = 0.0f;
}

float Timer::DeltaTime()
{
	return m_DeltaTime;
}

void Timer::TimeScale(float t)
{
	m_TimeScale = t;
}

float Timer::TimeScale()
{
	return m_TimeScale;
}

void Timer::Update()
{
	m_ElapsedTicks = SDL_GetTicks() - m_StartTicks;
	m_DeltaTime = m_ElapsedTicks * 0.001f;
	std::cout << m_DeltaTime <<  "\n";
}