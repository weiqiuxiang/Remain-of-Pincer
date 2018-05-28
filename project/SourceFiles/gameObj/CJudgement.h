#pragma once
#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_

#include "CJudge.h"

class CJudgement
{
public:
	static void Init(void);
	static void Update(void);

	//セッター
	static void ResetCreateFlag(void) { m_bJudge = false; }
private:
	//判定演出
	static void Judge(void);
	static bool JudgeCheck(void);         //評価を出す判定
	static void CreateJudge(void);          //判定のランク
	static void ShowJudge(void);          //判定の演出

	//判定関係
	static CJudge* m_pJudge;
	static bool m_bJudge;
	static int m_nJudgeEffectFrame;
};

#endif