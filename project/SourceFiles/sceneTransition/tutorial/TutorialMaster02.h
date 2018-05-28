#pragma once
#ifndef TUTORIAL_MASTER02_H_
#define TUTORIAL_MASTER02_H_

#include "main.h"
#include "CPlayer.h"
#include "CScoreGame.h"
#include "CSceneTraBotton.h"
#include "CPlayerArrow.h"
#include "CFontUIEffect.h"
#include "CPlayerSelecterEF.h"

class CTutorialMaster02
{
public:
	typedef enum
	{
		STEP_NONE = 0,
		STEP_CREATE_PLAYER1,
		STEP_DRAG_PLAYER1,
		STEP_CREATE_PLAYER2,
		STEP_DRAG_PLAYER2,
		STEP_CREATE_COUNT,
		STEP_COUNT_DOWN,
		STEP_GAME_CAN_START
	}GAME_STEP;

	typedef enum
	{
		FADE_IN = 0,
		FADE_OUT
	}FONT_FADE;

	//Init,Update,Uninit�֐�
	void Init(void);
	void Update(void);
	void Uninit(void);

	//�Q�b�^�[
	bool GetGameStartFlag(void) { return m_bGameStart; }

private:
	//�����o�֐�
	void TutorialStart(void);
	void MouseCreatePlayer1(void);
	void MouseDragPlayer1(void);
	void MouseCreatePlayer2(void);
	void MouseDragPlayer2(void);
	void GameCanStart(void);
	void GameStart(void);
	void GameFail(void);
	void GamePlayerKill(void);
	void GamePlayerReset(void);
	void TutorialSkip(void);
	void DeleteAllTutorialUI(void);
	void DeleteAllAllTutorialUI(void);
	bool MousePosInClickZone(void);
	void CountDown(void);
	void LockPlayerArrow(void);
	void CreatePlayerArrow(void);
	void DeletePlayerArrow(void);
	void DeletePlayerGuild(void);
	void FontEffect(void);

	void SelecterEF(void);

	//�t�H���g�G�t�F�N�g�֘A
	void CreateFontEffect(void);
	void ClearFontEffect(void);

	int m_TutorialStartTime;
	int m_Num_PlayerCanUse;                    //�g�p�ł���v���[���[�̐�
	bool m_bGameStart;                         //�v���[���[�ƃ{�[����������t���O
	int m_nPlayerKill;
	GAME_STEP m_GameStep;
	CPlayerArrow *m_PlayerArrowLeft;
	CPlayerArrow *m_PlayerArrowRight;
	CScoreGame *m_GameStartCountDown;
	CSceneTraBotton *m_CountDownFont;
	int m_nGameStartCnt;
	//�t�H���g�֘A
	bool m_MakeFontTimeFlag;
	CFontUIEffect *m_FontEffect;
	FONT_FADE m_FontFade;

	//�v���[���[������̃G�t�F�N�g�֘A
	CPlayerSelecterEF *m_PlayerSelecterEF;
	FONT_FADE m_SelecterMode;
};

#endif