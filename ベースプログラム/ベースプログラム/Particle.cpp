#include "Particle.h"

CParticle::CParticle()
{
	Position = D3DXVECTOR3();
	Color = D3DXCOLOR();
	Rotation = 0.0f;
	Size = 0.0f;
	LifeTime = 0.0f;
}

CParticle::~CParticle()
{

}