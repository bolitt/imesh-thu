#pragma once
#include "stdafx.h"
#include <exception>

namespace IMesh { namespace UI { namespace Models {

class IAnimation
{
public:
	int m_fps;
	int m_frameNum;
	bool m_isRepeat;

public:
	IAnimation() : m_fps(0), m_frameNum(-1), m_isRepeat(false) {}
	virtual void StartAnimation() = 0;
	virtual void StopAnimation() = 0;
	virtual void OnAnimationFrame(int i) = 0;
};

// 
class Animation : public IAnimation
{
protected:
	CWinThread* m_animationThread;
	bool m_isSetuped;

public:
	Animation();
	virtual ~Animation();
	void OnSetup();
	void StartAnimation();
	void StopAnimation();
	void OnAnimationFrame(int i);
};

} } }



