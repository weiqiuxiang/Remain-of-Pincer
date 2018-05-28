#include "CPlayerArrow.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CPlayerArrow::s_nPriority = 4;

CPlayerArrow::CPlayerArrow() : CScene2D(3)
{

}

CPlayerArrow::CPlayerArrow(int nPriority) : CScene2D(nPriority)
{
	
}

CPlayerArrow::~CPlayerArrow()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CPlayerArrow *CPlayerArrow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CPlayerArrow *pPlayerArrow;
	pPlayerArrow = new CPlayerArrow(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	return pPlayerArrow;
}

//�v���[���[�̏�����
HRESULT CPlayerArrow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_PLAYER_ARROW);
	m_bMouseLock = true;
	return S_OK;
}

//�X�V����
void CPlayerArrow::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CPlayerArrow::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CPlayerArrow::Uninit(void)
{
	CScene2D::Uninit();
}