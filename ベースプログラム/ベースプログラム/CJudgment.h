//***********************************************************************************************************
//
// 当たり判定
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Define.h"
#include "CDirectX.h"

bool	BOX2D(D3DXVECTOR2 ALeftUp, D3DXVECTOR2 ARightDown, D3DXVECTOR2 BLeftUp, D3DXVECTOR2 BRightDown);
bool	BOX3D();
bool	MouseTex2D(D3DXVECTOR3 MousePos, D3DXVECTOR3 TexPos, D3DXVECTOR2 TexSize, bool Portrait);
bool	MouseTex2DCircle(D3DXVECTOR3 MousePos, D3DXVECTOR3 TexPos, D3DXVECTOR2 TexSize);
bool	WorldModel2D(D3DXVECTOR3 MousePos, D3DXVECTOR3 ModelPos, D3DXVECTOR3 ModelSize);
bool	CIRCLE(D3DXVECTOR2 APos, float fARudius, D3DXVECTOR2 BPos, float fBRudius);
bool	ANGLEBOXandCIRCLE(D3DXVECTOR2 BoxCenter, D3DXVECTOR2 BoxSize, float fBoxAngle, D3DXVECTOR2 CircleCenter, float fCircleRadius);


//***********************************************************************************************************
// EOF
//***********************************************************************************************************