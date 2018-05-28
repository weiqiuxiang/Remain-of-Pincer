#include "CMouseClickZone.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CMouseClickZone::s_nPriority = 3;

CMouseClickZone::CMouseClickZone() : CScene2D(3)
{

}

CMouseClickZone::CMouseClickZone(int nPriority) : CScene2D(nPriority)
{
	
}

CMouseClickZone::~CMouseClickZone()
{

}

//プレーヤーのインスタンスを生成する関数
CMouseClickZone *CMouseClickZone::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const char* filePass)
{
	CMouseClickZone *pPlayerArrow;
	pPlayerArrow = new CMouseClickZone(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CMouseClickZone::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TUTORIAL_MOUSECLICKZONE);
	m_bMouseLock = true;
	return S_OK;
}

//更新処理
void CMouseClickZone::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CMouseClickZone::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	//加算合成設定
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	// 描画絵ポリゴンはαで透明化になっていく
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// 先の絵は透明化しない
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//ブレンドモードをアルファブレンドに戻す
	// 先の絵はα値で不透明なっていく
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// 描画絵はα値で透明なっていく
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

//終了処理
void CMouseClickZone::Uninit(void)
{
	CScene2D::Uninit();
}