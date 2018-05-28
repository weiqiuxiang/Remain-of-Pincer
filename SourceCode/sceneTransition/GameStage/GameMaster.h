//�t�@�C���� : GameManager.h
//�X�V�� : 20170424
//Author : i syuusyou
//���� : ���蔻��̏����ƃv���[���[�̃R���g���[��

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

	//Init,Update,Uninit�֐�
	void Init(void);
	void Update(void);
	void Uninit(void);

	//�Z�b�^�[
	void SetScorePointer(CScoreGame *pScore);
	void SetPauseFlag(bool PauseFlag) { m_bGamePause = PauseFlag; }

	//�Q�b�^�[
	bool GetGameStartFlag(void) {return m_bGameStart;}
	bool GetPauseFlag(void) { return m_bGamePause; }

private:
	//�����o�֐�
	void MouseCreatePlayer(void);
	void CreatePlayerArrow(void);                   //�v���[���[�̖������
	void CreatePlayerSelecterEF(void);
	void DeletePlayerArrow(void);                   //��������
	void DeletePlayerGuild(void);
	void LockPlayerArrow(void);                     //�v���[���[���̌Œ�
	void MouseDragPlayer(void);
	void GameCanStart(void);
	void GameStart(void);
	void GameFail(void);
	void GamePlayerKill(void);
	void GamePlayerReset(void);
	void GameReset(void);
	void CountDown(void);
	void GameClear(void);
	void ShowClear(void);        //�N���A���o
	bool HitMenuBotton(void);
	bool HitResetBotton(void);
	void ScaleMenuBotton(void);
	void ScaleResetBotton(void);
	bool PlayerOutRange(void);

	void SelecterEF(void);
	void SelecterScaleUp(void);
	void SelecterScaleDown(void);

	void UpdateGamePause(void);

	//�����o�ϐ�
	int m_Num_PlayerCanUse;                    //�g�p�ł���v���[���[�̐�
	bool m_bGameStart;                         //�v���[���[�ƃ{�[����������t���O
	int m_nPlayerKill;
	GAME_STEP m_GameStep;
	int m_nCntGameClear;
	CXBOXController  *GamePadState;

	CPlayerArrow *m_PlayerArrowLeft;
	CPlayerArrow *m_PlayerArrowRight;
	CScoreGame *m_pScore;
	int m_nGameStartCnt;

	//�v���[���[������̃G�t�F�N�g�֘A
	CPlayerSelecter *m_PlayerSelecter;
	CPlayerSelecterEF *m_PlayerSelecterEF;
	FONT_FADE m_SelecterMode;
	CFontUI *m_ClearUI;
	CFontUIScale *m_ResetBotton;
	CFontUIScale *m_MenuBotton;

	//�p�[�e�B�N���֘A
	CParticle *m_ClearParticle;
	int m_nParticleCounter;

	bool m_bGamePause;
	
};

#endif