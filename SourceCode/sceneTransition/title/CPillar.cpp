#include "CPillar.h"
#include "CNumber.h"
#include "CResult.h"
#include "CResultScore.h"
#include "SceneTransition.h"

int CPillar::s_nPriority = 3;

CPillar::CPillar() : CScene2D(3)
{
}

CPillar::CPillar(int Priority) : CScene2D(Priority)
{

}

CPillar::~CPillar()
{

}

//�e�L�X�g�{�b�N�X�̃C���X�^���X�𐶐�����֐�
CPillar* CPillar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, const char* filePass)
{
	CPillar *pPillar;
	pPillar = new CPillar(s_nPriority);
	pPillar->SetPos(pos);
	pPillar->SetSize(size);
	pPillar->SetStartPos(pos);
	pPillar->SetEndPos(endPos);
	pPillar->SetVelocity((endPos - pos) * 0.05f);
	pPillar->SetAlpha(255);
	pPillar->Init();
	pPillar->LoadTexture(filePass);
	return pPillar;
}

//�e�L�X�g�{�b�N�X�̏�����
HRESULT CPillar::Init(void)
{
	CScene2D::Init(m_pos, m_size);
	CScene2D::SetObjType(OBJTYPE_NONE);
	m_posU = 0.0f;
	m_posV = 0.0f;
			
	CScene2D::VertexLock();

	return S_OK;
}

//�X�V����
void CPillar::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CPillar::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CPillar::Uninit(void)
{
	CScene2D::Uninit();
}