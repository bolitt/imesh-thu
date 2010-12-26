#pragma once
#include "StdAfx.h"

namespace IMesh { namespace UI {

class HDTimer
{
protected:
	double MS_PER_TICK;

public:	
	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_prev;
	LARGE_INTEGER m_now;
	
public:
	HDTimer(void);
	~HDTimer(void);

	inline void Start() { QueryPerformanceCounter(&m_prev); }
	inline void Pause() { QueryPerformanceCounter(&m_now);}
	inline double GetTotalMilliSeconds() { return (m_now.QuadPart - m_prev.QuadPart) * MS_PER_TICK; }
};

} }
