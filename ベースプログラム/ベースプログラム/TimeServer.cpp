#include "TimeServer.h"

double CTimeServer::DifferenceTime;

CTimeServer::CTimeServer()
{
	Initialize();
}

CTimeServer::~CTimeServer()
{

}

void CTimeServer::Initialize()
{
	DifferenceTime = 0.0f;
	StartTime = NowTime = (double)clock() / CLOCKS_PER_SEC;
}

void CTimeServer::Finalize()
{

}

void CTimeServer::Update()
{
	double time = NowTime;
	NowTime = (double)clock() / CLOCKS_PER_SEC;
	DifferenceTime = NowTime - time;
}