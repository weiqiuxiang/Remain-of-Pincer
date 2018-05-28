#include "CEditorBall.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CEditorBall::s_nPriority = 3;

CEditorBall::CEditorBall() : CScene2D(3)
{

}

CEditorBall::CEditorBall(int nPriority) : CScene2D(nPriority)
{
	
}

CEditorBall::~CEditorBall()
{

}

//プレーヤーのインスタンスを生成する関数
CEditorBall *CEditorBall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CEditorBall *pPlayerArrow;
	pPlayerArrow = new CEditorBall(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CEditorBall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_EDITOR_BALL);
	return S_OK;
}

//更新処理
void CEditorBall::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CEditorBall::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CEditorBall::Uninit(void)
{
	CScene2D::Uninit();
}