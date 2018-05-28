#pragma once
#ifndef _NEXT_BOTTON_H_
#define _NEXT_BOTTON_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CNextBotton : public CScene2D
{
public:
	CNextBotton();
	CNextBotton(int Priority);
	~CNextBotton();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNextBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif