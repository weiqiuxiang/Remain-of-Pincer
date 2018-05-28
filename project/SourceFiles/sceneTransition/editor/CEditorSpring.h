#pragma once
#ifndef _CEDITOR_SPRING_H_
#define _CEDITOR_SPRING_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CEditorSpring : public CScene2D
{
public:
	CEditorSpring();
	CEditorSpring(int nPriority = 3);
	~CEditorSpring();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEditorSpring *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2Dのインスタンスを生成する関数
	static int GetPriority(void) { return s_nPriority; }
private:
	static int s_nPriority;
};

#endif