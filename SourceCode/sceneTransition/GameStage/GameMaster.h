//ファイル名 : GameManager.h
//更新日 : 20170424
//Author : i syuusyou
//説明 : 当り判定の処理とプレーヤーのコントロール

#pragma once

#ifndef _GAMEMASTER_H_
#define _GAMEMASTER_H_

#include "main.h"
#include "CPlayer.h"
#include "XInputGamepad.h"
#include "CFontUI.h"
#include "CScoreGame.h"
#include "CSceneTraBotton.h"
#include "CPlayerArrow.h"
#include "CJudge.h"
#include "CPlayerSelecter.h"
#include "CPlayerSelecterEF.h"
#include "CFontUIScale.h"
#include "Particle.h"

class CGameManager
{
public:
	typedef enum
	{
		STEP_CREATE_SCORE = 0,
		STEP_CREATE_PLAYER,
		STEP_DRAG_PLAYER,
		STEP_COUNT_DOWN,
		STEP_DECIDE_ARROW_DIRECTION,
		STEP_GAME_CAN_START,
		STEP_CLEAR
	}GAME_STEP;

	typedef enum
	{
		FADE_IN = 0,
		FADE_OUT
	}FONT_FADE;

	CGameManager();
	~CGameManager();

	//Init,Update,Uninit関数
	void Init(void);
	void Update(void);
	void Uninit(void);

	//セッター
	void SetScorePointer(CScoreGame *pScore);
	void SetPauseFlag(bool PauseFlag) { m_bGamePause = PauseFlag; }

	//ゲッター
	bool GetGameStartFlag(void) {return m_bGameStart;}
	bool GetPauseFlag(void) { return m_bGamePause; }

private:
	//メンバ関数
	void MouseCreatePlayer(void);
	void CreatePlayerArrow(void);                   //プレーヤーの矢印を作る
	void CreatePlayerSelecterEF(void);
	void DeletePlayerArrow(void);                   //矢印を消す
	void DeletePlayerGuild(void);
	void LockPlayerArrow(void);                     //プレーヤー矢印の固定
	void MouseDragPlayer(void);
	void GameCanStart(void);
	void GameStart(void);
	void GameFail(void);
	void GamePlayerKill(void);
	void GamePlayerReset(void);
	void GameReset(void);
	void CountDown(void);
	void GameClear(void);
	void ShowClear(void);        //クリア演出
	bool HitMenuBotton(void);
	bool HitResetBotton(void);
	void ScaleMenuBotton(void);
	void ScaleResetBotton(void);
	bool PlayerOutRange(void);

	void SelecterEF(void);
	void SelecterScaleUp(void);
	void SelecterScaleDown(void);

	void UpdateGamePause(void);

	//メンバ変数
	int m_Num_PlayerCanUse;                    //使用できるプレーヤーの数
	bool m_bGameStart;                         //プレーヤーとボールが動けるフラグ
	int m_nPlayerKill;
	GAME_STEP m_GameStep;
	int m_nCntGameClear;
	CXBOXController  *GamePadState;

	CPlayerArrow *m_PlayerArrowLeft;
	CPlayerArrow *m_PlayerArrowRight;
	CScoreGame *m_pScore;
	int m_nGameStartCnt;

	//プレーヤー発生器のエフェクト関連
	CPlayerSelecter *m_PlayerSelecter;
	CPlayerSelecterEF *m_PlayerSelecterEF;
	FONT_FADE m_SelecterMode;
	CFontUI *m_ClearUI;
	CFontUIScale *m_ResetBotton;
	CFontUIScale *m_MenuBotton;

	//パーティクル関連
	CParticle *m_ClearParticle;
	int m_nParticleCounter;

	bool m_bGamePause;
	
};

#endif