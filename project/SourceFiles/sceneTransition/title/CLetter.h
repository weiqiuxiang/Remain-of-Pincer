// letterの処理
#ifndef _CLETTER_H_
#define _CLETTER_H_

#include "main.h"
#include "scene2D.h"

#define NUM_MAX_LETTER (12)

class CLetter : public CScene
{
public:
	//CLetter();
	CLetter(int Priorit, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	~CLetter();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//セッター
	void SetPos(const D3DXVECTOR3& pos)override { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size)override { m_size = size; }
	void SetStartPos(const D3DXVECTOR3& startPos) { m_startPos = startPos; }
	void SetEndPos(const D3DXVECTOR3& endPos) { m_endPos = endPos; }
	void SetEndRot(const float& endRot) { m_endRot = endRot; }
	void SetVelocity(const D3DXVECTOR3& velocity) { m_velocity = velocity; }
	void SetRot(const float& rot) { m_rot = rot; }
	void SetDeltaRot(const float& deltaRot) { m_deltaRot = deltaRot; }
	void SetPushedL(const bool value) { m_pushedL = value; }
	void SetPushedR(const bool value) { m_pushedR = value; }
	void SetFall(const bool value) { m_fall = value; }
	void SetBottom(const float& bottom) { m_bottom = bottom; }

	void AddPos(const D3DXVECTOR3& value) { m_pos += value; }
	void AddVelocity(const D3DXVECTOR3& value) { m_velocity += value; }
	void AddRot(const float& value) { m_rot += value; }

	void PowerReset(void) {};            //受ける力をリセット
	void AddPowerX(float fPowerX) {};
	void AddPowerY(float fPowerY) {};

	//ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }                    //位置取得
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }
	D3DXVECTOR3 GetStartPos(void) { return m_startPos; }
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	float GetRot(void) { return m_rot; }
	float GetEndRot(void) { return m_endRot; }
	float GetDeltaRot(void) { return m_deltaRot; }
	float GetBottom(void) { return m_bottom; }
	static int GetPriority(void) { return s_nPriority; }
	bool GetPushedL(void) { return m_pushedL; }
	bool GetPushedR(void) { return m_pushedR; }
	bool GetFall(void) { return m_fall; }

	//他の関数
	static CLetter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, float bottom, float rot, char* filepass);
	void BindTexture(TEX_ID TexID);                                        //外のテクスチャを読み込む
	HRESULT LoadTexture(const char* filePass);                                                //対応読み込みテクスチャ番
	void SetVertex(void);

private:
	D3DXVECTOR3  m_pos;
	D3DXVECTOR3  m_size;
	D3DXVECTOR2  m_leftup;			// 左上の頂点XY
	D3DXVECTOR2  m_rightup;			// 右上の頂点XY
	D3DXVECTOR2  m_leftdown;		// 左下の頂点XY
	D3DXVECTOR2  m_rightdown;		// 右下の頂点XY	
	D3DXVECTOR2	 m_tex;
	D3DXVECTOR2  m_texsize;
	float		 m_length;			// ポリゴンの対角線の長さ
	float		 m_angle;			// ポリゴンの対角線の角度
	float		 m_rot;             // 回転角（ラジアン）

	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;

	TEX_ID		m_TEX_ID;		// テクスチャへのポインタ
	D3DXVECTOR3 m_startPos;     // スタート座標
	D3DXVECTOR3 m_endPos;       // ゴール座標
	D3DXVECTOR3 m_velocity;		// 速度
	float m_endRot;             // 落下後の角度
	float m_deltaRot;			// 角度の変化量
	float m_bottom;             // デフォルトの底辺Y座標
	int m_nValue;
	static int s_nPriority;
	bool m_pushedL;			    // 左から押される
	bool m_pushedR;				// 右から押される
	bool m_fall;                // 落下する
};

#endif
