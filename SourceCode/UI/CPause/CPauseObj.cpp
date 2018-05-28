#include "CPauseObj.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CPauseObj::s_nPriority = 6;

CPauseObj::CPauseObj() : CScene2D(8)
{

}

CPauseObj::CPauseObj(int nPriority) : CScene2D(nPriority)
{

}

CPauseObj::~CPauseObj()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CPauseObj *CPauseObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, bool bAlphaBlend,RGB rgb, const char* filePass)
{
	CPauseObj *pPlayerArrow;
	pPlayerArrow = new CPauseObj(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	pPlayerArrow->SetAlphaBlend(bAlphaBlend);
	pPlayerArrow->SetColor(rgb);
	pPlayerArrow->VertexLock();
	return pPlayerArrow;
}

//�v���[���[�̏�����
HRESULT CPauseObj::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_PAUSE);
	return S_OK;
}

//�X�V����
void CPauseObj::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CPauseObj::Draw(void)
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
void CPauseObj::Uninit(void)
{
	CScene2D::Uninit();
}