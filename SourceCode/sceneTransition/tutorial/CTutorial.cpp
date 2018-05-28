#include "CTutorial.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "TexManager.h"
#include "CGameStage.h"
#include "CSceneTraBotton.h"
#include "CPlayerSelecter.h"
#include "TutorialMaster.h"
#include "CFontUIScale.h"

/**************************SCENE_TUTORIAL部分*****************************/
void CTutorial::Init(void)
{
	//オブジェクトの生成
	CGameStage::LoadStageData(TUTORIAL01_DATA);

	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.08*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT*0.08, 0.0f), BLADE_TEX);
	CSceneTraBotton::Create(D3DXVECTOR3(SCREEN_WIDTH*0.93, SCREEN_HEIGHT*0.04, 0.0f), D3DXVECTOR3(100, 50, 0.0f), SKIP_BUTTON_TEX);

	CFontUIScale::Create(D3DXVECTOR3(SCREEN_WIDTH*0.795, SCREEN_HEIGHT*0.040, 0.0f), D3DXVECTOR3(50, 50, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.795, SCREEN_HEIGHT*0.040, 0.0f), 255, HASAMI_ICON_TEX);
	CFontUIScale::Create(D3DXVECTOR3(SCREEN_WIDTH*0.83, SCREEN_HEIGHT*0.040, 0.0f), D3DXVECTOR3(28, 28, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.83, SCREEN_HEIGHT*0.040, 0.0f), 255, HASAMI_X_TEX);
}
void CTutorial::Uninit(void)
{
	CScene::ReleaseAll();
}