#pragma once
#ifndef _HITCHECK_H_
#define _HITCHECK_H_

#include "main.h"

class CHitCheck
{
public:
	static bool HitCheckMoveAndStill_RectX(const D3DXVECTOR3& movePos, const D3DXVECTOR3& movePosOld, const D3DXVECTOR3& moveSize , const D3DXVECTOR3&Stillpos, const D3DXVECTOR3&StillSize);          //à⁄ìÆï®ëÃÇ∆ê√é~ï®ëÃÇÃìñÇËîªíË
	static bool HitCheckMoveAndStill_RectY(const D3DXVECTOR3& movePos, const D3DXVECTOR3& movePosOld, const D3DXVECTOR3& moveSize, const D3DXVECTOR3&Stillpos, const D3DXVECTOR3&StillSize);          //à⁄ìÆï®ëÃÇ∆ê√é~ï®ëÃÇÃìñÇËîªíË
	static bool HitRect(const D3DXVECTOR3& APos, const D3DXVECTOR3& ASize, const D3DXVECTOR3& BPos, const D3DXVECTOR3& BSize);
	static bool HitPointRect(const D3DXVECTOR3& point, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Size);
};

#endif