#pragma once
#ifndef _CBACKGROUND_H_
#define _CBACKGROUND_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CBackground : public CScene2D
{
public:
	CBackground();
	CBackground(int Priority);
	~CBackground();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBackground *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
private:
	float m_posU;
	float m_posV;
	static int s_nPriority;
};

#endif