#pragma once
#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_

#include "CJudge.h"

class CJudgement
{
public:
	static void Init(void);
	static void Update(void);

	//�Z�b�^�[
	static void ResetCreateFlag(void) { m_bJudge = false; }
private:
	//���艉�o
	static void Judge(void);
	static bool JudgeCheck(void);         //�]�����o������
	static void CreateJudge(void);          //����̃����N
	static void ShowJudge(void);          //����̉��o

	//����֌W
	static CJudge* m_pJudge;
	static bool m_bJudge;
	static int m_nJudgeEffectFrame;
};

#endif