#pragma once

#include <d3dx9.h>

class CParticleEmitter
{
private:
	D3DXVECTOR3	StartPosition;	// 開始時の位置
	D3DXCOLOR	StartColor;		// 開始時の色
	double		StartRotation;	// 開始時の角度
	double		StartSize;		// 開始時の大きさ
	double		StartLifeTime;	// 生存時間
public:
	CParticleEmitter();
	~CParticleEmitter();
};