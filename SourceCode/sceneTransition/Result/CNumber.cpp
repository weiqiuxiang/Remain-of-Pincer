#include "CNumber.h"
#include "SceneTransition.h"
#include "renderer.h"
#include "CScore.h"
#include "scene2D.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 CNumber::m_pTexture;
int CNumber::s_nPriority = 5;

CNumber::CNumber() : CScene2D(5)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nValue = 0;
}

CNumber::CNumber(int Priority) : CScene2D(Priority)
{
	
}

CNumber::~CNumber()
{

}

//
//��Ԋ֐�
////////////////////////////////////////////////
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();
	VERTEX_2D *pVtx = NULL;

	// �|���S���̈ʒu�Ȃǂ�ݒ�
	m_pos = pos;
	m_endPos = endPos;
	m_size = size;
	m_nAlpha = alpha;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	/***************************���z�A�h���X���擾���o�b�t�@�����b�N����************************************/
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���[�J�����W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	
	pVtx[0].tex = D3DXVECTOR2(m_nValue*0.1, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nValue*0.1 + 0.1, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nValue*0.1, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nValue*0.1 + 0.1, 1.0f);
	
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, alpha);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, alpha);

	m_pVtxBuff->Unlock();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_NUMBER);

	return S_OK;
}

void CNumber::Uninit(void)
{
	
}

void CNumber::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();
	VERTEX_2D *pVtx = NULL;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���[�J�����W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(m_nValue*0.1, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nValue*0.1 + 0.1, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nValue*0.1, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nValue*0.1 + 0.1, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);

	m_pVtxBuff->Unlock();
}

void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));                     //VRAM����GPU�Ƀf�[�^���X�g���[��

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);												 //�e�N�X�`���̐ݒ�

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);                                  //�`��
}

//
//�t�@�N�V�����֐�
////////////////////////////////////////////////
CNumber *CNumber::Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha)
{
	CNumber *pScore = new CNumber(s_nPriority);
	pScore->Init(pos, size, endPos, alpha);
	pScore->SetObjType(OBJTYPE_NUMBER);
	pScore->LoadTex();
	return  pScore;
}

HRESULT CNumber::LoadTex(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, SCORE_TEX, &m_pTexture)))
	{
		MessageBox(NULL, "�X�R�A�e�N�X�`���̓ǂݍ��݂����s���܂���", "�G���[", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	return S_OK;
}

void CNumber::UnloadTex(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CNumber::SetNumber(int nNumber)
{
	m_nValue = nNumber;
}
