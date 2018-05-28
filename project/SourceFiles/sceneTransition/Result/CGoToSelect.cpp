#include "CGoToSelect.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CGoToSelect::s_nPriority = 3;

CGoToSelect::CGoToSelect() : CScene2D(3)
{

}

CGoToSelect::CGoToSelect(int Priority) : CScene2D(Priority)
{
	
}

CGoToSelect::~CGoToSelect()
{

}

//プレーヤーのインスタンスを生成する関数
CGoToSelect *CGoToSelect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha)
{
	CGoToSelect *pGoToSelect;
	pGoToSelect = new CGoToSelect(s_nPriority);
	pGoToSelect->Init(pos, size, alpha);
	pGoToSelect->LoadTexture(filePass);
	return pGoToSelect;
}

//プレーヤーの初期化
HRESULT CGoToSelect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_GOTOSELECT_BOTTON);
	m_nAlpha = alpha;
	return S_OK;
}

//更新処理
void CGoToSelect::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CGoToSelect::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CGoToSelect::Uninit(void)
{
	CScene2D::Uninit();
}