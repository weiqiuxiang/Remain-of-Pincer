#pragma once
#ifndef _SCORE_GAME_H_
#define _SCORE_GAME_H_

#include "main.h"
#include "scene2D.h"
#include "CNumberGame.h"

class CScoreGame : public CScene
{
public:
	CScoreGame();
	CScoreGame(int nPriority = 3);
	~CScoreGame();

	//定番関数
	HRESULT Init(const D3DXVECTOR3& pos/*位置*/,const D3DXVECTOR3& NumberSize/*一個数字のサイズ*/,float NumberDistance/*数字の間の距離*/,int nDigit/*桁数*/,const char* TexPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ファクション関数
	static CScoreGame *Create(const D3DXVECTOR3& pos/*位置*/, const D3DXVECTOR3& NumberSize/*一個数字のサイズ*/, float NumberDistance/*数字の間の距離*/, int nDigit/*桁数*/, const char* TexPass);          //CScene2Dのインスタンスを生成する関数
	void AddScore(int nValue);                       //加算
	int GetScore(void);                              //スコアを取得
	void SetScorePos(void);                          //スコアの位置を設定
	static int GetPriority(void) { return s_nPriority; }

	//セッター
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) {}
	void SetScore(int nScore) { m_nScore = max(0, nScore); }

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
	static int s_nPriority;
};

#endif