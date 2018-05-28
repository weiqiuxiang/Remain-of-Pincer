#pragma once

#ifndef _CBULLET_H_
#define _CBULLET_H_

#include "main.h"
#include "scene2D.h"

//前方宣言
class CScene2D;

class CBullet:public CScene2D
{
public:
	CBullet();
	~CBullet();
	static HRESULT Load(int TexType);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 speed);          //CScene2Dのインスタンスを生成する関数
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;                    //弾の共通テクスチャポイント(弾ごとのm_pTextureにアドレスに渡すために)
	D3DXVECTOR3 m_move;                                      //移動量
};

#endif