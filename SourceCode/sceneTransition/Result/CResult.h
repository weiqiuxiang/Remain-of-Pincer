#pragma once
#ifndef _CRESULT_H_
#define _CRESULT_H_

#include "SceneManager.h"

#define RESULT_NUMBER_WIDTH (100.0f) // ���U���g�̃X�R�A�̐����̕�
#define RESULT_NUMBER_HEIGHT (160.0f) // ���U���g�̃X�R�A�̐����̍���
#define RESULT_NUMBER_INTV (15.0f)   // ���U���g�̃X�R�A�̐����̊Ԋu

class CResult : public CSceneManager
{
public:
	void Init(void);
	void Uninit(void);
};


#endif