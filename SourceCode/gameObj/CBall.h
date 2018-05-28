#pragma once
#ifndef _CBALL_H_
#define _CBALL_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CBall :public CScene2D
{
public:
	CBall();
	CBall(int Priority);
	~CBall();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2Dのインスタンスを生成する関数
	void HitFloor(void);
	void HitPlayer(void);
	static int GetPriority(void) { return s_nPriority; }

	//ゲッター
	bool GetDeadFlag(void) {return m_bDead;}

	D3DXVECTOR3 GetHitSize(void) { return m_HitSize; }

	//他の関数
	void AddPowerX(float PowerX) { m_PowerOther.x += PowerX; }
	void VertexLockRorate(float fAngle);

private:
	void BallAliveAction(void);
	void BallDeadAction(void);
	bool GameNotStart();

	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_PowerOther;              //プレーヤー以外の外力
	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_HitSize;
	bool m_StandFloor;                     //地面に立ってる
	bool m_bDead;
	int m_nCntChangeUV;
	int m_nCntMotionChange;
	static int s_nPriority;

	float m_fAngle;
	bool m_TexChangeMove;
	bool m_bMoveDir;
};

#endif