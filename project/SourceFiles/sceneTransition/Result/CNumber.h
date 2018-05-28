#pragma once
#ifndef _CNUMBER_H_
#define _CNUMBER_H_

#include "main.h"
#include "scene2D.h"

class CNumber : public CScene2D
{
public:
	typedef enum
	{
		NUMTYPE_USEPAIR = 0,
		NUMTYPE_MAXKILL,
		NUMTYPE_SCORE,
		NUMTYPE_MAX
	}NUMTYPE;

	CNumber();
	CNumber(int Priority = 3);
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//セッター
	void SetNumber(int nNumber);
	void SetPosX(const float posx) { m_pos.x = posx; }
	void SetNumType(NUMTYPE type) { m_type = type; }

	//ゲッター
	NUMTYPE GetNumType(void) { return m_type; }
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	static int GetPriority(void) { return s_nPriority; }

	//他の関数
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha);
	static HRESULT LoadTex(void);
	static void UnloadTex(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	int m_nValue;
	D3DXVECTOR3 m_endPos;       //ゴール座標
	NUMTYPE m_type;
	static int s_nPriority;
};

#endif