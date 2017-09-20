#include "ParticleEmitter.h"

CParticleEmitter::CParticleEmitter()
{
	StartPosition = D3DXVECTOR3();
	StartColor = D3DXCOLOR();
	StartRotation = 0.0f;
	StartSize = 0.0f;
	StartLifeTime = 0.0f;
}

CParticleEmitter::~CParticleEmitter()
{

}