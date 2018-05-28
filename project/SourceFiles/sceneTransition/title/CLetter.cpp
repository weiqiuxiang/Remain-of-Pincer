/*==============================================================================

CLetter�̏��� [CLetter.cpp]
�쐬�� : �����@�S��
�쐬�� : 
--------------------------------------------------------------------------------
��Update :
==============================================================================*/

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
 ------------------------------------------------------------------------------*/
#include "main.h"
#include "SceneTransition.h"
#include "CLetter.h"
#include "renderer.h"
#include "input.h"


 /*------------------------------------------------------------------------------
 �@�}�N��
  ------------------------------------------------------------------------------*/
#define TIRE_TEXTURENAME "data/TEXTURE/gang02.png"

/*------------------------------------------------------------------------------
  �@�ÓI�����o�ϐ��̏�����
------------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 CLetter::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLetter::CLetter(int Priority, D3DXVECTOR3 pos, D3DXVECTOR3 size) : CScene(Priority)
{
	m_pos = pos;
	m_size = size;

	// ���W�̏�����
	m_leftup = D3DXVECTOR2(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f);
	m_rightup = D3DXVECTOR2(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f);
	m_leftdown = D3DXVECTOR2(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f);
	m_rightdown = D3DXVECTOR2(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f);
	m_tex = D3DXVECTOR2(0.0f, 0.0f);
	m_texsize = D3DXVECTOR2(1.0f, 1.0f);
	m_rot = 0.0f;
	m_length = sqrt(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;			// �Ίp���̒����̎Z�o
	m_angle = atan2(m_size.y, m_size.x);											// �Ίp���̊p�x�̎Z�o
	m_pTexture = NULL;
	m_pushedL = false;
	m_pushedR = false;
	m_fall = false;

	// ������
	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLetter::~CLetter()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLetter::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̍쐬
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
		D3DUSAGE_WRITEONLY,		  			 // ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
		FVF_VERTEX_2D,						 	 // �H
		D3DPOOL_MANAGED,						 // ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
		&m_pVtxBuff,							 // ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X���i�[
		NULL)))								 // �g��Ȃ�
	{
		return E_FAIL;
	}

	// ���_�C���f�b�N�X�쐬
	pDevice->CreateIndexBuffer(sizeof(DWORD) * 6,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// ���_�̃������𒼂ŃR�s�[����
	DWORD *vIndex;
	m_pIdxBuff->Lock(0, 0, (void**)&vIndex, 0);

	// �����ŎO�p�`�����i�g���C�A���O�����X�g�j
	vIndex[0] = 0;
	vIndex[1] = 1;
	vIndex[2] = 2;
	vIndex[3] = 2;
	vIndex[4] = 1;
	vIndex[5] = 3;

	m_pIdxBuff->Unlock();

	// ���_�̐ݒ�
	SetVertex();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLetter::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		delete m_pVtxBuff;
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CLetter::Update(void)
{
	// ���W�̍X�V
	m_leftup.x = m_pos.x + cos(m_rot + D3DX_PI + m_angle) * m_length;		// ����̒��_X
	m_leftup.y = m_pos.y + sin(m_rot + D3DX_PI + m_angle) * m_length;		// ����̒��_Y		
	m_rightup.x = m_pos.x + cos(m_rot - m_angle) * m_length;		// �E��̒��_X
	m_rightup.y = m_pos.y + sin(m_rot - m_angle) * m_length;		// �E��̒��_Y
	m_leftdown.x = m_pos.x + cos(m_rot + D3DX_PI - m_angle) * m_length;		// �����̒��_X
	m_leftdown.y = m_pos.y + sin(m_rot + D3DX_PI - m_angle) * m_length;		// �����̒��_Y
	m_rightdown.x = m_pos.x + cos(m_rot + m_angle) * m_length;		// �E���̒��_X
	m_rightdown.y = m_pos.y + sin(m_rot + m_angle) * m_length;		// �E���̒��_Y

	SetVertex();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLetter::Draw(void)
{
	//CObject2D::Draw();	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();

	// �p�C�v���C���i�X�g���[���j��ݒ�
	pDevice->SetStreamSource(0,	// �p�C�v���C���ԍ�
		m_pVtxBuff,				// �p�C�v���C���̌��ɂȂ�̈���w��
		0,						// �I�t�Z�b�g�i�P�ʂ�byte�j���X�g���[���̊J�n�ʒu���w��ł���
		sizeof(VERTEX_2D));		// �����f�[�^�̒P�ʃT�C�Y�i�X�g���C�h�ʁj�C���f�b�N�X�̐ݒ�
								// �C���f�b�N�X�̐ݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// �e�N�X�`���̐ݒ�i�e�N�X�`���̃X�e�[�W�ւ̊����āj
	pDevice->SetTexture(0,		 // �X�e�[�W�� 
		CTexManager::UseTex(m_TEX_ID));			 //�e�N�X�`���C���^�[�t�F�[�X

								 // ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �v���~�e�B�u�i�|���S���j�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, // �v���~�e�B�u�̎��
		0,				   // �`��J�n�ʒu�̃I�t�Z�b�g�i���_���j
		0,				   // �ŏ��C���f�b�N�X�ԍ�
		6,				   // �ő�C���f�b�N�X�ԍ�
		0,				   // �C���f�b�N�X�z��̓ǂݎ��ʒu
		2);				   // �`�悷��v���~�e�B�u�̐�

}

void CLetter::SetVertex(void)
{
	VERTEX_2D* pVtx; // VRAM�̉��z�A�h���X���i�[

					 // ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	m_pVtxBuff->Lock(0,
		0,			   // ���ׂĂ����b�N
		(void**)&pVtx, // ���z�A�h���X�p�|�C���^�̃A�h���X��n��
		0);			   // ���b�N�t���O�H

					   // ���_���W�̐ݒ�( 2D���W�͉E���ɒ��_��p�ӂ��� )
	
	pVtx[0].pos = D3DXVECTOR3(m_leftup.x, m_leftup.y, 0.0f); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[1].pos = D3DXVECTOR3(m_rightup.x, m_rightup.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_leftdown.x, m_leftdown.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_rightdown.x, m_rightdown.y, 0.0f);

	// rhw�̐ݒ�i�K��1.0f�j����O�����i�o�b�t�@�j�̏��H
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
	pVtx[0].color = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].color = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].color = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].color = D3DXCOLOR(255, 255, 255, 255);

	// ���_�f�[�^��UV�f�[�^��ǉ�
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);
	pVtx[1].tex = D3DXVECTOR2(m_tex.x + m_texsize.x, m_tex.y);
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex.y + m_texsize.y);
	pVtx[3].tex = D3DXVECTOR2(m_tex.x + m_texsize.x, m_tex.y + m_texsize.y);	

	// ���_�o�b�t�@�̃��b�N������
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̃o�C���h
//=============================================================================
void CLetter::BindTexture(TEX_ID TexID)
{
	//��������������|�C���g
	m_TEX_ID = TexID;
}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CLetter::LoadTexture(const char* filePass)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	m_TEX_ID = CTexManager::LoadTex(filePass);

	return S_OK;
}

//=============================================================================
// �쐬
//=============================================================================
CLetter* CLetter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, float bottom, float rot, char* filePass)
{
	CLetter* pLetter = new CLetter(3, pos, size);
	pLetter->SetStartPos(pos);
	pLetter->SetRot(rot);
	pLetter->SetEndPos(D3DXVECTOR3(pos.x, bottom - size.y * 0.5f, 0.0f));
	pLetter->SetBottom(bottom);
	pLetter->LoadTexture(filePass);
	pLetter->SetEndRot((rand() % 628) * 0.01f);

	return pLetter;
}