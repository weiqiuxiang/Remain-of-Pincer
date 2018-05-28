#include "CNextBotton.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CNextBotton::s_nPriority = 3;

CNextBotton::CNextBotton() : CScene2D(3)
{

}

CNextBotton::CNextBotton(int Priority) : CScene2D(Priority)
{
	
}

CNextBotton::~CNextBotton()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CNextBotton *CNextBotton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha)
{
	CNextBotton *pNextBotton;
	pNextBotton = new CNextBotton(s_nPriority);
	pNextBotton->Init(pos, size, alpha);
	pNextBotton->LoadTexture(filePass);
	return pNextBotton;
}

//�v���[���[�̏�����
HRESULT CNextBotton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_NEXT_BOTTON);
	m_nAlpha = alpha;
	return S_OK;
}

//�X�V����
void CNextBotton::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CNextBotton::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CNextBotton::Uninit(void)
{
	CScene2D::Uninit();
}