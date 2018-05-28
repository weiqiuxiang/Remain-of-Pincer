#include "CFontUIScale.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CFontUIScale::s_nPriority = 5;

CFontUIScale::CFontUIScale() : CScene2D(3)
{

}

CFontUIScale::CFontUIScale(int nPriority) : CScene2D(nPriority)
{

}

CFontUIScale::~CFontUIScale()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CFontUIScale *CFontUIScale::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXVECTOR3 &ScalePoint,int nAlpha, const char* filePass)
{
	CFontUIScale *pPlayerArrow;
	pPlayerArrow = new CFontUIScale(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	pPlayerArrow->SetScalePoint(ScalePoint);
	return pPlayerArrow;
}

//�v���[���[�̏�����
HRESULT CFontUIScale::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_NONE);
	m_bMouseLock = true;

	//�X�P�[���֌W
	m_OriginPos = pos;
	m_OriginSize = size;
	m_Scale = 1.0f;

	return S_OK;
}

//�X�V����
void CFontUIScale::Update(void)
{
	D3DXVECTOR3 DistanceFromSP = m_OriginPos - m_ScalePoint;   //�����_�ƃX�P�[�����S�̍���
	DistanceFromSP = DistanceFromSP * m_Scale;      //�X�P�[���̌�̍����T�C�Y
	m_pos = m_ScalePoint + DistanceFromSP;    //�X�P�[��Center���W�����߂�
	m_size = m_OriginSize * m_Scale;      //�X�P�[����̃T�C�Y

	CScene2D::VertexLock();
}

//�`�揈��
void CFontUIScale::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CFontUIScale::Uninit(void)
{
	CScene2D::Uninit();
}