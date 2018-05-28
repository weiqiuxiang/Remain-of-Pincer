#pragma once
#ifndef _CSPRING_PUSH_PLAYER_H_
#define _CSPRING_PUSH_PLAYER_H_

#include "main.h"
#include "CPlayer.h"
#include "CSpring.h"

class CSpringPushPlayer
{
public:
	static void Update(void);
private:
	static void SpringReturn(void);
	static void SpringPushPlayer(void);
	static CSpring* PlayerHitSpring(CPlayer *pPlayer);
	static void AdjustSpring(CPlayer *pPlayer, CSpring* pSpring);
	static float GetPowerFromSpring(CSpring* pSpring);
	static void PushPlayer(CPlayer *pPlayer, float PowerFromSpring);
};

#endif