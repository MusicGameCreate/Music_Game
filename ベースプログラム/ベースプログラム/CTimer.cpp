//// ŽžŠÔŠÇ—ƒNƒ‰ƒX
//
//#include "CTimer.h"
//
//const	clock_t	RETURN_TIME = 1;	// 1•bŠÔ‚É1(•b)
//
//CTimer::CTimer(void)
//{
//	bActiv = false;
//	bEnd = false;
//	bLoop = false;
//	SetTime = 0;
//	Start = 0;
//	Now = 0;
//	Time = 0;
//}
//
//CTimer::~CTimer(void)
//{
//
//}
//
//void CTimer::TimerInit(double time)
//{
//	bActiv = false;
//	SetTime = time;
//	Start = Now = (double)clock() * RETURN_TIME / CLOCKS_PER_SEC;
//	bEnd = false;
//}
//
//void CTimer::TimerActiv(bool loop)
//{
//	bLoop = loop;
//	TimerInit(SetTime);
//	bActiv = true;
//}
//
//bool CTimer::TimerEnd(void)
//{
//	if (!bActiv)
//		return false;
//
//	Now = (double)clock() * RETURN_TIME / CLOCKS_PER_SEC;
//	Time = Now - Start;
//	if (Time >= SetTime)
//	{
//		if (bLoop)
//		{
//			TimerActiv(bLoop);
//			return true;
//		}
//		bActiv = false;
//		return true;
//	}
//	return false;
//}
//
//void CTimer::TimerPause(void)
//{
//	bActiv = false;
//}
//
//void CTimer::TimerRestart(void)
//{
//	Start = (double)clock() - Time;
//	bActiv = true;
//}
//
//void CTimer::SetTimerState(bool start)
//{
//	if (start)
//	{
//		if (!bActiv)
//		{
//			Start = ((double)clock() * RETURN_TIME / CLOCKS_PER_SEC) - Time;
//		}
//	}
//	bActiv = start;
//}
//
//double CTimer::GetTime(void)
//{
//	Now = (double)clock() * RETURN_TIME / CLOCKS_PER_SEC;
//	Time = Now - Start;
//	return (double)Time;
//}