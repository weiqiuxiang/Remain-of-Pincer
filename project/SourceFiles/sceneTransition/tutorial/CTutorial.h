#pragma once
#ifndef _CTUTORIAL_H_
#define _CTUTORIAL_H_

#include "SceneManager.h"

class CTutorial : public CSceneManager
{
public:
	void Init(void);
	void Uninit(void);
};

#endif