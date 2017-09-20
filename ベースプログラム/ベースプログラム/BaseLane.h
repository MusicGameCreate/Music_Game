#pragma once
#include "CTexture_3D_Base.h"

class CBaseLane
{
protected:
	int m_nLaneNum;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vRot;

public:
	CBaseLane();
	~CBaseLane();


};