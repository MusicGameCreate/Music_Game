#pragma once

#include <time.h>

class CTimeServer
{
private:
	static double DifferenceTime;	// –ˆƒtƒŒ[ƒ€Œo‰ß‚µ‚½ŠÔ‚ğŠi”[
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