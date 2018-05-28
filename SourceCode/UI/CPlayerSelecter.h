#pragma once
#ifndef _CPLAYER_SELECTER_H_
#define _CPLAYER_SELECTER_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CPlayerSelecter : public CScene2D
{
public:
	CPlayerSelecter();
	CPlayerSelecter(int nPriority = 3);
	~CPlayerSelecter();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerSelecter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha, const RGB& rgb, bool bAlphaBlend , const char* filePass);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }

	//セッター
	void SetScale(float fScale) { m_Scale = max(0.1f,fScale); }
	void SetAlphaBlend(bool AlphaBlend) { m_bAlphaBlend = AlphaBlend; }
private:
	bool m_bAlphaBlend;
	static int s_nPriority;
	D3DXVECTOR3 m_OriginSize;                     //元のサイズ
	float m_Scale;
};

#endif