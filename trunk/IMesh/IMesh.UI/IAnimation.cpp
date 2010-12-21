#include "StdAfx.h"
#include "IAnimation.h"

namespace IMesh { namespace UI { namespace Models {


Animation::Animation() : m_animationThread(NULL), m_animationCompleted()
						, m_isSetuped(false)
{
	//m_animationCompleted.ResetEvent();
}

Animation::~Animation()
{
	if (m_animationThread != NULL) 
	{
		m_animationThread->Delete();
		m_animationThread = NULL;
	}
}

void Animation::OnSetup()
{
	class AnimationThread : public CWinThread
	{
	public:
		Animation& m_animation;
	protected:
		void Wait(DWORD millionSeconds)
		{
			LARGE_INTEGER prev, now, freq;
			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&prev);

			double ms_per_tick = 1000.0 / freq.QuadPart;
			while (true) 
			{
				QueryPerformanceCounter(&now);
				double elapsed = (now.QuadPart - prev.QuadPart) * ms_per_tick;
				if (elapsed > millionSeconds) {
					break;
				}

				BOOL bRet;
				MSG msg;
				if ( (bRet = PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) != 0)
				{ 
					//GetMessage(&msg, NULL, 0, PM_NOREMOVE);
					//TranslateMessage(&msg);
					//DispatchMessage(&msg);
					if ( ! AfxGetApp()->PumpMessage() ) {
						AfxGetApp()->ExitInstance();
					}
				}
				Sleep(0);
			}
			
		}
	public:
		AnimationThread(Animation& animation) : m_animation(animation) {
			m_bAutoDelete = TRUE;
		}
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
					Wait(millionSeconds);
				}
			} while(m_animation.m_isRepeat);
			
			m_animation.m_animationCompleted.SetEvent();
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
		m_animationCompleted.SetEvent();
	}
}


void Animation::JoinAnimation()
{
	WaitForSingleObject(m_animationCompleted.m_hObject, INFINITE);
}

void Animation::OnAnimationFrame( int i )
{
	throw std::exception("Not Implemented Exception!");
}


} } }
