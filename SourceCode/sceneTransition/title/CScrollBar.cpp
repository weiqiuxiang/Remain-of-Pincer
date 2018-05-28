#include "CScrollBar.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CScrollBar::s_nPriority = 8;

CScrollBar::CScrollBar() : CScene2D(3)
{

}

CScrollBar::CScrollBar(int nPriority) : CScene2D(nPriority)
{
	
}

CScrollBar::~CScrollBar()
{

}

//プレーヤーのインスタンスを生成する関数
CScrollBar *CScrollBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nAlpha, const char* filePass)
{
	CScrollBar *pPlayerArrow;
	pPlayerArrow = new CScrollBar(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CScrollBar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_SCROLL_BAR);
	m_bMouseLock = true;
	return S_OK;
}

//更新処理
void CScrollBar::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CScrollBar::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CScrollBar::Uninit(void)
{
	CScene2D::Uninit();
}