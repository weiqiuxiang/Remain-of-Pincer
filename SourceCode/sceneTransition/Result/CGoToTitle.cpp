#include "CGoToTitle.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CGoToTitle::s_nPriority = 3;

CGoToTitle::CGoToTitle() : CScene2D(3)
{

}

CGoToTitle::CGoToTitle(int Priority) : CScene2D(Priority)
{
	
}

CGoToTitle::~CGoToTitle()
{

}

//プレーヤーのインスタンスを生成する関数
CGoToTitle *CGoToTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha)
{
	CGoToTitle *pGoToTitleBotton;
	pGoToTitleBotton = new CGoToTitle(s_nPriority);
	pGoToTitleBotton->Init(pos, size, alpha);
	pGoToTitleBotton->LoadTexture(filePass);
	return pGoToTitleBotton;
}

//プレーヤーの初期化
HRESULT CGoToTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_GOTOTITLE_BOTTON);
	m_nAlpha = alpha;
	return S_OK;
}

//更新処理
void CGoToTitle::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CGoToTitle::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CGoToTitle::Uninit(void)
{
	CScene2D::Uninit();
}