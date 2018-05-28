#include "CWormHole.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CWormHole::s_nPriority = 4;

CWormHole::CWormHole() : CScene2D(4)
{

}

CWormHole::CWormHole(int nPriority) : CScene2D(nPriority)
{

}

CWormHole::~CWormHole()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CWormHole *CWormHole::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const RGB& rgb, bool bAlphaBlend, const char* filePass)
{
	CWormHole *pPlayerSelecter;
	pPlayerSelecter = new CWormHole(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	pPlayerSelecter->SetAlpha(nAlpha);
	pPlayerSelecter->SetColor(rgb);
	pPlayerSelecter->SetAlphaBlend(bAlphaBlend);
	pPlayerSelecter->SetWarpFlag(false);
	pPlayerSelecter->VertexLock();
	return pPlayerSelecter;
}

//�v���[���[�̏�����
HRESULT CWormHole::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_WORM_HOLE);
	return S_OK;
}

//�X�V����
void CWormHole::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CWormHole::Draw(void)
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
void CWormHole::Uninit(void)
{
	CScene2D::Uninit();
}