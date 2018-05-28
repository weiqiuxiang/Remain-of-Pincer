#pragma once
#ifndef CRESULT_SCORE_H_
#define CRESULT_SCORE_H_

#include "main.h"
#include "CStageMaster.h"

class CResultScore
{
public:
	//Init関数
	static void Init(void);
	static void InitAllStageScore(void);
	
	//セッター
	static void SetClearPair(int Value) { m_nUsePairClear = max(0,Value); }
	static void SetStageScore(int nStageNum, int Score) { m_StageScore[nStageNum] = Score; }
	static void SetStageClearFlag(int nStageNum, bool flag) { m_StageClearFlag[nStageNum] = flag; }   //ステージクリアフラグを設定

	//ゲッター
	static int GetUsePairMin(void) { return m_nUsePairMin; }
	static int GetKillEnemyOneTurn(void) { return m_nKillEnemyOneTurn; }
	static int GetKillEnemyOneTurnMax(void){ return m_nKillEnemyOneTurnMax; }
	static int GetClearPair(void) { return m_nUsePairClear; }
	static double GetStageScore(void) { return m_dScore; }
	static int GetStageScore(int nStageNum) { return m_StageScore[nStageNum]; }
	static bool GetStageClearFlag(int nStageNum) { return m_StageClearFlag[nStageNum]; }      //ステージクリアフラグを取得

	//別の関数
	static void IncrementPairMin(void) { m_nUsePairMin++; }
	static void IncrementKillEnemyOneTurn(void) { m_nKillEnemyOneTurn++; }
	static void CheckKillEnemyOneTurnMax(void)
	{
		if (m_nKillEnemyOneTurn > m_nKillEnemyOneTurnMax) m_nKillEnemyOneTurnMax = m_nKillEnemyOneTurn;
		m_nKillEnemyOneTurn = 0;         //1ターン中敵
	}
	static void AddScore(double Value) { m_dScore += Value; }

private:
	static int m_nUsePairMin;                    //最小セットプレーヤーペア数
	static int m_nKillEnemyOneTurn;              //1ターン中殺した敵の数
	static int m_nKillEnemyOneTurnMax;           //1ターン中殺した敵の数の最大値
	static int m_nUsePairClear;                  //最低クリア使用回数
	static double m_dScore;

	static int m_StageScore[STAGE_MAX];          //ステージごとのスコア
	static bool m_StageClearFlag[STAGE_MAX];     //ステージクリアフラグ
};

#endif