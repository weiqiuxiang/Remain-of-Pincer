#include "CEditorEraser.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CEditorEraser::s_nPriority = 3;

CEditorEraser::CEditorEraser() : CScene2D(3)
{

}

CEditorEraser::CEditorEraser(int nPriority) : CScene2D(nPriority)
{

}

CEditorEraser::~CEditorEraser()
{

}

//プレーヤーのインスタンスを生成する関数
CEditorEraser *CEditorEraser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CEditorEraser *pPlayerArrow;
	pPlayerArrow = new CEditorEraser(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CEditorEraser::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_EDITOR_ERASER);
	return S_OK;
}

//更新処理
void CEditorEraser::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CEditorEraser::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CEditorEraser::Uninit(void)
{
	CScene2D::Uninit();
}