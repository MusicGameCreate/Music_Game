#pragma once

#include <d3dx9.h>

class CParticle
{
private:
	D3DXVECTOR3	Position;	// 
	D3DXCOLOR	Color;		// 
	double		Rotation;	// 
	double		Size;		// 
	double		LifeTime;	// 
public:
	CParticle();
	~CParticle();
};