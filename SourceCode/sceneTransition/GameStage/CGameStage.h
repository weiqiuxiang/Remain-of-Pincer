#pragma once
#ifndef _CGAMESTAGE_H_
#define _CGAMESTAGE_H_

#include "main.h"
#include "CSpring.h"

class CGameStage
{
public:
	//セッター
	static void SetStageNumber(int StageNumber) { m_nStageNumber = StageNumber; }
	//ゲッター
	static int GetStageNumber(void) { return m_nStageNumber; }
	//他の関数
	static void StageSelect(int StageNumber);
	static void LoadStageData(const char *FilePass);

private:
	//メンバ変数
	static int m_nStageNumber;
	static char m_aStageData[VERTICAL_BLOCK_MAX][HORIZON_BLOCK_MAX + 1];
	static CSpring *m_Spring;
};

#endif