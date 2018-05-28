#include "CPlayerSelecter.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CPlayerSelecter::s_nPriority = 3;

CPlayerSelecter::CPlayerSelecter() : CScene2D(3)
{

}

CPlayerSelecter::CPlayerSelecter(int nPriority) : CScene2D(nPriority)
{

}

CPlayerSelecter::~CPlayerSelecter()
{

}

//プレーヤーのインスタンスを生成する関数
CPlayerSelecter *CPlayerSelecter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const RGB& rgb, bool bAlphaBlend, const char* filePass)
{
	CPlayerSelecter *pPlayerSelecter;
	pPlayerSelecter = new CPlayerSelecter(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	pPlayerSelecter->SetAlpha(nAlpha);
	pPlayerSelecter->SetColor(rgb);
	pPlayerSelecter->SetAlphaBlend(bAlphaBlend);
	pPlayerSelecter->VertexLock();
	return pPlayerSelecter;
}

//プレーヤーの初期化
HRESULT CPlayerSelecter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_PLAYER_SELECTER);
	m_Scale = 1.0f;
	m_OriginSize = size;
	return S_OK;
}

//更新処理
void CPlayerSelecter::Update(void)
{
	m_size = m_OriginSize * m_Scale;        //スケール後のサイズ
	CScene2D::VertexLock();
}

//描画処理
void CPlayerSelecter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();
	if (m_bAlphaBlend == true)
	{
		//加算有効
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		CScene2D::Draw();

		//加算無効
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}

	else
	{
		CScene2D::Draw();
	}
}

//終了処理
void CPlayerSelecter::Uninit(void)
{
	CScene2D::Uninit();
}