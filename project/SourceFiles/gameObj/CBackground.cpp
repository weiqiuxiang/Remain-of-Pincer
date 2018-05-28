#include "CBackground.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CBackground::s_nPriority = 0;

CBackground::CBackground() : CScene2D(3)
{

}

CBackground::CBackground(int Priority) : CScene2D(Priority)
{
	
}

CBackground::~CBackground()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CBackground *CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CBackground *pBackground;
	pBackground = new CBackground(s_nPriority);
	pBackground->Init(pos, size);
	pBackground->LoadTexture(filePass);
	return pBackground;
}

//�v���[���[�̏�����
HRESULT CBackground::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_BACKGROUND);
	m_posU = 0.0f;
	m_posV = 0.0f;
	return S_OK;
}

//�X�V����
void CBackground::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CBackground::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CBackground::Uninit(void)
{
	CScene2D::Uninit();
}