#include "CFontUI.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CFontUI::s_nPriority = 5;

CFontUI::CFontUI() : CScene2D(3)
{

}

CFontUI::CFontUI(int nPriority) : CScene2D(nPriority)
{

}

CFontUI::~CFontUI()
{

}

//プレーヤーのインスタンスを生成する関数
CFontUI *CFontUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nAlpha, const char* filePass)
{
	CFontUI *pPlayerArrow;
	pPlayerArrow = new CFontUI(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CFontUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TUTORIAL_UI);
	m_bMouseLock = true;
	return S_OK;
}

//更新処理
void CFontUI::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CFontUI::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CFontUI::Uninit(void)
{
	CScene2D::Uninit();
}