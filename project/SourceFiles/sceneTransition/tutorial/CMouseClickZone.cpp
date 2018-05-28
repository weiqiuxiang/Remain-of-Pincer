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

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CMouseClickZone *CMouseClickZone::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const char* filePass)
{
	CMouseClickZone *pPlayerArrow;
	pPlayerArrow = new CMouseClickZone(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	return pPlayerArrow;
}

//�v���[���[�̏�����
HRESULT CMouseClickZone::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TUTORIAL_MOUSECLICKZONE);
	m_bMouseLock = true;
	return S_OK;
}

//�X�V����
void CMouseClickZone::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CMouseClickZone::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	//���Z�����ݒ�
	// �A���t�@�E�u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	// �`��G�|���S���̓��œ������ɂȂ��Ă���
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	// ��̊G�͓��������Ȃ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//�u�����h���[�h���A���t�@�u�����h�ɖ߂�
	// ��̊G�̓��l�ŕs�����Ȃ��Ă���
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �`��G�̓��l�œ����Ȃ��Ă���
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

//�I������
void CMouseClickZone::Uninit(void)
{
	CScene2D::Uninit();
}