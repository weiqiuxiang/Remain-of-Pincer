#include "CTutorial02.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "TexManager.h"
#include "CGameStage.h"
#include "CSceneTraBotton.h"
#include "CPlayerSelecter.h"
#include "TutorialMaster.h"

/**************************SCENE_TUTORIAL部分*****************************/
void CTutorial02::Init(void)
{
	//オブジェクトの生成
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), BACKGROUND_TEXTURENAME);

	CGameStage::LoadStageData(TUTORIAL02_DATA);

	CSceneTraBotton::Create(D3DXVECTOR3(SCREEN_WIDTH*0.95, SCREEN_HEIGHT*0.04, 0.0f), D3DXVECTOR3(100, 25.0f, 0.0f), SKIP_BUTTON_TEX);
	CPlayerSelecter::Create
	(
		D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(10, 50.0f, 0.0f),
		255, {255,255,255},false,PLAYER_TEX
	);
}
void CTutorial02::Uninit(void)
{
	CScene::ReleaseAll();
}