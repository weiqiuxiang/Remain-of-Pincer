#include "TexManager.h"

//�}�N��
#define TEXTURE_IS_NULL (-1)

//�O���[�o��
TEX *CTexManager::m_TexTureSlot[TEXSLOT_NUM] = {};

//���ׂẴe�N�X�`���X���b�g������
HRESULT CTexManager::InitAll(void)
{
	for (int nCnt = 0; nCnt < TEXSLOT_NUM; nCnt++)
	{
		if (m_TexTureSlot[nCnt] != NULL)
		{
			m_TexTureSlot[nCnt]->Uninit();
			delete m_TexTureSlot[nCnt];
			m_TexTureSlot[nCnt] = NULL;
		}

		m_TexTureSlot[nCnt] = NULL;
	}

	return S_OK;
}

//���ׂẴe�N�X�`���X���b�g���
void CTexManager::UninitAll(void)
{
	for (int nCnt = 0; nCnt < TEXSLOT_NUM; nCnt++)
	{
		if (m_TexTureSlot[nCnt] != NULL)
		{
			m_TexTureSlot[nCnt]->Uninit();
			delete m_TexTureSlot[nCnt];
			m_TexTureSlot[nCnt] = NULL;
		}
	}
}

//�e�N�X�`�������[�h��ID��Ԃ�
TEX_ID CTexManager::LoadTex(const char *FilePass)
{
	if (FilePass == NULL) return TEXTURE_IS_NULL;
	for (TEX_ID IDNum = 0; IDNum < TEXSLOT_NUM; IDNum++)
	{
		if (m_TexTureSlot[IDNum] != NULL)//�X���b�g���łɎg�p�����ꍇ
		{
			const char *SlotFilePass = m_TexTureSlot[IDNum]->GetTexPass();   //�t�@�C���p�X�擾
			int ValueStrcmp = strcmp(SlotFilePass, FilePass);
			if (ValueStrcmp == 0) return IDNum;
			else continue;
		}

		if (m_TexTureSlot[IDNum] == NULL)//�X���b�g�󂪂�������e�N�X�`��������
		{
			CreateTexObj(IDNum, FilePass);
			return IDNum;
		}
	}

	//��O����
	MessageBox(NULL, "�g�p�ł���e�N�X�`���X���b�g���Ȃ�", "�G���[", MB_OK | MB_ICONHAND);
	return TEXTURE_IS_NULL;
}

//�e�N�X�`���ԍ���n��,�e�N�X�`���|�C���^��Ԃ�
LPDIRECT3DTEXTURE9 CTexManager::UseTex(TEX_ID IDNum)
{
	if (IDNum == TEXTURE_IS_NULL) return NULL;
	if (m_TexTureSlot[IDNum] == NULL) return NULL;
	return m_TexTureSlot[IDNum]->GetTexturePoint();
}

//�e�N�X�`���X���b�g�Ƀe�N�X�`��������
HRESULT CTexManager::CreateTexObj(TEX_ID IDNum, const char *FilePass)
{
	if (m_TexTureSlot[IDNum] != NULL)
	{
		MessageBox(NULL, "���̃e�N�X�`���X���b�g�����łɎg�p����Ă���", "�G���[", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}
	m_TexTureSlot[IDNum] = new TEX;//���̉�
	m_TexTureSlot[IDNum]->SetTexPass(FilePass);//�t�@�C���p�X���Z�b�g
	m_TexTureSlot[IDNum]->CreateTexObj();//�e�N�X�`���I�u�W�F�N�g����

	return S_OK;
}