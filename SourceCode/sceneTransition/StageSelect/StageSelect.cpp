#include "StageSelect.h"
#include "CStageMaster.h"
#include "CBackground.h"
#include "TexManager.h"
#include "CExplosion.h"
#include "sound.h"

void CStageSelect::Init(void)
{
	CStageMaster::Init();
	CStageMaster::CreateStageSelectBar();
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5,0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), STAGE_SELECT_TEX);

	PlaySound(TITLE_BGM);
}

void CStageSelect::Uninit(void)
{
	CStageMaster::Uninit();
	CScene::ReleaseAll();
}