#pragma once
#ifndef CRESULT_SCORE_H_
#define CRESULT_SCORE_H_

#include "main.h"
#include "CStageMaster.h"

class CResultScore
{
public:
	//Init�֐�
	static void Init(void);
	static void InitAllStageScore(void);
	
	//�Z�b�^�[
	static void SetClearPair(int Value) { m_nUsePairClear = max(0,Value); }
	static void SetStageScore(int nStageNum, int Score) { m_StageScore[nStageNum] = Score; }
	static void SetStageClearFlag(int nStageNum, bool flag) { m_StageClearFlag[nStageNum] = flag; }   //�X�e�[�W�N���A�t���O��ݒ�

	//�Q�b�^�[
	static int GetUsePairMin(void) { return m_nUsePairMin; }
	static int GetKillEnemyOneTurn(void) { return m_nKillEnemyOneTurn; }
	static int GetKillEnemyOneTurnMax(void){ return m_nKillEnemyOneTurnMax; }
	static int GetClearPair(void) { return m_nUsePairClear; }
	static double GetStageScore(void) { return m_dScore; }
	static int GetStageScore(int nStageNum) { return m_StageScore[nStageNum]; }
	static bool GetStageClearFlag(int nStageNum) { return m_StageClearFlag[nStageNum]; }      //�X�e�[�W�N���A�t���O���擾

	//�ʂ̊֐�
	static void IncrementPairMin(void) { m_nUsePairMin++; }
	static void IncrementKillEnemyOneTurn(void) { m_nKillEnemyOneTurn++; }
	static void CheckKillEnemyOneTurnMax(void)
	{
		if (m_nKillEnemyOneTurn > m_nKillEnemyOneTurnMax) m_nKillEnemyOneTurnMax = m_nKillEnemyOneTurn;
		m_nKillEnemyOneTurn = 0;         //1�^�[�����G
	}
	static void AddScore(double Value) { m_dScore += Value; }

private:
	static int m_nUsePairMin;                    //�ŏ��Z�b�g�v���[���[�y�A��
	static int m_nKillEnemyOneTurn;              //1�^�[�����E�����G�̐�
	static int m_nKillEnemyOneTurnMax;           //1�^�[�����E�����G�̐��̍ő�l
	static int m_nUsePairClear;                  //�Œ�N���A�g�p��
	static double m_dScore;

	static int m_StageScore[STAGE_MAX];          //�X�e�[�W���Ƃ̃X�R�A
	static bool m_StageClearFlag[STAGE_MAX];     //�X�e�[�W�N���A�t���O
};

#endif