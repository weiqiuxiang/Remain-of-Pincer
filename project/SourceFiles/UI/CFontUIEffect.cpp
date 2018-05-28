#include "CFontUIEffect.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CFontUIEffect::s_nPriority = 5;

CFontUIEffect::CFontUIEffect() : CScene2D(3)
{

}

CFontUIEffect::CFontUIEffect(int nPriority) : CScene2D(nPriority)
{

}

CFontUIEffect::~CFontUIEffect()
{

}

//プレーヤーのインスタンスを生成する関数
CFontUIEffect *CFontUIEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nAlpha,const RGB& rgb,bool bAlphaBlend , const char* filePass)
{
	CFontUIEffect *pPlayerArrow;
	pPlayerArrow = new CFontUIEffect(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	pPlayerArrow->SetColor(rgb);
	pPlayerArrow->SetAlphaBlend(bAlphaBlend);
	pPlayerArrow->VertexLock();
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CFontUIEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TUTORIAL_EFFECT_UI);
	m_bMouseLock = true;
	return S_OK;
}

//更新処理
void CFontUIEffect::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CFontUIEffect::Draw(void)
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
void CFontUIEffect::Uninit(void)
{
	CScene2D::Uninit();
}