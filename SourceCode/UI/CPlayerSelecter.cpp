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

//�v���[���[�̃C���X�^���X�𐶐�����֐�
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

//�v���[���[�̏�����
HRESULT CPlayerSelecter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_PLAYER_SELECTER);
	m_Scale = 1.0f;
	m_OriginSize = size;
	return S_OK;
}

//�X�V����
void CPlayerSelecter::Update(void)
{
	m_size = m_OriginSize * m_Scale;        //�X�P�[����̃T�C�Y
	CScene2D::VertexLock();
}

//�`�揈��
void CPlayerSelecter::Draw(void)
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
void CPlayerSelecter::Uninit(void)
{
	CScene2D::Uninit();
}