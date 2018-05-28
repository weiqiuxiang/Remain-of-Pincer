//ファイル名 : ResultManager.h
//更新日 : 20170424
//Author : nakanishi yusuke
//説明 : リザルトの管理

#pragma once

#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_

#include "main.h"
#include "CTextBox.h"
#include "CScore.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "CRetryBotton.h"
#include "CNextBotton.h"
#include "CGoToTitle.h"
#include "CGoToSelect.h"
#include "TexManager.h"
#include "Particle.h"
#include "Effect.h"

class CResultManager
{
public:
	typedef enum
	{
		STEP_1 = 0,
		STEP_2,
		STEP_3,
		STEP_4,
		STEP_5,
		STEP_6,
		STEP_7,
		STEP_8
	}RESULT_STEP;

	typedef enum
	{
		RANK_S = 0,
		RANK_A,
		RANK_B,
		RANK_C
	}RANK;

	CResultManager();
	~CResultManager();

	//Init,Update,Uninit関数
	void Init(void);
	void Update(void);
	void Uninit(void);

	void SetUp(void);
	void UpdateClear(void);
	void UpdateUsePair(void);
	void UpdateRank(void);
	void UpdateRankVariety(void);

	void RetryGame(void);
	void NextGame(void);
	void GoToTitle(void);
	void GoToSelect(void);

	static void NullAllPointer(void);

	static void SetClear(CTextBox* pClear) { m_Clear = pClear; }
	static void SetClearBox(CTextBox* pClearBox) { m_ClearBox = pClearBox; }
	static void SetUsePair(CNumber* pUsePair) { m_UsePair = pUsePair; }
	static void SetUsePairText(CTextBox* pUsePairText) { m_UsePairText = pUsePairText; }
	static void SetUsePairBox(CTextBox* pUsePairBox) { m_UsePairBox = pUsePairBox; }
	static void SetRank(CTextBox* pRank) { m_Rank = pRank; }
	static void SetRankBox(CTextBox* pRankBox) { m_RankBox = pRankBox; }
	static void SetRankText(CTextBox* pRankText) { m_RankText = pRankText; }
	static void SetRetryButton(CRetryBotton* pRetryButton) { m_RetryButton = pRetryButton; }
	static void SetNextButton(CNextBotton* pNextButton) { m_NextButton = pNextButton; }
	static void SetTitleButton(CGoToTitle* pTitleButton) { m_TitleButton = pTitleButton; }
	static void SetSelectButton(CGoToSelect* pSelectButton) { m_SelectButton = pSelectButton; }

private:
	//メンバ関数
	RESULT_STEP m_ResultStep;
	bool m_skip;
	int m_timer;

	int m_changeAlpha;
	float m_changePosRate;
	float m_changeValue;
	D3DXVECTOR3 m_startPos;
	D3DXVECTOR3 m_endPos;
	float m_deltaY;

	//Cランク演出
	int m_nCRankFrameCount;
	bool m_bFlagRankCJump;

	// ポインタ
	static CTextBox* m_Clear;
	static CTextBox* m_ClearBox;
	static CNumber* m_UsePair;
	static CTextBox* m_UsePairBox;
	static CTextBox* m_UsePairText;
	static CTextBox* m_Rank;
	static CTextBox* m_RankBox;
	static CTextBox* m_RankText;
	static CRetryBotton* m_RetryButton;
	static CNextBotton* m_NextButton;
	static CGoToSelect* m_SelectButton;
	static CGoToTitle* m_TitleButton;
	static CParticle* m_Particle;
};

#endif