#pragma once

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "TexManager.h"

//前方宣言
class CScene;

typedef struct
{
	float powerLeft;
	float powerRight;
}BETWEEN_POWTER;

class CScene2D : public CScene
{
public:
	CScene2D();
	CScene2D(int nPriority = 3);
	~CScene2D();

	//Init,Uninit,Update,Draw関数
	HRESULT Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ゲッター
	D3DXVECTOR3 GetPos(void);                    //位置取得
	D3DXVECTOR3 GetSize(void);
	int GetAlpha(void) { return m_nAlpha; }

	//セッター
	void SetUV(const D3DXVECTOR2& UV) { m_UV = UV; }
	void SetUVWH(const D3DXVECTOR2& UVWH) { m_UVWH = UVWH; }
	void SetPos(const D3DXVECTOR3& pos) {m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetAlpha(int nValue);
	void SetColor(const RGB &Color);            //色設定
	void SetColor(const RGBA &Color);           //色設定
	void ChangePos(const D3DXVECTOR3& PosValue) { m_pos += PosValue; }
	void AddPowerX(float fPowerX);
	void AddPowerY(float fPowerY);
	void PowerReset(void);                       //受ける力をリセット
	void ChangeAlpha(int ChangeValue);             //ALPHAレイヤーの値を徐々変更させる
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass);          //CScene2Dのインスタンスを生成する関数
	void BindTexture(TEX_ID TexID);                                        //外のテクスチャを読み込む
	HRESULT LoadTexture(const char* filePass);                                                //対応読み込みテクスチャ番
	static int GetPriority(void) { return s_nPriority; }
private:
	TEX_ID		m_TEX_ID;		// テクスチャへのポインタ
	static int s_nPriority;
protected:
	void VertexLock(void);                  //頂点ロック

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴンのサイズ
	BETWEEN_POWTER			m_powerBetween;	// オブジェが受けた挟む力
	D3DXVECTOR2             m_UV;           //UV原点
	D3DXVECTOR2             m_UVWH;         //UVの幅と高さ
	float                   m_mass;         // 質量
	int                     m_nAlpha;        //アルファ値
	RGB                     m_Color;        //色
	bool m_bLoadTexture;                    //テクスチャ読み込まれたかのフラグ
};

#endif