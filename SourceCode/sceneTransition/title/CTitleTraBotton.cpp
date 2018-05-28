#include "CTitleTraBotton.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CTitleTraBotton::s_nPriority = 5;

CTitleTraBotton::CTitleTraBotton() : CScene2D(3)
{

}

CTitleTraBotton::CTitleTraBotton(int nPriority) : CScene2D(nPriority)
{
	
}

CTitleTraBotton::~CTitleTraBotton()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CTitleTraBotton *CTitleTraBotton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TRA_TYPE TraType,const char* filePass)
{
	CTitleTraBotton *pPlayerSelecter;
	pPlayerSelecter = new CTitleTraBotton(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	pPlayerSelecter->m_TraType = TraType;
	return pPlayerSelecter;
}

CTitleTraBotton *CTitleTraBotton:: Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStageNum, const char* filePass)
{
	CTitleTraBotton *pPlayerSelecter;
	pPlayerSelecter = new CTitleTraBotton(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	nStageNum = max(1, nStageNum);
	pPlayerSelecter->SetStageNum(nStageNum);
	pPlayerSelecter->m_TraType = TYPE_STAGE_NUM;
	return pPlayerSelecter;
}

//�v���[���[�̏�����
HRESULT CTitleTraBotton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TITLE_TRA_OBJ);
	m_sizeOrigin = m_size;                      //���̃T�C�Y�ۑ�
	return S_OK;
}

//�X�V����
void CTitleTraBotton::Update(void)
{
	CScene2D::VertexLock();
}

//�`�揈��
void CTitleTraBotton::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CTitleTraBotton::Uninit(void)
{
	CScene2D::Uninit();
}