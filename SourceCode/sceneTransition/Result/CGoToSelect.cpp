#include "CGoToSelect.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CGoToSelect::s_nPriority = 3;

CGoToSelect::CGoToSelect() : CScene2D(3)
{

}

CGoToSelect::CGoToSelect(int Priority) : CScene2D(Priority)
{
	
}

CGoToSelect::~CGoToSelect()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CGoToSelect *CGoToSelect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha)
{
	CGoToSelect *pGoToSelect;
	pGoToSelect = new CGoToSelect(s_nPriority);
	pGoToSelect->Init(pos, size, alpha);
	pGoToSelect->LoadTexture(filePass);
	return pGoToSelect;
}

//�v���[���[�̏�����
HRESULT CGoToSelect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_GOTOSELECT_BOTTON);
	m_nAlpha = alpha;
	return S_OK;
}

//�X�V����
void CGoToSelect::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CGoToSelect::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CGoToSelect::Uninit(void)
{
	CScene2D::Uninit();
}