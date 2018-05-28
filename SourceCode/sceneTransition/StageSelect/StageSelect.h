#pragma once
#ifndef STAGE_SELECT_H_
#define STAGE_SELECT_H_

#include "SceneManager.h"

class CStageSelect : public CSceneManager
{
public:
	void Init(void);
	void Uninit(void);
};

#endif