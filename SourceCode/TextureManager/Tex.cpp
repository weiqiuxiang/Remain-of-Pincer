#define _CRT_SECURE_NO_WARNINGS
#include "Tex.h"
#include "SceneTransition.h"
#include "renderer.h"

//�R���X�g���N�^�ƃf�X�g���N�^
TEX::TEX()
{
	m_pTexture = NULL;
	memset(&m_pFilepass[0], '\0', sizeof(&m_pFilepass[0]));
}

TEX::~TEX()
{
	if (m_pTexture != NULL) 
	{
		m_pTexture->Release(); 
		m_pTexture = NULL;
	}
}

HRESULT TEX::Init(void)
{
	if (m_pTexture != NULL) 
	{ 
		m_pTexture->Release(); 
		m_pTexture = NULL; 
	}

	m_pTexture = NULL;
	memset(&m_pFilepass[0], '\0', sizeof(&m_pFilepass[0]));

	return S_OK;
}

void TEX::Uninit(void)
{
	if (m_pTexture != NULL) { m_pTexture->Release(); m_pTexture = NULL; }   //�e�N�X�`���|�C���^���
}

void TEX::SetTexPass(const char* filepass)
{
	strcpy(&m_pFilepass[0], filepass);     //�t�@�C���p�X�L�^
}

const char *TEX::GetTexPass(void)
{
	return m_pFilepass;
}

const LPDIRECT3DTEXTURE9 TEX::GetTexturePoint(void)
{
	return m_pTexture;
}

void TEX::CreateTexObj(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();

	if(m_pFilepass[0] == '\0')
	{
		MessageBox(NULL, "�t�@�C���p�X���ǂݍ��܂�ĂȂ��I�e�N�X�`���������s", "�G���[", MB_OK | MB_ICONHAND);
		return;
	}

	//�e�N�X�`�����[�h
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_pFilepass, &m_pTexture)))
	{
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂����s���܂���", "�G���[", MB_OK | MB_ICONHAND);
		return;
	}
}