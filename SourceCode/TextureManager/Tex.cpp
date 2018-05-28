#define _CRT_SECURE_NO_WARNINGS
#include "Tex.h"
#include "SceneTransition.h"
#include "renderer.h"

//コンストラクタとデストラクタ
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
	if (m_pTexture != NULL) { m_pTexture->Release(); m_pTexture = NULL; }   //テクスチャポインタ解放
}

void TEX::SetTexPass(const char* filepass)
{
	strcpy(&m_pFilepass[0], filepass);     //ファイルパス記録
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
		MessageBox(NULL, "ファイルパスが読み込まれてない！テクスチャ生成失敗", "エラー", MB_OK | MB_ICONHAND);
		return;
	}

	//テクスチャロード
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_pFilepass, &m_pTexture)))
	{
		MessageBox(NULL, "テクスチャの読み込みが失敗しました", "エラー", MB_OK | MB_ICONHAND);
		return;
	}
}