#pragma once
#ifndef CPLAYER_HIT_FLOOR_BREAK
#define CPLAYER_HIT_FLOOR_BREAK

#include "main.h"
#include "CPlayer.h"
#include "CFloor.h"

class CPlayerHitFloorBreak
{
public:
	static void Update(void);
private:
	static void PlayerHitAllFloor(CScene* pPlayer);
	static void DeleteFloorBreak(CFloor* pFloor);
};

#endif