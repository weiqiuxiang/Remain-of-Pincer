#pragma once
#ifndef TUTORIAL_MASTER_H_
#define TUTORIAL_MASTER_H_

#include "main.h"
#include "CPlayer.h"
#include "CScoreGame.h"
#include "CSceneTraBotton.h"
#include "CPlayerArrow.h"
#include "CFontUIEffect.h"
#include "CPlayerSelecter.h"
#include "CPlayerSelecterEF.h"

class CTutorialMaster
{
public:
	typedef enum
	{
		STEP_NONE = 0,
		STEP_CREATE_PLAYER1,
		STEP_DRAG_PLAYER1,
		STEP_CREATE_PLAYER2,
		STEP_SHOW_MOVE_DIR_LEFT,
		STEP_SHOW_MOVE_DIR_RIGHT,
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
	void ClearFontEffect(void);
	void FontEffect(void);

	void SelecterEF(void);
	void CreatePlayerSelecterEF(void);
	void SelecterScaleUp(void);
	void SelecterScaleDown(void);

	//STEP_SHOW_MOVE_DIR
	void ShowLeft(void);
	void ShowRight(void);

	int m_TutorialStartTime;
	int m_Num_PlayerCanUse;                    //�g�p�ł���v���[���[�̐�
	bool m_bGameStart;                         //�v���[���[�ƃ{�[����������t���O
	int m_nPlayerKill;
	GAME_STEP m_GameStep;
	CPlayerArrow *m_PlayerArrowLeft;
	CPlayerArrow *m_PlayerArrowRight;
	CPlayerArrow *m_ExplainArrow;
	//�t�H���g�֘A
	CFontUIEffect *m_FontEffect;
	FONT_FADE m_FontFade;

	int m_nGameStartCnt;

	//�v���[���[������̃G�t�F�N�g�֘A
	CPlayerSelecter *m_PlayerSelecter;
	CPlayerSelecterEF *m_PlayerSelecterEF;
	FONT_FADE m_SelecterMode;

	CScoreGame *m_pScore;
};

#endif