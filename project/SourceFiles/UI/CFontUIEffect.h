#pragma once
#ifndef _CTUTORIAL_UI_EFFECT_H_
#define _CTUTORIAL_UI_EFFECT_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CFontUIEffect : public CScene2D
{
public:
	CFontUIEffect();
	CFontUIEffect(int nPriority = 3);
	~CFontUIEffect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFontUIEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nAlpha ,const RGB& rgb,bool bAlphaBlend, const char* filePass);          //CScene2Dのインスタンスを生成する関数

	//ゲッター
	bool GetMouseLock(void) { return m_bMouseLock; }
	static int GetPriority(void) { return s_nPriority; }

	//セッター
	void SetMouseLock(bool MouseLock) { m_bMouseLock = MouseLock; }
	void SetAlphaBlend(bool AlphaBlend) { m_bAlphaBlend = AlphaBlend; }
private:
	bool m_bMouseLock;
	bool m_bAlphaBlend;
	static int s_nPriority;
};

#endif