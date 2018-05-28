#pragma once
#ifndef _CNUMBER_GAME_H_
#define _CNUMBER_GAME_H_

#include "main.h"

class CNumberGame
{
public:
	CNumberGame();
	~CNumberGame();

	HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const char* TexPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumberGame *Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& size,const char* TexPass,int Number);
	void SetNumber(int nNumber);
	void SetPos(const D3DXVECTOR3 *pos);
	void SetSize(const D3DXVECTOR3 *size) { m_size = *size; }
private:
	TEX_ID m_TexID;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	int m_nValue;
};

#endif