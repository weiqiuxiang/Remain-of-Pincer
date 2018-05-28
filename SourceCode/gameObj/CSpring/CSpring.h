#pragma once
#ifndef _CSPRING_H_
#define _CSPRING_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CSpring : public CScene2D
{
public:
	CSpring();
	CSpring(int nPriority = 3);
	~CSpring();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSpring *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fElasticModulus,bool bFixDirection, const char* filePass);          //CScene2Dのインスタンスを生成する関数

	//セッター
	void SetElasticModulus(float fElasticModulus){
		if(fElasticModulus < 0.0f) m_fElasticModulus = 1.0f;
		m_fElasticModulus = fElasticModulus;
	}
	void SetFixDirection(bool bFixDirection) { m_bFixDirection = bFixDirection; }
	void SetReturnFlag(bool ReturnFlag) { m_ReturnSizeFlag = ReturnFlag; }

	//ゲッター
	static int GetPriority(void) { return s_nPriority; }
	D3DXVECTOR3 GetPosOrigin(void) {return m_posOrigin;}
	D3DXVECTOR3 GetSizeOrigin(void) { return m_sizeOrigin; }
	bool GetFixDirection(void) { return m_bFixDirection; }
	float GetElasticModulus(void) { return m_fElasticModulus; }

	//他の関数
	void ReturnAction(void);
private:
	float m_fElasticModulus;   //ばねの弾性係数
	D3DXVECTOR3 m_sizeOrigin; //元のサイズ
	D3DXVECTOR3 m_posOrigin;  //元の位置
	float m_PowerX;           //X方向の弾力
	bool m_bFixDirection;     //ばねの固定方向(false は左固定,trueは右固定)
	bool m_ReturnSizeFlag;    //プレーヤーとの当り判定がない場合徐々に元のサイズに戻る設定
	static int s_nPriority;
};

#endif