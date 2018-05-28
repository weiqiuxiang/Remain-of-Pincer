#pragma once
#ifndef _CEARTHQUAKE_H_
#define _CEARTHQUAKE_H_

#include "main.h"

class CEarthquake
{
public:
	static void Update(void);
	static void SetAngle(double Angle);
	static void SetAmplitude(double Amplitude);          //振幅設定
	static void SetDecrement(double Decrement);          //減衰度設定
	static double GetChangeY(void) { return m_ChangeY; }
private:
	static double m_Angle;
	static double m_ChangeY;
	static double m_Amplitude;      //振幅
	static double m_Decrement;      //1フレームの減衰度
};

#endif