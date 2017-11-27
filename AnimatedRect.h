#pragma once

#include "window.h"
#include "drawrect.h"
#include "Timer.h"

class AnimatedRect : public DrawRect
{
public:
	
	enum WRAP_MODE { once = 0, loop = 1};
	enum ANIM_DIR { horizontal = 0, vertical = 1};

private:

	Timer* m_Timer;
	int m_StartX;
	int m_StartY;

	float m_AnimationTimer;
	float m_AnimationSpeed;
	float m_TimePerFrame;

	int m_FrameCount;

	WRAP_MODE m_WrapMode;
	ANIM_DIR m_AnimationDirection;

	bool m_AnimationDone;

public:
	AnimatedRect(const Window &window, std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir, int clippedX, int clippedY);
	~AnimatedRect();

	void WrapMode(WRAP_MODE mode);
	void TimerReset();
	float GetTimerDelta();
	void Update();
};
