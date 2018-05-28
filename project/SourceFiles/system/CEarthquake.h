#pragma once
#ifndef _CEARTHQUAKE_H_
#define _CEARTHQUAKE_H_

#include "main.h"

class CEarthquake
{
public:
	static void Update(void);
	static void SetAngle(double Angle);
	static void SetAmplitude(double Amplitude);          //�U���ݒ�
	static void SetDecrement(double Decrement);          //�����x�ݒ�
	static double GetChangeY(void) { return m_ChangeY; }
private:
	static double m_Angle;
	static double m_ChangeY;
	static double m_Amplitude;      //�U��
	static double m_Decrement;      //1�t���[���̌����x
};

#endif