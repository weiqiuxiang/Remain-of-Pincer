#include "CGoToTitle.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CGoToTitle::s_nPriority = 3;

CGoToTitle::CGoToTitle() : CScene2D(3)
{

}

CGoToTitle::CGoToTitle(int Priority) : CScene2D(Priority)
{
	
}

CGoToTitle::~CGoToTitle()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CGoToTitle *CGoToTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha)
{
	CGoToTitle *pGoToTitleBotton;
	pGoToTitleBotton = new CGoToTitle(s_nPriority);
	pGoToTitleBotton->Init(pos, size, alpha);
	pGoToTitleBotton->LoadTexture(filePass);
	return pGoToTitleBotton;
}

//�v���[���[�̏�����
HRESULT CGoToTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_GOTOTITLE_BOTTON);
	m_nAlpha = alpha;
	return S_OK;
}

//�X�V����
void CGoToTitle::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CGoToTitle::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CGoToTitle::Uninit(void)
{
	CScene2D::Uninit();
}