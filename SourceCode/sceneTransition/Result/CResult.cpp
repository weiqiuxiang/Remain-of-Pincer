#include "CResult.h"
#include "CTextBox.h"
#include "CScore.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "CRetryBotton.h"
#include "CNextBotton.h"
#include "TexManager.h"
#include "Particle.h"
#include "Effect.h"
#include "CResultScore.h"
#include "CGameStage.h"
#include "ResultManager.h"
#include "sound.h"

/**************************SCENE_RESULT部分*****************************/
void CResult::Init(void)
{
	//
	if (CResultScore::GetUsePairMin() == 0 || CResultScore::GetUsePairMin() == 1) CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), RESULT_PERFECT_TEX);
	else CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), RESULT_TEX);

	//得点は元より高い時,得点登録
	int nStageScore = CResultScore::GetStageScore(CGameStage::GetStageNumber() - 1);
	if (CResultScore::GetUsePairMin() < nStageScore) CResultScore::SetStageScore(CGameStage::GetStageNumber()-1, CResultScore::GetUsePairMin());//スコア登録

	//ステージクリアフラグを設定
	CResultScore::SetStageClearFlag(CGameStage::GetStageNumber() - 1,true);

	//ナカニシ
	CTextBox* pClearBox = CTextBox::Create(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.17f, 0.0f),
		D3DXVECTOR3(800.0f, 240.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.17f, 0.0f),
		0,
		RESULT_CLEAR_TEX);

	CResultManager::SetClearBox(pClearBox);

	CTextBox* pUsePairText = CTextBox::Create(
		D3DXVECTOR3(-SCREEN_WIDTH * 0.6f, 325.0f, 0.0f),
		D3DXVECTOR3(540.0f, 100.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.45f, 325.0f, 0.0f),
		255,
		RESULT_USEPAIRTEXT_TEX);
	CResultManager::SetUsePairText(pUsePairText);

	CTextBox* pUsePairBox = CTextBox::Create(
		D3DXVECTOR3(-SCREEN_WIDTH * 0.3f, 320.0f, 0.0f),
		D3DXVECTOR3(140.0f, 140.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.715f, 320.0f, 0.0f),
		255,
		RESULT_NUMBER_RANK_BOX_TEX);
	CResultManager::SetUsePairBox(pUsePairBox);

	CNumber* pUsePair = CNumber::Create(
		D3DXVECTOR3(-SCREEN_WIDTH * 0.3f - 45.0f, 260.0f, 0.0f),
		D3DXVECTOR3(80.0f, 120.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.715f - 45.0f, 260.0f, 0.0f),
		255);
	pUsePair->SetNumber(CResultScore::GetUsePairMin());
	CResultManager::SetUsePair(pUsePair);

	CTextBox* pRankText = CTextBox::Create(
		D3DXVECTOR3(-SCREEN_WIDTH * 0.6f, 465.0f, 0.0f),
		D3DXVECTOR3(540.0f, 100.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.45f, 465.0f, 0.0f),
		255,
		RESULT_RANKTEXT_TEX);
	CResultManager::SetRankText(pRankText);

	CTextBox* pRankBox = CTextBox::Create(
		D3DXVECTOR3(-SCREEN_WIDTH * 0.3f, 470.0f, 0.0f),
		D3DXVECTOR3(140.0f, 140.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.715f, 470.0f, 0.0f),
		255,
		RESULT_NUMBER_RANK_BOX_TEX);
	CResultManager::SetRankBox(pRankBox);

	CTextBox* pRank = CTextBox::Create(
		D3DXVECTOR3(-SCREEN_WIDTH * 0.3f, 470.0f, 0.0f),
		D3DXVECTOR3(80.0f, 120.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.715f, 470.0f, 0.0f),
		0,
		RESULT_RANK_VARIETY_TEX);
	CResultManager::SetRank(pRank);

	CRetryBotton* pRetryButton = CRetryBotton::Create(
		D3DXVECTOR3(SCREEN_WIDTH * 0.10f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		RESULT_BUTTON_RETRY_TEX,
		0);
	pRetryButton->Update();
	CResultManager::SetRetryButton(pRetryButton);

	CNextBotton* pNextButton = CNextBotton::Create(
		D3DXVECTOR3(SCREEN_WIDTH * 0.50f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(150.0f, 150.0f, 0.0f),
		RESULT_BUTTON_NEXT_TEX,
		0);
	pNextButton->Update();
	CResultManager::SetNextButton(pNextButton);

	//CGoToTitle* pTitleButton = CGoToTitle::Create(
	//	D3DXVECTOR3(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f, 0.0f),
	//	D3DXVECTOR3(300.0f, 150.0f, 0.0f),
	//	RESULT_RANK_VARIETY_TEX,
	//	0);
	//pTitleButton->Update();
	//CResultManager::SetTitleButton(pTitleButton);

	CGoToSelect* pSelectButton = CGoToSelect::Create(
		D3DXVECTOR3(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(400.0f, 100.0f, 0.0f),
		RESULT_STAGE_SELECT_BOTTON_TEX,
		0);
	pSelectButton->Update();
	CResultManager::SetSelectButton(pSelectButton);

	CEffect::Load(RESULT_PARTICLE_01);

	PlaySound(RESULT_BGM);
}

void CResult::Uninit(void)
{
	CScene::ReleaseAll();
}