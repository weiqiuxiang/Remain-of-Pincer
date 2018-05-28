#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene2D.h"

#define MAX_DIGIT (8)
#define SCORE_WIDTH (15.0f)
#define SCORE_HEIGHT (30.0f)
#define SCORE_DISTANCE (SCORE_WIDTH + 5.0f)

class CScene2D;
class CNumber;

class CScore : public CScene2D
{
public:
	CScore();
	CScore(int Priority);
	~CScore();

	//定番関数
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ファクション関数
	static CScore *Create(D3DXVECTOR3 pos);          //CScene2Dのインスタンスを生成する関数
	void AddScore(int nValue);                       //加算
	int GetScore(void);                              //スコアを取得
	void SetScorePos(void);                          //スコアの位置を設定
	void ChangePos(D3DXVECTOR3 value) { m_pos += value; }
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) {}
	D3DXVECTOR3 GetPos(void);
	static int GetPriority(void) { return s_nPriority; }
private:
	//ダミー                     //スコアの位置取得
	D3DXVECTOR3 GetSize(void);
	void PowerReset(void);
	void AddPowerX(float fPowerX);
	void AddPowerY(float fPowerY);

	CNumber *m_apNumber[MAX_DIGIT];
	D3DXVECTOR3 m_pos;
	int m_nScore;
	static int s_nPriority;
};

#endif