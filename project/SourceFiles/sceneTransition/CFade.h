#pragma once
#ifndef _CFADE_H_
#define _CFADE_H_

#include "main.h"

class CFade
{
public:
	//メンバ関数
	CFade();
	CFade(const D3DXVECTOR3 &Pos, const D3DXVECTOR3 &pSize);
	~CFade();

	//Init,Update,Draw,Uninit関数
	HRESULT Init(const D3DXVECTOR3 &Pos, const D3DXVECTOR3 &pSize, const char *filePass);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	//セッター
	void SetLayerR(int Value);                     //REDレイヤーの値設定
	void SetLayerG(int Value);                     //GREENレイヤーの値設定
	void SetLayerB(int Value);                     //BLUEレイヤーの値設定
	void SetLayerA(int Value);                     //ALPHAレイヤーの値設定
	void SetRGBA(RGBA rgba);                       //RGBA一括設定
	void ChangeAlpha(int ChangeValue);             //ALPHAレイヤーの値を徐々変更させる
	void SetUV(const D3DXVECTOR2& UV) { m_UV = UV; }
	void SetUVWH(const D3DXVECTOR2& UVWH) { m_UVWH = UVWH; }
	void SetPosX(float PosX) { m_pos.x = PosX; }

	//ゲッター
	int GetLayerA(void) { return m_RGBA.a; }       //ALPHAレイヤーの値取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	//他の関数
	void AddPosX(float Pos) { m_pos.x += Pos; }
private:
	//メンバ関数
	void SetRenderStates(void);          //レンダーステート諸設定
	void VertexBufferLock(void);         //頂点ロック

	//メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR2             m_UV;           //UV原点
	D3DXVECTOR2             m_UVWH;         //UVの幅と高さ
	RGBA m_RGBA;
	TEX_ID *m_TexID;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
};

#endif