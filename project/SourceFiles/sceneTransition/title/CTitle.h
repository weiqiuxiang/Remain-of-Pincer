#pragma once
#ifndef _CTITLE_H_
#define _CTITLE_H_

#include "SceneManager.h"

#define TITLE_RELETIVE_X (325.0f)
#define TITLE_RELETIVE_Y (30.0f)

class CTitle : public CSceneManager
{
public:
	void Init(void);
	void Uninit(void);
};

#endif