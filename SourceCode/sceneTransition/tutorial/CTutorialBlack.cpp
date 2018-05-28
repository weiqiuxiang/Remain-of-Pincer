#include "CTutorialBlack.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CTutorialBlack::s_nPriority = 3;

CTutorialBlack::CTutorialBlack() : CScene2D(3)
{

}

CTutorialBlack::CTutorialBlack(int nPriority) : CScene2D(nPriority)
{

}

CTutorialBlack::~CTutorialBlack()
{

}

//プレーヤーのインスタンスを生成する関数
CTutorialBlack *CTutorialBlack::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nAlpha, const char* filePass)
{
	CTutorialBlack *pPlayerArrow;
	pPlayerArrow = new CTutorialBlack(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CTutorialBlack::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TUTORIAL_BLACK);
	m_bMouseLock = true;
	return S_OK;
}

//更新処理
void CTutorialBlack::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CTutorialBlack::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CTutorialBlack::Uninit(void)
{
	CScene2D::Uninit();
}