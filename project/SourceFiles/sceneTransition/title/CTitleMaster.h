#pragma once
#ifndef _CTITLE_MASTER_H_
#define _CTITLE_MASTER_H_

#include "main.h"
#include "CTitleTraBotton.h"
#include "CPillar.h"
#include "CLetter.h"
#include "Particle.h"

class CTitleMaster
{
public:
	typedef enum
	{
		TITLESTEP_1 = 0,
		TITLESTEP_2,
		TITLESTEP_3,
		TITLESTEP_4,
		TITLESTEP_5,
		TITLESTEP_6,
		TITLESTEP_7,
		TITLESTEP_8
	}TITLESTEP;

	static void Init(void);
	static void Update(void);

	static void CreateStartExit(void);

	//�Z�b�^�[
	static void SetPillar(CPillar* PillarL, CPillar* PillarR)
	{
		m_PillarL = PillarL;
		m_PillarR = PillarR;
	}

	static void SetLetter(CLetter** Letter)
	{
		for (int i = 0; i < 13; i++)
		{
			m_Letter[i] = Letter[i];
		}
	}

	//�Q�b�^�[
	static void GetWnd(HWND hWnd) { m_hWnd = hWnd; }                     //�E�B���h�E�̃n���h�����擾
private:
	static void HitPillarAndLetter(void);
	static void AnimeTitle(void);

	static CTitleTraBotton* HitCheckMouseAndTitleObj(void);  //�}�E�X�ƃ^�C�g���I�u�W�F�̓��蔻��(�I�u�W�F�N�g�̃V�[���J�ڃ^�C�v��Ԃ�)
	static void TraBottonScaleUp(CTitleTraBotton* pTitleTraBotton);
	static void TraBottonScaleDown(CTitleTraBotton* pTitleTraBotton);
	static void TraBottonScaleDownNotHit(CTitleTraBotton* pTitleTraBotton);
	static void Transition(CTitleTraBotton* pTitleTraBotton);
	static void DeleteAllTitleObj(void);
	static void FadeInTitleBgm(void);

	//�����o�ϐ�
	static HWND m_hWnd;

	static CLetter* m_Letter[12];
	static CPillar* m_PillarL;
	static CPillar* m_PillarR;
	static CParticle* m_ParticleL;
	static CParticle* m_ParticleR;
	static float m_bottom;
	static int m_timer;
	static TITLESTEP m_step;
	static bool m_bPlayHasamiSoundOneTime;
};

#endif