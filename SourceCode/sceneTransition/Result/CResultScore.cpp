#include "CResultScore.h"

int CResultScore::m_nUsePairMin = 0;                    //�ŏ��Z�b�g�v���[���[�y�A��
int CResultScore::m_nKillEnemyOneTurn = 0;              //1�^�[�����E�����G�̐�
int CResultScore::m_nKillEnemyOneTurnMax = 0;           //1�^�[�����E�����G�̐��̍ő�l
int CResultScore::m_nUsePairClear = 0;
double CResultScore::m_dScore = 0;
int CResultScore::m_StageScore[STAGE_MAX] = {4};
bool CResultScore::m_StageClearFlag[STAGE_MAX] = { false };

void CResultScore::Init(void)
{
	m_nUsePairMin = 0;
	m_nKillEnemyOneTurn = 0;
	m_nKillEnemyOneTurnMax = 0;
	m_dScore = 0;
}

void CResultScore::InitAllStageScore(void)
{
	for(int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++)
	{
		m_StageScore[nStageNum] = 4;
		m_StageClearFlag[nStageNum] = false;
	}
}