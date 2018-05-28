#pragma once

#ifndef _CEXPLOSION_H_
#define _CEXPLOSION_H_

#include "main.h"
#include "scene2D.h"
#include "TexManager.h"

//前方宣言
class CScene2D;

class CExplosion :public CScene2D
{
public:
	CExplosion();
	CExplosion(int nPriority = 3);
	~CExplosion();
	static HRESULT Load(const char* filePass);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
private:
	static TEX_ID m_TEX_ID;                    //弾の共通テクスチャポイント(弾ごとのm_pTextureにアドレスに渡すために)
	int m_nframe;
	static int s_nPriority;
};

#endif