#pragma once

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "main.h"
#include "scene2D.h"
#include "Particle.h"

//前方宣言
class CScene2D;

class CPlayer:public CScene2D
{
public:
	CPlayer();
	CPlayer(int nPriority = 3);
	~CPlayer();

	//Init,Uninit,Update,Draw関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ゲッター
	D3DXVECTOR3 GetSpeed(void);
	D3DXVECTOR3 GetPosOld(void);
	int GetPlayerId(void);
	bool GetMouseLock(void) { return m_MouseLock; }
	bool GetDirectionYes(void) { return m_bDirectionYes; }
	bool GetMoveDirection(void) { return m_bMoveDirection; }

	//セッター
	void AddMove(float SpeedX);
	void SetPosition(const D3DXVECTOR3& playerPos);
	void SetMouseLock(bool mouseLookFlag) { m_MouseLock = mouseLookFlag; }
	void SetMoveDirection(bool MoveDirection) { m_bMoveDirection = MoveDirection; }
	void SetDirectionYes(bool DirectionYes) { m_bDirectionYes = DirectionYes; }
	void AddPowerX(float AddPowerX) { m_Power.x += AddPowerX; }

	//他の関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
	
private:
	//メンバ関数
	bool GameNotStart(void);          //ゲーム始まる前の処理
	void HitFloorBeforeGameStart(void);
	void HitFloorNormal(void);
	void HitFloor(void);             //地面に対する当り判定
	void HitFloorCanNotMove(void);   //壁に嵌った時の対策
	void HitOtherPlayer(void);
	void PushOtherPlayer(int SceneID);
	void ChangeDirectionSeeOtherPlayer(void);
	void ChangeDirectionSeeOtherPlayerGameNotStart(void);
	void MouseCreatePlayerGuild(bool bHitPlayerAndFloor);
	void SetEarthquake(void);
	void PlayHitSound(void);
	void MoveParticle(void);                     //移動の時のパーティクル

	//メンバ変数
	D3DXVECTOR3				m_posOld;		// ポリゴンの古い位置
	D3DXVECTOR3				m_speed;	    // ポリゴンの速度
	D3DXVECTOR3             m_speedOld;
	D3DXVECTOR3             m_Power;
	int                     m_PlayerID;
	bool m_StandFloor;                     //地面に立ってる
	bool m_StandFloorOld;                  //古い位置
	bool m_MouseLock;                      //マウスに選択された状態
	bool m_bMoveDirection;                 //進行方向
	bool m_bDirectionYes;                  //進行方向すでに決まっているかどうか

	//パーティクル関連
	CParticle *m_Particle;
	CParticle *m_ParticleHitFloor;
	int m_HitFloorTime;
	static int s_nPriority;
};

#endif