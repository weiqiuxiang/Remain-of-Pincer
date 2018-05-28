#define _CRT_SECURE_NO_WARNINGS
#include "Particle.h"
#include "Effect.h"
#include <random>

std::random_device rnd;     // 非決定的な乱数生成器を生成
int CParticle::s_nPriority = 10;            //プライオリティ

void CParticle::Update()
{
	if (m_Stop == true) return;
	CEffect::Load(m_TexPass);               //テクスチャ切り替え

	std::uniform_real_distribution<> randWidth(-m_ShotWidth, m_ShotWidth);		// 横の出る幅乱数
	std::uniform_real_distribution<> randHeight(-m_ShotHeight, m_ShotHeight);		// 縦の出る幅乱数
	std::uniform_real_distribution<> randDepth(-m_ShotDepth, m_ShotDepth);		// 縦の出る幅乱数
	std::uniform_real_distribution<> randSpeedX(0, m_Speed_xWidth);									// 速度乱数
	std::uniform_real_distribution<> randSpeedY(0, m_Speed_yWidth);
	std::uniform_real_distribution<> randSpeedZ(0, m_Speed_zWidth);
	std::uniform_real_distribution<> randSizeX(0, m_Size_xWidth);									// サイズ乱数
	std::uniform_real_distribution<> randSizeY(0, m_Size_yWidth);
	std::uniform_real_distribution<> randSizeZ(0, m_Size_zWidth);
	std::uniform_real_distribution<> randRegistanceX(0, m_Registance_xWidth);									// サイズ乱数
	std::uniform_real_distribution<> randRegistanceY(0, m_Registance_yWidth);
	std::uniform_real_distribution<> randRegistanceZ(0, m_Registance_zWidth);
	std::uniform_real_distribution<> randScaleX(-m_ScaleSpeed_xWidth, m_ScaleSpeed_xWidth);									// スケール乱数
	std::uniform_real_distribution<> randScaleY(-m_ScaleSpeed_yWidth, m_ScaleSpeed_yWidth);
	std::uniform_real_distribution<> randScaleZ(-m_ScaleSpeed_zWidth, m_ScaleSpeed_zWidth);
	std::uniform_real_distribution<> randGravityX(0, m_Gravity_xWidth);									// スケール乱数
	std::uniform_real_distribution<> randGravityY(0, m_Gravity_yWidth);
	std::uniform_real_distribution<> randGravityZ(0, m_Gravity_zWidth);
	std::uniform_real_distribution<> randLife(0, m_LifeWidth);									// 速度乱数
	std::uniform_real_distribution<> randRot(-m_RotWidth, m_RotWidth);				// 角度幅乱数
	std::uniform_real_distribution<> randRotText(-m_TextRotWidth, m_TextRotWidth);				// 角度幅乱数
	std::uniform_real_distribution<> randRotTextSpeed(-m_TextRotSpeedWidth, m_TextRotSpeedWidth);
	std::uniform_real_distribution<> randColorRed(0.0f, m_RedWidth);									// 赤色乱数
	std::uniform_real_distribution<> randColorGreen(0.0f, m_GreenWidth);								// 緑色乱数
	std::uniform_real_distribution<> randColorBlue(0.0f, m_BlueWidth);									// 青色乱数
	std::uniform_real_distribution<> randColorAlpha(0.0f, m_AlphaWidth);									// 青色乱数
	for (int CntEffect = 0; CntEffect < m_ShotNum; CntEffect++)
	{
		CEffect::Create(
			m_Pos_x + randWidth(rnd),									// 位置＿X
			m_Pos_y + randHeight(rnd),									// 位置＿Y ,
			m_Size_x + randSizeX(rnd),									// サイズ＿X
			m_Size_y + randSizeY(rnd),									// サイズ＿Y
			m_Speed_x + randSpeedX(rnd),									// 速度＿X
			m_Speed_y + randSpeedY(rnd),									// 速度＿Y

			m_Rot + randRot(rnd),						// 発射角度
			m_Life + randLife(rnd),									// 寿命
			m_Gravity_x + randGravityX(rnd),									// 重力
			m_Gravity_y + randGravityY(rnd),									// 風
			m_Registance_x + randRegistanceX(rnd),									// 抵抗＿X
			m_Registance_y + randRegistanceY(rnd),									// 抵抗＿Y
			
			m_ScaleSpeed_x + randScaleX(rnd),									// 拡大速度＿X
			m_ScaleSpeed_y + randScaleY(rnd),									// 拡大速度＿Y
			(m_Red + randColorRed(rnd)) * 255,		// 赤色
			(m_Green + randColorGreen(rnd)) * 255,				// 緑色
			(m_Blue + randColorBlue(rnd)) * 255,				// 青色
			(m_Alpha + randColorAlpha(rnd)) * 255 									// 透過率
			);
	}
	if (m_ParticleLife == 0)
	{
		Uninit();
	}
	else if (m_ParticleLife > 0)
	{
		m_ParticleLife--;
	}
}

