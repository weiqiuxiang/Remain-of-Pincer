#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);               //�f�o�C�X���擾����֐�

#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
	int						m_nCountFPS;			// FPS�J�E���^
#endif

private:
#ifdef _DEBUG
	void DrawFPS(void);
#endif
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif