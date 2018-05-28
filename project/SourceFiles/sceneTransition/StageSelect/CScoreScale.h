#pragma once
#ifndef _SCORE_SCALE_H_
#define _SCORE_SCALE_H_

#include "main.h"
#include "scene2D.h"
#include "CNumberGame.h"

class CScoreScale : public CScene
{
public:
	CScoreScale();
	CScoreScale(int nPriority = 3);
	~CScoreScale();

	//定番関数
	HRESULT Init(const D3DXVECTOR3& pos/*位置*/,const D3DXVECTOR3& NumberSize/*一個数字のサイズ*/,int nDigit/*桁数*/,const char* TexPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ファクション関数
	static CScoreScale *Create(const D3DXVECTOR3& pos/*左上の位置*/, const D3DXVECTOR3& NumberSize/*一個数字のサイズ*/, const D3DXVECTOR3& ScalePoint,
		 int nDigit/*桁数*/, const char* TexPass);          //CScene2Dのインスタンスを生成する関数
	void AddScore(int nValue);                       //加算
	int GetScore(void);                              //スコアを取得
	void SetScorePos(void);                          //スコアの位置を設定
	static int GetPriority(void) { return s_nPriority; }

	//セッター
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetOriginPos(const D3DXVECTOR3& pos) { m_OriginPos = pos; }
	void SetPosToSetOrigin(const D3DXVECTOR3& pos) {
		m_pos = pos; 
		float CenterX = (m_pos.x + m_pos.x + (m_nDigit - 1)*m_OriginSize.x) * 0.5;
		float CenterY = (m_pos.y + m_pos.y + m_OriginSize.y) *0.5;
		m_OriginPos = D3DXVECTOR3(CenterX, CenterY, 0.0f);
	}
	void SetSize(const D3DXVECTOR3& size) {}
	void SetScore(int nScore) { m_nScore = max(0, nScore); }
	void SetScale(float fScale) { m_Scale = max(0, fScale); }
	void SetScalePoint(const D3DXVECTOR3& ScalePoint) { m_ScalePoint = ScalePoint; }

	//ゲッター
	D3DXVECTOR3 GetPos(void);                        //スコアの位置取得
	D3DXVECTOR3 GetSize(void);

private:
	void PowerReset(void);
	void AddPowerX(float fPowerX);
	void AddPowerY(float fPowerY);

	CNumberGame *m_apNumber;   //Numberポインタ
	D3DXVECTOR3 m_pos;         //位置
	D3DXVECTOR3 m_NumberSize;  //一個数字のサイズ
	float m_NumberDistance;    //数字の間の距離
	int m_nDigit;              //桁数
	int m_nScore;              //スコア

	//スケール変数
	D3DXVECTOR3 m_CenterPos;     //中心座標
	D3DXVECTOR3 m_OriginPos;     //元の原点(中心)
	D3DXVECTOR3 m_ScalePoint;    //スケール原点(スケール原点)
	D3DXVECTOR3 m_OriginSize;    //元のサイズ
	float m_Scale;

	static int s_nPriority;
};

#endif