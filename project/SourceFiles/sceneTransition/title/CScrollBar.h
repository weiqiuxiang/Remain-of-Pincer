#pragma once
#ifndef _SCROLL_BAR_H_
#define _SCROLL_BAR_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CScrollBar : public CScene2D
{
public:
	CScrollBar();
	CScrollBar(int nPriority);
	~CScrollBar();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScrollBar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha , const char* filePass);          //CScene2Dのインスタンスを生成する関数

	//ゲッター
	bool GetMouseLock(void) { return m_bMouseLock; }
	static int GetPriority(void) { return s_nPriority; }

	//セッター
	void SetMouseLock(bool MouseLock) { m_bMouseLock = MouseLock; }
private:
	bool m_bMouseLock;
	static int s_nPriority;
};

#endif