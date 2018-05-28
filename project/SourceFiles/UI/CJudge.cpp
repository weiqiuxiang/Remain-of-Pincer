#include "CJudge.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CJudge::s_nPriority = 5;

CJudge::CJudge() : CScene2D(5)
{

}

CJudge::CJudge(int nPriority) : CScene2D(nPriority)
{

}

CJudge::~CJudge()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CJudge *CJudge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const RGB& rgb, bool bAlphaBlend, const D3DXVECTOR2& UV, const D3DXVECTOR2& UVHW, const char* filePass)
{
	CJudge *pPlayerArrow;
	pPlayerArrow = new CJudge(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	pPlayerArrow->SetColor(rgb);
	pPlayerArrow->SetAlphaBlend(bAlphaBlend);
	pPlayerArrow->SetUV(UV);
	pPlayerArrow->SetUVWH(UVHW);
	pPlayerArrow->VertexLock();
	return pPlayerArrow;
}

//�v���[���[�̏�����
HRESULT CJudge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_JUDGE);
	m_bMouseLock = true;
	return S_OK;
}

//�X�V����
void CJudge::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CJudge::Draw(void)
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
void CJudge::Uninit(void)
{
	CScene2D::Uninit();
}