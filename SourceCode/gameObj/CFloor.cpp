#include "CFloor.h"
#include "SceneTransition.h"
#include "input.h"
#include "inputmouse.h"
#include "CBullet.h"

#define DEAD_TIME (30)

//�O���錾
class CSceneTransition;

int CFloor::s_nPriority = 1;

CFloor::CFloor() : CScene2D(3)
{
	
}

CFloor::CFloor(int nPriority) : CScene2D(nPriority)
{
	
}

CFloor::~CFloor()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CFloor *CFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BLOCK_TYPE FloorType, const char* filePass)
{
	CFloor *pFloor;
	pFloor = new CFloor(s_nPriority);
	pFloor->Init(pos, size);
	pFloor->LoadTexture(filePass);
	pFloor->SetBlockType(FloorType);
	if(FloorType == TYPE_NORMAL)
	{
		pFloor->SetUV(D3DXVECTOR2( 0.0f,0.0f ));
		pFloor->SetUVWH(D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		pFloor->SetUV(D3DXVECTOR2(0.0f, 0.0f));
		pFloor->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
	}
	pFloor->VertexLock();
	return pFloor;
}

//�v���[���[�̏�����
HRESULT CFloor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size);
	CScene2D::SetObjType(OBJTYPE_FLOOR);
	m_FlagAlreadyHit = false;
	m_nCntDead = DEAD_TIME;
	return S_OK;
}

//�X�V����
void CFloor::Update(void)
{
	//UVChange
	if (m_FloorType == TYPE_BREAK)
	{
		float fPercent = (float)m_nCntDead / DEAD_TIME;
		if ((fPercent >= 0.50) && (fPercent < 0.75))
		{
			m_UV = D3DXVECTOR2(0.25f, 0.0f);
			m_UVWH = D3DXVECTOR2(0.25f, 1.0f);
		}
		else if ((fPercent >= 0.25) && (fPercent < 0.50))
		{
			m_UV = D3DXVECTOR2(0.5f, 0.0f);
			m_UVWH = D3DXVECTOR2(0.25f, 1.0f);
		}

		else if(fPercent < 0.25f)
		{
			m_UV = D3DXVECTOR2(0.75f, 0.0f);
			m_UVWH = D3DXVECTOR2(0.25f, 1.0f);
		}
	}

	CScene2D::VertexLock();                     //���_���b�N

	if(m_FlagAlreadyHit == true)
	{
		m_nCntDead--;
		if(m_nCntDead < 0)
		{
			Uninit();
			return;
		}
	}
}

//�`�揈��
void CFloor::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CFloor::Uninit(void)
{
	CScene2D::Uninit();
}