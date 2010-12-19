#include "StdAfx.h"
#include "IAnimation.h"

namespace IMesh { namespace UI { namespace Models {


Animation::Animation() : m_animationThread(NULL), m_isSetuped(false)
{

}

	
Animation::~Animation()
{
	if (m_animationThread != NULL) 
	{
		m_animationThread->ExitInstance();
	}
}

void Animation::OnSetup()
{
	class AnimationThread : public CWinThread
	{
	public:
		Animation& m_animation;
	protected:
		void SpinWait(double millionSeconds)
		{
			Sleep(millionSeconds);
		}
	public:
		AnimationThread(Animation& animation) : m_animation(animation) {}
		int Run()
		{
			ASSERT(m_animation.m_fps > 0);
			ASSERT(m_animation.m_frameNum > 0);

			DWORD millionSeconds = 1000 / m_animation.m_fps;
			do
			{
				for (int i = 0; i < m_animation.m_frameNum; ++i) 
				{
					m_animation.OnAnimationFrame(i);
					SpinWait(millionSeconds);
				}
			} while(m_animation.m_isRepeat);

			return 0;
		}
	};

	m_animationThread = new AnimationThread(*this);
	BOOL bRet = (m_animationThread->CreateThread(CREATE_SUSPENDED));
	if (bRet) {
		m_animationThread->InitInstance();
		m_isSetuped = true;
	} else {
		throw std::exception("Cannot Setup Animation");
	}
}

void Animation::StartAnimation()
{
	if (m_animationThread != NULL) 
	{
		if (!m_isSetuped) { OnSetup(); }
		m_animationThread->Run();
	}
}

void Animation::StopAnimation()
{
	if (m_animationThread != NULL) 
	{
		m_animationThread->ExitInstance();
	}
}

void Animation::OnAnimationFrame( int i )
{
	throw std::exception("Not Implemented Exception!");
}

} } }
