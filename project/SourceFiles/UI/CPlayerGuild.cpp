#include "CPlayerGuild.h"
#include "SceneTransition.h"
#include "hitCheck.h"

#define SCROLL_SPEED (0.005f)

int CPlayerGuild::s_nPriority = 3;

CPlayerGuild::CPlayerGuild() : CScene2D(3)
{

}

CPlayerGuild::CPlayerGuild(int nPriority) : CScene2D(nPriority)
{

}

CPlayerGuild::~CPlayerGuild()
{

}

//プレーヤーのインスタンスを生成する関数
CPlayerGuild *CPlayerGuild::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Alpha, const char* filePass)
{
	CPlayerGuild *pPlayerArrow;
	pPlayerArrow = new CPlayerGuild(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(Alpha);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CPlayerGuild::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_PLAYER_GUILD);
	m_bMouseLock = true;
	return S_OK;
}

//更新処理
void CPlayerGuild::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CPlayerGuild::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CPlayerGuild::Uninit(void)
{
	CScene2D::Uninit();
}