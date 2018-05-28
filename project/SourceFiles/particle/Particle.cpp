#define _CRT_SECURE_NO_WARNINGS
#include "Particle.h"
#include "Effect.h"
#include <random>

std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
int CParticle::s_nPriority = 10;            //�v���C�I���e�B

void CParticle::Update()
{
	if (m_Stop == true) return;
	CEffect::Load(m_TexPass);               //�e�N�X�`���؂�ւ�

	std::uniform_real_distribution<> randWidth(-m_ShotWidth, m_ShotWidth);		// ���̏o�镝����
	std::uniform_real_distribution<> randHeight(-m_ShotHeight, m_ShotHeight);		// �c�̏o�镝����
	std::uniform_real_distribution<> randDepth(-m_ShotDepth, m_ShotDepth);		// �c�̏o�镝����
	std::uniform_real_distribution<> randSpeedX(0, m_Speed_xWidth);									// ���x����
	std::uniform_real_distribution<> randSpeedY(0, m_Speed_yWidth);
	std::uniform_real_distribution<> randSpeedZ(0, m_Speed_zWidth);
	std::uniform_real_distribution<> randSizeX(0, m_Size_xWidth);									// �T�C�Y����
	std::uniform_real_distribution<> randSizeY(0, m_Size_yWidth);
	std::uniform_real_distribution<> randSizeZ(0, m_Size_zWidth);
	std::uniform_real_distribution<> randRegistanceX(0, m_Registance_xWidth);									// �T�C�Y����
	std::uniform_real_distribution<> randRegistanceY(0, m_Registance_yWidth);
	std::uniform_real_distribution<> randRegistanceZ(0, m_Registance_zWidth);
	std::uniform_real_distribution<> randScaleX(-m_ScaleSpeed_xWidth, m_ScaleSpeed_xWidth);									// �X�P�[������
	std::uniform_real_distribution<> randScaleY(-m_ScaleSpeed_yWidth, m_ScaleSpeed_yWidth);
	std::uniform_real_distribution<> randScaleZ(-m_ScaleSpeed_zWidth, m_ScaleSpeed_zWidth);
	std::uniform_real_distribution<> randGravityX(0, m_Gravity_xWidth);									// �X�P�[������
	std::uniform_real_distribution<> randGravityY(0, m_Gravity_yWidth);
	std::uniform_real_distribution<> randGravityZ(0, m_Gravity_zWidth);
	std::uniform_real_distribution<> randLife(0, m_LifeWidth);									// ���x����
	std::uniform_real_distribution<> randRot(-m_RotWidth, m_RotWidth);				// �p�x������
	std::uniform_real_distribution<> randRotText(-m_TextRotWidth, m_TextRotWidth);				// �p�x������
	std::uniform_real_distribution<> randRotTextSpeed(-m_TextRotSpeedWidth, m_TextRotSpeedWidth);
	std::uniform_real_distribution<> randColorRed(0.0f, m_RedWidth);									// �ԐF����
	std::uniform_real_distribution<> randColorGreen(0.0f, m_GreenWidth);								// �ΐF����
	std::uniform_real_distribution<> randColorBlue(0.0f, m_BlueWidth);									// �F����
	std::uniform_real_distribution<> randColorAlpha(0.0f, m_AlphaWidth);									// �F����
	for (int CntEffect = 0; CntEffect < m_ShotNum; CntEffect++)
	{
		CEffect::Create(
			m_Pos_x + randWidth(rnd),									// �ʒu�QX
			m_Pos_y + randHeight(rnd),									// �ʒu�QY ,
			m_Size_x + randSizeX(rnd),									// �T�C�Y�QX
			m_Size_y + randSizeY(rnd),									// �T�C�Y�QY
			m_Speed_x + randSpeedX(rnd),									// ���x�QX
			m_Speed_y + randSpeedY(rnd),									// ���x�QY

			m_Rot + randRot(rnd),						// ���ˊp�x
			m_Life + randLife(rnd),									// ����
			m_Gravity_x + randGravityX(rnd),									// �d��
			m_Gravity_y + randGravityY(rnd),									// ��
			m_Registance_x + randRegistanceX(rnd),									// ��R�QX
			m_Registance_y + randRegistanceY(rnd),									// ��R�QY
			
			m_ScaleSpeed_x + randScaleX(rnd),									// �g�呬�x�QX
			m_ScaleSpeed_y + randScaleY(rnd),									// �g�呬�x�QY
			(m_Red + randColorRed(rnd)) * 255,		// �ԐF
			(m_Green + randColorGreen(rnd)) * 255,				// �ΐF
			(m_Blue + randColorBlue(rnd)) * 255,				// �F
			(m_Alpha + randColorAlpha(rnd)) * 255 									// ���ߗ�
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
	float Pos_x,			// �ʒu
	float Pos_y,			// �ʒu
	float Pos_z,			// �ʒu
	float Rot,				// ��Ԋp�x
	float Size_x,			// ���T�C�Y
	float Size_y,			// �c�T�C�Y
	float Size_z,			// ���T�C�Y
	float ScaleSpeed_x,		// �g��ω���
	float ScaleSpeed_y,		// �g��ω���
	float ScaleSpeed_z,		// �g��ω���
	float Speed_x,			// ���X�s�[�h
	float Speed_y,			// �c�X�s�[�h
	float Speed_z,			// �c�X�s�[�h
	float Registance_x,		// ��R
	float Registance_y,		// ��R
	float Registance_z,		// ��R
	int ShotNum,			// �o�鐔
	float Life,			// ����
	float TextRot,			// �摜�̊p�x
	float TextRotSpeed,	// �摜�̉�]���x
	float Red,				// ��
	float Green,			// ��
	float Blue,			// ��
	float Alpha,			// ����
	float Gravity_x,			// �d��
	float Gravity_y,			// �d��
	float Gravity_z,			// �d��
								//		EFFECT_LABEL Label,	// �摜
	float ShotWidth,		// ���̏o�镝
	float ShotHeight,		// �c�̏o�镝
	float ShotDepth,		// ���̏o�镝
	int NumWidth,			// �o�鐔��
	float Speed_yWidth,	// �X�s�[�h�̕�
	float Speed_xWidth,
	float Speed_zWidth,	// �X�s�[�h�̕�
	float Size_xWidth,		// �c�T�C�Y��
	float Size_yWidth,		// ���T�C�Y��
	float Size_zWidth,		// ���T�C�Y��
	float Gravity_xWidth,			// �d�͕�
	float Gravity_yWidth,			// �d�͕�
	float Gravity_zWidth,			// �d�͕�
	float Registance_xWidth,		// ��R
	float Registance_yWidth,		// ��R
	float Registance_zWidth,		// ��R
	float TextRotWidth,			// �摜�̊p�x
	float TextRotSpeedWidth,	// �摜�̉�]���x
	float RotWidth,		// �p�x��
	float LifeWidth,		// ������
	float RedWidth,		// �ԐF��
	float GreenWidth,		// �ΐF��
	float BlueWidth,		// �F��)
	float AlphaWidth,		// �ΐF��
	int BlendMode,			// �\���̎d��
	int ParticleLife,		// �p�[�e�B�N���̎���
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