#include "CSceneTraBotton.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CSceneTraBotton::s_nPriority = 5;

CSceneTraBotton::CSceneTraBotton() : CScene2D(3)
{

}

CSceneTraBotton::CSceneTraBotton(int nPriority) : CScene2D(nPriority)
{

}

CSceneTraBotton::~CSceneTraBotton()
{

}

//プレーヤーのインスタンスを生成する関数
CSceneTraBotton *CSceneTraBotton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CSceneTraBotton *pPlayerSelecter;
	pPlayerSelecter = new CSceneTraBotton(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	return pPlayerSelecter;
}

//プレーヤーの初期化
HRESULT CSceneTraBotton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_RESET_BOTTON);
	m_Scale = 1.0f;
	m_OriginSize = size;                     //元のサイズ
	return S_OK;
}

//更新処理
void CSceneTraBotton::Update(void)
{
	m_size = m_OriginSize * m_Scale;
	CScene2D::VertexLock();
}

//描画処理
void CSceneTraBotton::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CSceneTraBotton::Uninit(void)
{
	CScene2D::Uninit();
}