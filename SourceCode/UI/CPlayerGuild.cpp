#include "CPlayerGuild.h"
#include "SceneTransition.h"
#include "hitCheck.h"

#define SCROLL_SPEED (0.005f)

int CPlayerGuild::s_nPriority = 3;

CPlayerGuild::CPlayerGuild() : CScene2D(3)
{

}

CPlayerGuild::CPlayerGuild(int nPriority) : CScene2D(nPriority)
{

}

CPlayerGuild::~CPlayerGuild()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CPlayerGuild *CPlayerGuild::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Alpha, const char* filePass)
{
	CPlayerGuild *pPlayerArrow;
	pPlayerArrow = new CPlayerGuild(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(Alpha);
	return pPlayerArrow;
}

//�v���[���[�̏�����
HRESULT CPlayerGuild::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_PLAYER_GUILD);
	m_bMouseLock = true;
	return S_OK;
}

//�X�V����
void CPlayerGuild::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CPlayerGuild::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CPlayerGuild::Uninit(void)
{
	CScene2D::Uninit();
}