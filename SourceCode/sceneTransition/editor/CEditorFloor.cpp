#include "CEditorFloor.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CEditorFloor::s_nPriority = 3;

CEditorFloor::CEditorFloor() : CScene2D(3)
{

}

CEditorFloor::CEditorFloor(int nPriority) : CScene2D(nPriority)
{
	
}

CEditorFloor::~CEditorFloor()
{

}

//プレーヤーのインスタンスを生成する関数
CEditorFloor *CEditorFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CEditorFloor *pPlayerArrow;
	pPlayerArrow = new CEditorFloor(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CEditorFloor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_EDITOR_FLOOR);
	return S_OK;
}

//更新処理
void CEditorFloor::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CEditorFloor::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CEditorFloor::Uninit(void)
{
	CScene2D::Uninit();
}