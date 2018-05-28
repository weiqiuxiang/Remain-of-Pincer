#pragma once
#ifndef _CGAMESTAGE_H_
#define _CGAMESTAGE_H_

#include "main.h"
#include "CSpring.h"

class CGameStage
{
public:
	//�Z�b�^�[
	static void SetStageNumber(int StageNumber) { m_nStageNumber = StageNumber; }
	//�Q�b�^�[
	static int GetStageNumber(void) { return m_nStageNumber; }
	//���̊֐�
	static void StageSelect(int StageNumber);
	static void LoadStageData(const char *FilePass);

private:
	//�����o�ϐ�
	static int m_nStageNumber;
	static char m_aStageData[VERTICAL_BLOCK_MAX][HORIZON_BLOCK_MAX + 1];
	static CSpring *m_Spring;
};

#endif