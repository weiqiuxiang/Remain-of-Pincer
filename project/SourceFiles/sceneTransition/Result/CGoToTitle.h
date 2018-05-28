#pragma once
#ifndef _GO_TO_TITLE_H_
#define _GO_TO_TITLE_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CGoToTitle : public CScene2D
{
public:
	CGoToTitle();
	CGoToTitle(int Priority);
	~CGoToTitle();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGoToTitle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif