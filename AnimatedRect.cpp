#include "AnimatedRect.h"

AnimatedRect::AnimatedRect(const Window &window, std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir, int ClippedX, int ClippedY)
	: DrawRect(window, w, h, x, y, filename)
{

	m_Timer = Timer::Instance();


	//SDL_QueryTexture(m_texture, NULL, NULL, &m_w, &m_h);

	m_ClippedRect = { 0, 0, 308, 55 };

	m_StartX = x;
	m_StartY = y;

	m_FrameCount = frameCount;
	m_AnimationSpeed = animationSpeed;
	m_TimePerFrame = m_AnimationSpeed / m_FrameCount;
	m_AnimationTimer = 0.0f;

	m_AnimationDirection = animationDir;

	m_AnimationDone = false;

	m_WrapMode = once;
}

AnimatedRect::~AnimatedRect()
{
}

void AnimatedRect::TimerReset()
{
	m_Timer->Reset();
	m_AnimationDone = false;
}

float AnimatedRect::GetTimerDelta()
{
	return m_Timer->DeltaTime();
}

void AnimatedRect::WrapMode(WRAP_MODE mode)
{
	m_WrapMode = mode;
}

void AnimatedRect::Update()
{
	

	if (!m_AnimationDone)
	{
		m_Timer->Update();

		m_AnimationTimer = m_Timer->DeltaTime();

		if (m_AnimationTimer >= m_AnimationSpeed)
		{
			if (m_WrapMode == loop)
			{
				m_AnimationTimer -= m_AnimationSpeed;
			}
			else
			{
				m_AnimationDone = true;
				m_AnimationTimer = m_AnimationSpeed - (m_TimePerFrame);
			}
		}

		m_ClippedRect.y = m_StartY + (int)(m_AnimationTimer / m_TimePerFrame) * 55;
	}
	/*

	if (m_Timer->DeltaTime() > 50.0f)
	{
		m_Timer->Reset();
	}
	*/
}
