#include "CEarthquake.h"

double CEarthquake::m_Amplitude = 0;
double CEarthquake::m_Decrement = 0;
double CEarthquake::m_Angle = D3DX_PI*0.5;
double CEarthquake::m_ChangeY = 0;

#define CHANGE_ANGLE (1.0f)

void CEarthquake::Update(void)
{
	if (m_Amplitude > 0)
	{
		m_ChangeY = m_Amplitude*sin(m_Angle);
		m_Amplitude = max(0, m_Amplitude - m_Decrement);
		m_Angle += CHANGE_ANGLE;
	}
}

void CEarthquake::SetAngle(double Angle)
{
	m_Angle = Angle;
}

void CEarthquake::SetAmplitude(double Amplitude)
{
	m_Amplitude = max(0,Amplitude);
}

void CEarthquake::SetDecrement(double Decrement)
{
	m_Decrement = max(0, Decrement);
}