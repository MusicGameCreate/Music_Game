#include "MouseTrackEvent.h"

CMouseTrackEvent::CMouseTrackEvent() : m_bMouseTracking(false)
{

}

CMouseTrackEvent::~CMouseTrackEvent()
{

}

void CMouseTrackEvent::OnMouseMove(HWND hwnd)
{
	if (!m_bMouseTracking)
	{
		// �}�E�X�ǐՂ��\�ɂ���
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = hwnd;
		tme.dwFlags = /*TME_HOVER | */TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;
		TrackMouseEvent(&tme);
		m_bMouseTracking = true;
	}
}

void CMouseTrackEvent::Reset()
{
	m_bMouseTracking = false;
}