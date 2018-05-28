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

	//�Q�b�^�[

	//�Z�b�^�[
	void SetStopFlag(bool StopFlag) { m_Stop = StopFlag; }
	void SetPosX(float PosX) { m_Pos_x = PosX; }
	void SetPosY(float PosY) { m_Pos_y = PosY; }

	static CParticle* Create(
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
		);

	void SetStop(bool Stop) { m_Stop = Stop; }
	void SetPosXYZ (D3DXVECTOR3& pos) {
		m_Pos_x = pos.x;
		m_Pos_y = pos.y;
		m_Pos_z = pos.z;
	}
	static int GetPriority(void) { return s_nPriority; }
private:
	float m_Pos_x;			// �ʒu
	float m_Pos_y;			// �ʒu
	float m_Pos_z;
	float m_Rot;				// ��Ԋp�x
	float m_Size_x;			// ���T�C�Y
	float m_Size_y;			// �c�T�C�Y
	float m_Size_z;
	float m_ScaleSpeed_x;		// �g��ω���
	float m_ScaleSpeed_y;		// �g��ω���
	float m_ScaleSpeed_z;		// �g��ω���
	float m_Registance_x;		// ��R					������
	float m_Registance_y;		// ��R					������
	float m_Registance_z;		// ��R					������
	float m_Speed_x;			// ���X�s�[�h
	float m_Speed_y;			// �c�X�s�[�h
	float m_Speed_z;
	int   m_ShotNum;			// �o�鐔
	float m_Life;			// ����
	float m_TextRot;			// �摜�̊p�x
	float m_TextRotSpeed;	// �摜�̉�]���x
				//float Wind ;			// ��
	float m_Red;				// ��
	float m_Green;			// ��
	float m_Blue;			// ��
	float m_Alpha;			// ����
	float m_Gravity_x;			// �d��
	float m_Gravity_y;			// �d��
	float m_Gravity_z;			// �d��
//	EFFECTm__LABEL Label;	// �摜
	float m_ShotWidth;		// ���̏o�镝
	float m_ShotHeight;		// �c�̏o�镝
	float m_ShotDepth;		// Z�̂ł镝
	int   m_NumWidth;			// �o�鐔��
	float m_Speed_yWidth;	// �X�s�[�h�̕�
	float m_Speed_xWidth;	// �X�s�[�h�̕�
	float m_Speed_zWidth;	// �X�s�[�h�̕�
	float m_Gravity_xWidth;			// �d�͕�
	float m_Gravity_yWidth;			// �d�͕�
	float m_Gravity_zWidth;			// �d�͕�
	float m_Registance_xWidth;		// ��R��
	float m_Registance_yWidth;		// ��R��
	float m_Registance_zWidth;		// ��R��
	float m_ScaleSpeed_xWidth;		// �g��ω��ʕ�
	float m_ScaleSpeed_yWidth;		// �g��ω��ʕ�
	float m_ScaleSpeed_zWidth;		// �g��ω��ʕ�
	float m_WindWidth;		// ���̕�
	float m_Size_xWidth;		// �c�T�C�Y��
	float m_Size_yWidth;		// ���T�C�Y��
	float m_Size_zWidth;		// ���T�C�Y��
	float m_RotWidth;		// �p�x��
	float m_LifeWidth;		// ������
	float m_RedWidth;		// �ԐF��
	float m_GreenWidth;		// �ΐF��
	float m_BlueWidth;		// �F��
	float m_AlphaWidth;
	float m_TextRotWidth;			// �摜�̊p�x
	float m_TextRotSpeedWidth;	// �摜�̉�]���x
	int m_ParticleLife;		// �p�[�e�B�N���̎���
							//int Index ;				// ���Ԗڂ̃p�[�e�B�N
	bool m_Stop;				// �������~�܂��Ă��邩�ǂ���
	char m_TexPass[256];

	static int s_nPriority;
};

#endif