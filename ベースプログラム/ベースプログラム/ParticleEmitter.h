#pragma once

#include <d3dx9.h>

class CParticleEmitter
{
private:
	D3DXVECTOR3	StartPosition;	// �J�n���̈ʒu
	D3DXCOLOR	StartColor;		// �J�n���̐F
	double		StartRotation;	// �J�n���̊p�x
	double		StartSize;		// �J�n���̑傫��
	double		StartLifeTime;	// ��������
public:
	CParticleEmitter();
	~CParticleEmitter();
};