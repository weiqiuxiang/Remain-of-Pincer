#pragma once
#ifndef _CRESULT_H_
#define _CRESULT_H_

#include "SceneManager.h"

#define RESULT_NUMBER_WIDTH (100.0f) // リザルトのスコアの数字の幅
#define RESULT_NUMBER_HEIGHT (160.0f) // リザルトのスコアの数字の高さ
#define RESULT_NUMBER_INTV (15.0f)   // リザルトのスコアの数字の間隔

class CResult : public CSceneManager
{
public:
	void Init(void);
	void Uninit(void);
};


#endif