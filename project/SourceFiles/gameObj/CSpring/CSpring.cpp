#include "CSpring.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CSpring::s_nPriority = 3;

CSpring::CSpring() : CScene2D (3)
{

}

CSpring::CSpring(int nPriority) : CScene2D(nPriority)
{

}

CSpring::~CSpring()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CSpring *CSpring::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fElasticModulus , bool bFixDirection, const char* filePass)
{
	CSpring *pSpring;
	pSpring = new CSpring(s_nPriority);
	pSpring->Init(pos, size);
	pSpring->LoadTexture(filePass);
	pSpring->SetElasticModulus(fElasticModulus);
	pSpring->SetFixDirection(bFixDirection);
	return pSpring;
}

//�v���[���[�̏�����
HRESULT CSpring::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_SPRING);
	m_sizeOrigin = m_size;                   //���̃T�C�Y��ۑ�
	m_posOrigin = m_pos;                   //���̈ʒu�ۑ�
	m_PowerX = 0;
	m_ReturnSizeFlag = false;
	return S_OK;
}

//�X�V����
void CSpring::Update(void)
{
	ReturnAction();           //���̃T�C�Y�ɖ߂�A�N�V����
	CScene2D::VertexLock();
}

//�`�揈��
void CSpring::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CSpring::Uninit(void)
{
	CScene2D::Uninit();
}

void CSpring::ReturnAction(void)
{
	if (m_ReturnSizeFlag == false) return;
	if (m_sizeOrigin.x == m_size.x) return;

	//���Œ�
	m_size.x += 10;
	if (m_size.x > m_sizeOrigin.x)
	{
		m_size.x = m_sizeOrigin.x;
		m_ReturnSizeFlag = false;
	}
	if(m_bFixDirection == false)
	{
		m_size.x += 4;
		float Left = m_posOrigin.x - m_sizeOrigin.x*0.5;
		m_pos.x = Left + m_size.x*0.5;
	}
	//�E�Œ�
	else
	{
		m_size.x += 4;
		float Right = m_posOrigin.x + m_sizeOrigin.x*0.5;
		m_pos.x = Right - m_size.x*0.5;
	}
}