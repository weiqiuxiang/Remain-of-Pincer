#define _CRT_SECURE_NO_WARNINGS
#include "CEditor.h"
#include "CEditorSetObj.h"
#include "CBackground.h"
#include "CExplosion.h"
#include "CFloor.h"
#include "CBall.h"
#include "TexManager.h"

/**************************SCENE_RESULTïîï™*****************************/

CEditor::CEditor()
{
	
}

CEditor::~CEditor()
{
	
}

void CEditor::Init(void)
{
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), BACKGROUND_TEXTURENAME);
	CEditorSetObj::Init();             //ï“èWäÌèâä˙âª
}

void CEditor::Uninit(void)
{
	CScene::ReleaseAll();
}