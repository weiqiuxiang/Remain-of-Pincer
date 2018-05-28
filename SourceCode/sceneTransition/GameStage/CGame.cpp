#define _CRT_SECURE_NO_WARNINGS
#include "CGame.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "CBall.h"
#include "CFloor.h"
#include "CScore.h"
#include "CPlayerSelecter.h"
#include "CSceneTraBotton.h"
#include "TexManager.h"
#include "CResultScore.h"
#include "CEditorSetObj.h"
#include "CGameStage.h"
#include "CSpring.h"
#include "CScoreGame.h"
#include "CResultScore.h"
#include "CFontUI.h"
#include <stdio.h>
#include "GameMaster.h"
#include "SceneTransition.h"
#include "CFontUIEffect.h"
#include "CGameStage.h"
#include "sound.h"

//マグロ
#define FLOOR_BLOCK_HEIGHT (30.0f)

/**************************SCENE_GAME部分*****************************/
void CGame::Init(void)
{
	CResultScore::Init();            //スコア初期化

	//オブジェクトの生成
	CGameStage::StageSelect(CGameStage::GetStageNumber());

	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.08*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT*0.08, 0.0f), BLADE_TEX);

	CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.795, SCREEN_HEIGHT*0.040, 0.0f), D3DXVECTOR3(50, 50, 0.0f),255, HASAMI_ICON_TEX);
	CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.83, SCREEN_HEIGHT*0.040, 0.0f), D3DXVECTOR3(28, 28, 0.0f), 255, HASAMI_X_TEX);

	CFontUIScale::Create(
		D3DXVECTOR3(SCREEN_WIDTH*0.5 - 110.16*0.3, SCREEN_HEIGHT*0.04, 0.0f),
		D3DXVECTOR3(110.16, 30.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH*0.5 - 110.16*0.3, SCREEN_HEIGHT*0.04, 0.0f),
		255, STAGE_FONT_TEX
	);

	CScoreScale* pScore = CScoreScale::Create(
		D3DXVECTOR3(SCREEN_WIDTH*0.5 + 40, SCREEN_HEIGHT*0.04, 0.0f),
		D3DXVECTOR3(23.4f, 30.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH*0.5 + 40, SCREEN_HEIGHT*0.04, 0.0f),
		2, STAGE_NUMBER_TEX
	);
	pScore->SetScore(CGameStage::GetStageNumber());
	pScore->Update();

	PlaySound(TITLE_BGM);
}

void CGame::Uninit(void)
{
	CScene::ReleaseAll();
}