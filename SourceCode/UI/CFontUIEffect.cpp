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

//�v���[���[�̃C���X�^���X�𐶐�����֐�
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

//�v���[���[�̏�����
HRESULT CFontUIEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TUTORIAL_EFFECT_UI);
	m_bMouseLock = true;
	return S_OK;
}

//�X�V����
void CFontUIEffect::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CFontUIEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();
	if (m_bAlphaBlend == true)
	{
		//���Z�L��
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		CScene2D::Draw();

		//���Z����
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}

	else
	{
		CScene2D::Draw();
	}
}

//�I������
void CFontUIEffect::Uninit(void)
{
	CScene2D::Uninit();
}