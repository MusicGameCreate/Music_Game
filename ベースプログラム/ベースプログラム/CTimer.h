////=================================================================
//// 
//// タイマークラス[Timer.h]
//// 
////=================================================================
//
//#pragma once
//
//#include <time.h>
//
//class CTimer
//{
//private:
//	bool	bActiv;
//	bool	bEnd;
//	bool	bLoop;
//	double		SetTime;
//	double		Start;
//	double		Now;
//	double		Time;
//	//clock_t		nSetTime;
//	//clock_t		Start;
//	//clock_t		Now;
//	//clock_t		Time;
//public:
//	CTimer(void);
//	~CTimer(void);
//	void TimerInit(double time);
//	void TimerActiv(bool loop);
//	bool TimerEnd(void);
//	void TimerPause(void);
//	void TimerRestart(void);
//
//	// セッタ
//	void SetTimerState(bool start);
//	//void TimerStart(void);
//	// タイマー起動からの経過時間を返す
//	double GetTime(void);
//};