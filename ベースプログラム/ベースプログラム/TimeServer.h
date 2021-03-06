#pragma once

#include <time.h>

class CTimeServer
{
private:
	static double DifferenceTime;	// 毎フレーム経過した時間を格納
	double		StartTime;			// 
	double		NowTime;
public:
	CTimeServer();
	~CTimeServer();

	void Initialize();
	void Finalize();
	void Update();

	static double GetDifference() { return DifferenceTime; }
};