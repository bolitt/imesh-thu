#include "StdAfx.h"
#include "HDTimer.h"

namespace IMesh { namespace UI { 

HDTimer::HDTimer(void)
{
	QueryPerformanceFrequency(&m_freq);
	MS_PER_TICK = 1000.0 / m_freq.QuadPart;
}


HDTimer::~HDTimer(void)
{
}



} } 
