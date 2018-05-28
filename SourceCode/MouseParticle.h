#pragma once
#ifndef MOUSE_PARTICLE_H_
#define MOUSE_PARTICLE_H_

#include "main.h"
#include "Particle.h"

class CMouseParticle
{
public:
	static void Init(void);
	static void Update(void);
	static void Uninit(void);
private:
	static CParticle *m_Particle;
	static D3DXVECTOR3 m_MousePosOld;
};

#endif