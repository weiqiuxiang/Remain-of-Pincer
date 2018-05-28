#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "scene2D.h"

class CParticle :public CScene2D
{
public:
	CParticle() : CScene2D(7){}
	CParticle(int nPriority) : CScene2D(nPriority) {}
	~CParticle() {}
	HRESULT Init() { return S_OK; }
	void Update();
	void Draw() {}
	void Uninit() { CScene2D::Uninit(); }

	//ゲッター

	//セッター
	void SetStopFlag(bool StopFlag) { m_Stop = StopFlag; }
	void SetPosX(float PosX) { m_Pos_x = PosX; }
	void SetPosY(float PosY) { m_Pos_y = PosY; }

	static CParticle* Create(
		float Pos_x,			// 位置
		float Pos_y,			// 位置
		float Pos_z,			// 位置
		float Rot,				// 飛ぶ角度
		float Size_x,			// 横サイズ
		float Size_y,			// 縦サイズ
		float Size_z,			// 億サイズ
		float ScaleSpeed_x,		// 拡大変化量
		float ScaleSpeed_y,		// 拡大変化量
		float ScaleSpeed_z,		// 拡大変化量
		float Speed_x,			// 横スピード
		float Speed_y,			// 縦スピード
		float Speed_z,			// 縦スピード
		float Registance_x,		// 抵抗
		float Registance_y,		// 抵抗
		float Registance_z,		// 抵抗
		int ShotNum,			// 出る数
		float Life,			// 寿命
		float TextRot,			// 画像の角度
		float TextRotSpeed,	// 画像の回転速度
		float Red,				// 赤
		float Green,			// 緑
		float Blue,			// 青
		float Alpha,			// 透明
		float Gravity_x,			// 重力
		float Gravity_y,			// 重力
		float Gravity_z,			// 重力
//		EFFECT_LABEL Label,	// 画像
		float ShotWidth,		// 横の出る幅
		float ShotHeight,		// 縦の出る幅
		float ShotDepth,		// 奥の出る幅
		int NumWidth,			// 出る数幅
		float Speed_yWidth,	// スピードの幅
		float Speed_xWidth,
		float Speed_zWidth,	// スピードの幅
		float Size_xWidth,		// 縦サイズ幅
		float Size_yWidth,		// 横サイズ幅
		float Size_zWidth,		// 横サイズ幅
		float Gravity_xWidth,			// 重力幅
		float Gravity_yWidth,			// 重力幅
		float Gravity_zWidth,			// 重力幅
		float Registance_xWidth,		// 抵抗
		float Registance_yWidth,		// 抵抗
		float Registance_zWidth,		// 抵抗
		float TextRotWidth,			// 画像の角度
		float TextRotSpeedWidth,	// 画像の回転速度
		float RotWidth,		// 角度幅
		float LifeWidth,		// 寿命幅
		float RedWidth,		// 赤色幅
		float GreenWidth,		// 緑色幅
		float BlueWidth,		// 青色幅)
		float AlphaWidth,		// 緑色幅
		int BlendMode,			// 表示の仕方
		int ParticleLife,		// パーティクルの寿命
		const char* TexPass
		);

	void SetStop(bool Stop) { m_Stop = Stop; }
	void SetPosXYZ (D3DXVECTOR3& pos) {
		m_Pos_x = pos.x;
		m_Pos_y = pos.y;
		m_Pos_z = pos.z;
	}
	static int GetPriority(void) { return s_nPriority; }
private:
	float m_Pos_x;			// 位置
	float m_Pos_y;			// 位置
	float m_Pos_z;
	float m_Rot;				// 飛ぶ角度
	float m_Size_x;			// 横サイズ
	float m_Size_y;			// 縦サイズ
	float m_Size_z;
	float m_ScaleSpeed_x;		// 拡大変化量
	float m_ScaleSpeed_y;		// 拡大変化量
	float m_ScaleSpeed_z;		// 拡大変化量
	float m_Registance_x;		// 抵抗					未実装
	float m_Registance_y;		// 抵抗					未実装
	float m_Registance_z;		// 抵抗					未実装
	float m_Speed_x;			// 横スピード
	float m_Speed_y;			// 縦スピード
	float m_Speed_z;
	int   m_ShotNum;			// 出る数
	float m_Life;			// 寿命
	float m_TextRot;			// 画像の角度
	float m_TextRotSpeed;	// 画像の回転速度
				//float Wind ;			// 風
	float m_Red;				// 赤
	float m_Green;			// 緑
	float m_Blue;			// 青
	float m_Alpha;			// 透明
	float m_Gravity_x;			// 重力
	float m_Gravity_y;			// 重力
	float m_Gravity_z;			// 重力
//	EFFECTm__LABEL Label;	// 画像
	float m_ShotWidth;		// 横の出る幅
	float m_ShotHeight;		// 縦の出る幅
	float m_ShotDepth;		// Zのでる幅
	int   m_NumWidth;			// 出る数幅
	float m_Speed_yWidth;	// スピードの幅
	float m_Speed_xWidth;	// スピードの幅
	float m_Speed_zWidth;	// スピードの幅
	float m_Gravity_xWidth;			// 重力幅
	float m_Gravity_yWidth;			// 重力幅
	float m_Gravity_zWidth;			// 重力幅
	float m_Registance_xWidth;		// 抵抗幅
	float m_Registance_yWidth;		// 抵抗幅
	float m_Registance_zWidth;		// 抵抗幅
	float m_ScaleSpeed_xWidth;		// 拡大変化量幅
	float m_ScaleSpeed_yWidth;		// 拡大変化量幅
	float m_ScaleSpeed_zWidth;		// 拡大変化量幅
	float m_WindWidth;		// 風の幅
	float m_Size_xWidth;		// 縦サイズ幅
	float m_Size_yWidth;		// 横サイズ幅
	float m_Size_zWidth;		// 横サイズ幅
	float m_RotWidth;		// 角度幅
	float m_LifeWidth;		// 寿命幅
	float m_RedWidth;		// 赤色幅
	float m_GreenWidth;		// 緑色幅
	float m_BlueWidth;		// 青色幅
	float m_AlphaWidth;
	float m_TextRotWidth;			// 画像の角度
	float m_TextRotSpeedWidth;	// 画像の回転速度
	int m_ParticleLife;		// パーティクルの寿命
							//int Index ;				// 何番目のパーティク
	bool m_Stop;				// 発生が止まっているかどうか
	char m_TexPass[256];

	static int s_nPriority;
};

#endif