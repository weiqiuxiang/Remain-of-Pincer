#include "CTitle.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "TexManager.h"
#include "CTitleMaster.h"
#include "sound.h"

/**************************SCENE_TITLEïîï™*****************************/
void CTitle::Init(void)
{
	CTitleMaster::Init();
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TITLE_BG_TEX);
	
	CTitleMaster::CreateStartExit();                 //titleÇ∆exitÇçÏÇÈ

	// ï∂éö
	CLetter* pLetter[12] = {};
	pLetter[0]  = CLetter::Create(D3DXVECTOR3(160.0f + TITLE_RELETIVE_X, 100.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 80.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_R_TEX);
	pLetter[1]  = CLetter::Create(D3DXVECTOR3(240.0f + TITLE_RELETIVE_X, 140.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f,  80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_E_TEX);
	pLetter[2]  = CLetter::Create(D3DXVECTOR3(340.0f + TITLE_RELETIVE_X, 140.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3(100.0f,  80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_M_TEX);
	pLetter[3]  = CLetter::Create(D3DXVECTOR3(440.0f + TITLE_RELETIVE_X, 140.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f,  70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_A_TEX);
	pLetter[4]  = CLetter::Create(D3DXVECTOR3(560.0f + TITLE_RELETIVE_X, 140.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f,  80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_N_TEX);
	pLetter[5]  = CLetter::Create(D3DXVECTOR3(260.0f + TITLE_RELETIVE_X, 250.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f,  90.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_O_TEX);
	pLetter[6]  = CLetter::Create(D3DXVECTOR3(340.0f + TITLE_RELETIVE_X, 235.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f, 110.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_F_TEX);
	pLetter[7]  = CLetter::Create(D3DXVECTOR3( 80.0f + TITLE_RELETIVE_X, 300.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 80.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_P_TEX);
	pLetter[8]  = CLetter::Create(D3DXVECTOR3(240.0f + TITLE_RELETIVE_X, 340.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f,  80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_N_TEX);
	pLetter[9]  = CLetter::Create(D3DXVECTOR3(320.0f + TITLE_RELETIVE_X, 340.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 70.0f,  90.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_C_TEX);
	pLetter[10] = CLetter::Create(D3DXVECTOR3(400.0f + TITLE_RELETIVE_X, 340.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 60.0f,  70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_E_TEX);
	pLetter[11] = CLetter::Create(D3DXVECTOR3(480.0f + TITLE_RELETIVE_X, 340.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3( 80.0f,  80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 460.0f, 0.0f, LETTER_R2_TEX);

	CTitleMaster::SetLetter(pLetter);
        
	CPillar* pPillarL = CPillar::Create(D3DXVECTOR3(160.0f + TITLE_RELETIVE_X, 325.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3(40.0f, 110.0f, 0.0f),  D3DXVECTOR3( - 50.0f + TITLE_RELETIVE_X, 20.0f + TITLE_RELETIVE_Y, 0.0f), LETTER_I_TEX); 
	CPillar* pPillarR = CPillar::Create(D3DXVECTOR3(500.0f + TITLE_RELETIVE_X, 120.0f + TITLE_RELETIVE_Y, 0.0f), D3DXVECTOR3(40.0f, 110.0f, 0.0f),  D3DXVECTOR3(650.0f + TITLE_RELETIVE_X, 20.0f + TITLE_RELETIVE_Y, 0.0f), LETTER_I_TEX);          

	CTitleMaster::SetPillar(pPillarL, pPillarR);

	PlaySound(TITLE_BGM);
}

void CTitle::Uninit(void)
{
	CScene::ReleaseAll();
	CExplosion::Unload();
}