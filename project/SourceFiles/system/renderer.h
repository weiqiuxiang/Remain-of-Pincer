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
	LPDIRECT3DDEVICE9 GetDevice(void);               //デバイスを取得する関数

#ifdef _DEBUG
	LPD3DXFONT				m_pFont;			// フォントへのポインタ
	int						m_nCountFPS;			// FPSカウンタ
#endif

private:
#ifdef _DEBUG
	void DrawFPS(void);
#endif
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif