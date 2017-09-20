#pragma once
#include <Windows.h>

class CMouseTrackEvent
{
private:
	bool	m_bMouseTracking;
public:
	CMouseTrackEvent();
	~CMouseTrackEvent();

	void OnMouseMove(HWND hwnd);
	void Reset();
};