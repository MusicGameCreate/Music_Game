#pragma once

#include <time.h>

class CTimeServer
{
private:
	static double DifferenceTime;	// ���t���[���o�߂������Ԃ��i�[
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