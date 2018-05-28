#pragma once
#ifndef CWORM_HOLE_WARP_PLAYER
#define CWORM_HOLE_WARP_PLAYER

#include "main.h"
#include "CWormHole.h"
#include "CPlayer.h"

class CWormHoleWarpPlayer
{
public:
	static void Update(void);
private:
	static void PlayerHitWormHole(void);            //柱とワープホールの当り判定
	static CWormHole* OnePlayerHitAllWormHole(CPlayer *pPlayer);
	static void AdjustTwoPlayerPos(CPlayer *pPlayer);
	static void WormHoleReturn(void);
	static void WormHoleNotHitAnyPlayer(CWormHole* pWormHole);
};

#endif