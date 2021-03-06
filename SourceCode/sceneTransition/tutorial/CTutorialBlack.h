#pragma once
#ifndef _CTUTORIAL_BLACK_H_
#define _CTUTORIAL_BLACK_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CTutorialBlack : public CScene2D
{
public:
	CTutorialBlack();
	CTutorialBlack(int nPriority = 3);
	~CTutorialBlack();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorialBlack *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha , const char* filePass);          //CScene2Dのインスタンスを生成する関数

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