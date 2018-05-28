#pragma once

#ifndef _CFLOOR_H_
#define _CFLOOR_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CFloor :public CScene2D
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_BREAK
	}BLOCK_TYPE;

	CFloor();
	CFloor(int nPriority = 3);
	~CFloor();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFloor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size , BLOCK_TYPE FloorType, const char* filePass);          //CScene2Dのインスタンスを生成する関数

	//セッター
	void SetBlockType(BLOCK_TYPE type) { m_FloorType = type; }
	void SetAlreadyHit(bool AlreadyHit) { m_FlagAlreadyHit = AlreadyHit; }

	//ゲッター
	BLOCK_TYPE GetBlockType(void) { return m_FloorType; }
	bool GetAlreadyHit(void) { return m_FlagAlreadyHit; }
	static int GetPriority(void) { return s_nPriority; }
private:
	BLOCK_TYPE m_FloorType;
	bool m_FlagAlreadyHit;
	int m_nCntDead;
	static int s_nPriority;
};

#endif