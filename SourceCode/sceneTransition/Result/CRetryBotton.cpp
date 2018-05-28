#include "CRetryBotton.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CRetryBotton::s_nPriority = 3;

CRetryBotton::CRetryBotton() : CScene2D(3)
{

}

CRetryBotton::CRetryBotton(int Priority) : CScene2D(Priority)
{

}

CRetryBotton::~CRetryBotton()
{

}

//プレーヤーのインスタンスを生成する関数
CRetryBotton *CRetryBotton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha)
{
	CRetryBotton *pRetryBotton;
	pRetryBotton = new CRetryBotton(s_nPriority);
	pRetryBotton->Init(pos, size, alpha);
	pRetryBotton->LoadTexture(filePass);
	return pRetryBotton;
}

//プレーヤーの初期化
HRESULT CRetryBotton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_RETRY_BOTTON);
	m_nAlpha = alpha;
	return S_OK;
}

//更新処理
void CRetryBotton::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CRetryBotton::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CRetryBotton::Uninit(void)
{
	CScene2D::Uninit();
}