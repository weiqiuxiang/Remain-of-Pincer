#include "hitCheck.h"

bool CHitCheck::HitCheckMoveAndStill_RectX(const D3DXVECTOR3& movePos, const D3DXVECTOR3& movePosOld, const D3DXVECTOR3& moveSize, const D3DXVECTOR3&StillPos, const D3DXVECTOR3&StillSize)
{
	//矩形の上下左右辺の位置の計算
	float StillLeft, StillRight, StillTop, StillBottom;
	StillLeft = StillPos.x - StillSize.x*0.5;
	StillRight = StillPos.x + StillSize.x*0.5;
	StillTop = StillPos.y - StillSize.y*0.5;
	StillBottom = StillPos.y + StillSize.y*0.5;

	//プレーヤーの上下左右辺の位置の計算
	float MoveLeft, MoveRight, MoveTop, MoveBottom;
	if (movePos.x < movePosOld.x)    //左に向いて進む
	{
		MoveLeft = movePos.x - moveSize.x*0.5;
		MoveRight = movePosOld.x + moveSize.x*0.5;
	}
	else
	{
		MoveLeft = movePosOld.x - moveSize.x*0.5;
		MoveRight = movePos.x + moveSize.x*0.5;
	}
	MoveTop = movePos.y - moveSize.y*0.5;
	MoveBottom = movePos.y + moveSize.y*0.5;

	//当りフラグ
	bool HitX = (StillLeft <= MoveRight) && (StillRight >= MoveLeft);  //X方向判定
	bool HitY = (StillTop <= MoveBottom) && (StillBottom >= MoveTop);  //Y方向判定

	if (HitX&&HitY) return true;
	return false;
}

bool CHitCheck::HitCheckMoveAndStill_RectY(const D3DXVECTOR3& movePos, const D3DXVECTOR3& movePosOld, const D3DXVECTOR3& moveSize, const D3DXVECTOR3&StillPos, const D3DXVECTOR3&StillSize)
{
	//矩形の上下左右辺の位置の計算
	float StillLeft, StillRight, StillTop, StillBottom;
	StillLeft = StillPos.x - StillSize.x*0.5;
	StillRight = StillPos.x + StillSize.x*0.5;
	StillTop = StillPos.y - StillSize.y*0.5;
	StillBottom = StillPos.y + StillSize.y*0.5;

	//プレーヤーの上下左右辺の位置の計算
	float MoveLeft, MoveRight, MoveTop, MoveBottom;
	if (movePos.y > movePosOld.y)    //上に向いて進む
	{
		MoveTop = movePosOld.y - moveSize.y*0.5;
		MoveBottom = movePos.y + moveSize.y*0.5;
	}
	else            //落下
	{
		MoveTop = movePosOld.y - moveSize.y*0.5;
		MoveBottom = movePos.y + moveSize.y*0.5;
	}
	MoveLeft = movePos.x - moveSize.x*0.5;
	MoveRight = movePos.x + moveSize.x*0.5;

	//当りフラグ
	bool HitX = (StillLeft <= MoveRight) && (StillRight >= MoveLeft);  //X方向判定
	bool HitY = (StillTop <= MoveBottom) && (StillBottom >= MoveTop);  //Y方向判定

	if (HitX&&HitY) return true;
	return false;
}

bool CHitCheck::HitRect(const D3DXVECTOR3& APos, const D3DXVECTOR3& ASize, const D3DXVECTOR3& BPos, const D3DXVECTOR3& BSize)
{
	float ALeft = APos.x - ASize.x * 0.5;
	float ARight = APos.x + ASize.x * 0.5;
	float ATop = APos.y - ASize.y * 0.5;
	float ABottom = APos.y + ASize.y * 0.5;

	float BLeft = BPos.x - BSize.x * 0.5;
	float BRight = BPos.x + BSize.x * 0.5;
	float BTop = BPos.y - BSize.y * 0.5;
	float BBottom = BPos.y + BSize.y * 0.5;

	bool HitX = (ALeft < BRight) && (ARight > BLeft);
	bool HitY = (ATop < BBottom) && (ABottom > BTop);

	if (HitX && HitY) return true;
	return false;
}

bool CHitCheck::HitPointRect(const D3DXVECTOR3& point, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Size)
{
	float Left = Pos.x - Size.x * 0.5;
	float Right = Pos.x + Size.x * 0.5;
	float Top = Pos.y - Size.y * 0.5;
	float Bottom = Pos.y + Size.y * 0.5;

	bool HitX = (point.x <= Right) && (point.x >= Left);
	bool HitY = (point.y <= Bottom) && (point.y > Top);

	if (HitX && HitY) return true;
	return false;
}