CParticle* CParticle::Create(
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
	)
{
	CParticle* pParticle;
	pParticle = new CParticle(s_nPriority);
	pParticle->m_Pos_x = Pos_x;
	pParticle->m_Pos_y = Pos_y;
	pParticle->m_Pos_z = Pos_z;
	pParticle->m_Rot = Rot;
	pParticle->m_Size_x = Size_x;
	pParticle->m_Size_y = Size_y;
	pParticle->m_Size_z = Size_z;
	pParticle->m_ScaleSpeed_x = ScaleSpeed_x;
	pParticle->m_ScaleSpeed_y = ScaleSpeed_y;
	pParticle->m_ScaleSpeed_z = ScaleSpeed_z;
	pParticle->m_Speed_x = Speed_x;
	pParticle->m_Speed_y = Speed_y;
	pParticle->m_Speed_z = Speed_z;
	pParticle->m_Registance_x = Registance_x;
	pParticle->m_Registance_y = Registance_y;
	pParticle->m_Registance_z = Registance_z;
	pParticle->m_ShotNum = ShotNum;
	pParticle->m_Life = Life;
	pParticle->m_TextRot = TextRot;
	pParticle->m_TextRotSpeed = TextRotSpeed;
	pParticle->m_Red = Red;
	pParticle->m_Green = Green;
	pParticle->m_Blue = Blue;
	pParticle->m_Alpha = Alpha;
	pParticle->m_Gravity_x = Gravity_x;
	pParticle->m_Gravity_y = Gravity_y;
	pParticle->m_Gravity_z = Gravity_z;
//	pParticle->m_Label = Label;
	pParticle->m_ShotWidth = ShotWidth;
	pParticle->m_ShotHeight = ShotHeight;
	pParticle->m_ShotDepth = ShotDepth;
	pParticle->m_NumWidth;
	pParticle->m_Speed_xWidth = Speed_xWidth;
	pParticle->m_Speed_yWidth = Speed_yWidth;
	pParticle->m_Speed_zWidth = Speed_zWidth;
	pParticle->m_Size_xWidth = Size_xWidth;
	pParticle->m_Size_yWidth = Size_yWidth;
	pParticle->m_Size_zWidth = Size_zWidth;
	pParticle->m_Gravity_xWidth = Gravity_xWidth;
	pParticle->m_Gravity_yWidth = Gravity_yWidth;
	pParticle->m_Gravity_zWidth = Gravity_zWidth;
	pParticle->m_Registance_xWidth = Registance_xWidth;
	pParticle->m_Registance_yWidth = Registance_yWidth;
	pParticle->m_Registance_zWidth = Registance_zWidth;
	pParticle->m_RotWidth = RotWidth;
	pParticle->m_LifeWidth = LifeWidth;
	pParticle->m_RedWidth = RedWidth;
	pParticle->m_GreenWidth = GreenWidth;
	pParticle->m_BlueWidth = BlueWidth;
	pParticle->m_AlphaWidth = AlphaWidth;
	pParticle->m_TextRotSpeedWidth = TextRotSpeedWidth;
	pParticle->m_TextRotWidth = TextRotWidth;
	pParticle->m_ParticleLife = ParticleLife;
	pParticle->m_Stop = false;
//	pParticle->m_BlendMode = BlendMode;
	strcpy(pParticle->m_TexPass, TexPass);
	return pParticle;

}