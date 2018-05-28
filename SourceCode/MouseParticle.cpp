#include "MouseParticle.h"
#include "Effect.h"

CParticle *CMouseParticle::m_Particle = NULL;
D3DXVECTOR3 CMouseParticle::m_MousePosOld;

#define PARTICLE_CREATE_DISTANCE (5.0f)

void CMouseParticle::Init(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	m_Particle = NULL;
	m_Particle = CParticle::Create(507.000, 290.000, 0.000, 58.000, 8.000, 8.000, 8.000, 0.000, 0.000, 0.000, 0.050, 0.050, 0.050, 0.000, 0.000, 0.000, 3, 21.000, 0.000, 0.000, 1.00, 1.00, 1.00, 1.00, 0.000, 0.000, 0.000, 0.000, 0.000, 5.000, 0.000, 6.950, 6.950, 6.950, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.121, 0.121, 0.121, 0.000, 0.000, 205.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, PARTICLE_BASE_TEX);
	m_Particle->SetStopFlag(true);
	m_MousePosOld = MousePos;
}

void CMouseParticle::Update(void)
{
	if (NULL == m_Particle) return;

	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	m_Particle->SetPosXYZ(MousePos);

	if(D3DXVec3Length(&(MousePos - m_MousePosOld)) > PARTICLE_CREATE_DISTANCE)
	{
		m_Particle->SetStopFlag(false);
	}

	else
	{
		m_Particle->SetStopFlag(true);
	}
	m_MousePosOld = MousePos;
}

void CMouseParticle::Uninit(void)
{
	m_Particle = NULL;
}