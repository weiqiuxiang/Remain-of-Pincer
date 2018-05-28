#include "CEditorSpring.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CEditorSpring::s_nPriority = 3;

CEditorSpring::CEditorSpring() : CScene2D(3)
{

}

CEditorSpring::CEditorSpring(int nPriority) : CScene2D(nPriority)
{
	
}

CEditorSpring::~CEditorSpring()
{

}

//プレーヤーのインスタンスを生成する関数
CEditorSpring *CEditorSpring::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CEditorSpring *pPlayerArrow;
	pPlayerArrow = new CEditorSpring(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CEditorSpring::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_EDITOR_SPRING);
	return S_OK;
}

//更新処理
void CEditorSpring::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CEditorSpring::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CEditorSpring::Uninit(void)
{
	CScene2D::Uninit();
}