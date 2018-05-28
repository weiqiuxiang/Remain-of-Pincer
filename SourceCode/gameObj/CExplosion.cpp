#include "CExplosion.h"
#include "SceneTransition.h"
#include "renderer.h"

//�O���錾
class CSceneTransition;

int CExplosion::s_nPriority = 4;

//�O���o�[���錾
TEX_ID CExplosion::m_TEX_ID = -1;

CExplosion::CExplosion() : CScene2D(3)
{

}

CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
{
	
}

CExplosion::~CExplosion()
{

}

//�v���[���[�̃C���X�^���X�𐶐�����֐�
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion(s_nPriority);
	pExplosion->Init(pos,size);
	pExplosion->BindTexture(m_TEX_ID);                        //�e�N�X�`�������蓖�Ă�
	return pExplosion;
}

//�v���[���[�̏�����
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_EXPLOSION);
	m_nframe = 0;
	return S_OK;
}

//�X�V����
void CExplosion::Update(void)
{
	VERTEX_2D *pVtx = NULL;
	float i, j;
	i = (m_nframe % 3)*0.3333;
	j = (m_nframe / 3)*0.14285;

	D3DXVECTOR3 HalfSize = m_size * 0.5;

	if (m_pVtxBuff != NULL)
	{

		/***************************���z�A�h���X���擾���o�b�t�@�����b�N����************************************/
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���[�J�����W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - HalfSize.x, m_pos.y - HalfSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + HalfSize.x, m_pos.y - HalfSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - HalfSize.x, m_pos.y + HalfSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + HalfSize.x, m_pos.y + HalfSize.y, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(i, j);
		pVtx[1].tex = D3DXVECTOR2(i + 0.3333, j);
		pVtx[2].tex = D3DXVECTOR2(i, j + 0.14285);
		pVtx[3].tex = D3DXVECTOR2(i + 0.3333, j + 0.14285);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

		m_pVtxBuff->Unlock();
	}

	else
	{
		return;
	}

	m_nframe++;
	if(m_nframe > 21)                             //�����A�j���I��
	{
		Uninit();
	}
}

//�`�揈��
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//�I������
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//�e�N�X�`���̓ǂ݂���
HRESULT CExplosion::Load(const char* filePass)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	m_TEX_ID = CTexManager::LoadTex(filePass);

	return S_OK;
}

//�e�N�X�`���̔j��
void CExplosion::Unload(void)
{
	
}