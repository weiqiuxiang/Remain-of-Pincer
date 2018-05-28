#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "Scene2D.h"

class CEffect:public CScene2D
{
public:
	CEffect();
	CEffect(int nPriority = 7);
	~CEffect();

	typedef struct
	{
		D3DXVECTOR2 Pos;		// 中心座標
		float Angle;			// 対角線の角度
		float Length;			// 対角線の半分の長さ
	}SPIN_INFO;
	static CEffect *Create(void);
	static CEffect *Create(  float x , float y , float Width , float Height , float Speed , float Rot , int Life);
	static CEffect *Create(  float x , float y , float Width , float Height , float Speed , float Rot , int Life , float r , float g , float b , float a );
	static CEffect *Create(float x, float y, float Width, float Height, float Speed_x , float Speed_y, float Rot, int Life ,
		float Gravity_x , float Gravity_y , float Registance_x , float Registance_y , float ScaleSpeed_x , float ScaleSpeed_y ,
		float r, float g, float b, float a ) ;
	void SetPos( float x , float y , float z ) ;
	void SetSpeed( float x , float y , float z ) ;
	void SetSize( float x , float y , float z ) ;
	void SetGravity( float x , float y , float z ) ;
	void SetRegistance( float x , float y , float z ) ;
	void SetScale( float x , float y , float z ) ;
	void SetScaleSpeed( float x , float y , float z ) ;

	static HRESULT Load( char File[] );
	static void UnLoad( void );
	static int GetPriority(void) { return s_nPriority; }

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
private:
	static TEX_ID m_TexID ;
	D3DXVECTOR3 Pos ;				// 座標
	D3DXVECTOR3 Speed ;				// スピード
	D3DXVECTOR3 Size ;				// 弾の大きさ
	D3DXVECTOR3 CollisionPos ;		// 当たり判定座標
	D3DXVECTOR3 Gravity ;					// 重力
	D3DXVECTOR3 Registance ;
	float Count ;					// カウント
	D3DXVECTOR3 Scale ;					// 拡大率
	D3DXVECTOR3 ScaleSpeed ;				// 拡大率の変化量
	float Rot ;						// 角度
	float RotSpeed ;				// 角度変化量
	float Radius ;					// 当たり判定半径
	float ColorAlphaValue ;			// 色の変化量
	float RadiusValue ;				// 半径変化量
	RGBA  Color ;				// 色
	SPIN_INFO Info ;				// 回転情報
	float MoveRot_xy ;					// 進む角度
	float MoveRot_xz ;					// 進む角度
	int Life ;						// 寿命
//	DRAW_TYPE BlendMode ;
	float Length ;					// カメラのと距離

	static int s_nPriority;
};

#endif