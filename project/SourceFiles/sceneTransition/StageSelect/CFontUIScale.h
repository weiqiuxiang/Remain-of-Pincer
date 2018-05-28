#pragma once
#ifndef _CSCALE_UI_H_
#define _CSCALE_UI_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CFontUIScale : public CScene2D
{
public:
	CFontUIScale();
	CFontUIScale(int nPriority = 3);
	~CFontUIScale();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFontUIScale *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,const D3DXVECTOR3 &ScalePoint, int nAlpha , const char* filePass);          //CScene2Dのインスタンスを生成する関数

	//ゲッター
	bool GetMouseLock(void) { return m_bMouseLock; }
	static int GetPriority(void) { return s_nPriority; }

	//セッター
	void SetMouseLock(bool MouseLock) { m_bMouseLock = MouseLock; }
	void SetScale(float fScale) { m_Scale = max(0, fScale); }
	void SetOriginPos(const D3DXVECTOR3& pos) { m_OriginPos = pos; }
	void SetScalePoint(const D3DXVECTOR3 &ScalePoint) { m_ScalePoint = ScalePoint; }
private:
	//スケールのための変数
	D3DXVECTOR3 m_ScalePoint;                //スケール中心
	D3DXVECTOR3 m_OriginPos;                 //元の位置
	D3DXVECTOR3 m_OriginSize;                //元のサイズ
	float m_Scale;                          //スケール倍率

	bool m_bMouseLock;
	static int s_nPriority;
};

#endif