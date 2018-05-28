#pragma once
#ifndef _RETRY_BOTTON_H_
#define _RETRY_BOTTON_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CRetryBotton : public CScene2D
{
public:
	CRetryBotton();
	CRetryBotton(int Priority);
	~CRetryBotton();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int alpha);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRetryBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass, int alpha);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif