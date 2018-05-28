#pragma once
#ifndef _CSPRING_PUSH_BALL_H_
#define _CSPRING_PUSH_BALL_H_

#include "main.h"
#include "CBall.h"
#include "CSpring.h"

class CSpringPushBall
{
public:
	static void Update(void);
private:
	static void SpringPushBall(void);
	static CSpring* BallHitSpring(CBall *pBall);
	static void AdjustSpring(CBall *pBall, CSpring* pSpring);
	static float GetPowerFromSpring(CSpring* pSpring);
	static void PushBall(CBall *pBall, float PowerFromSpring);
};

#endif