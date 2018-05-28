#pragma once
#ifndef _CEDITOR_H_
#define _CEDITOR_H_

#include "SceneManager.h"

class CEditor : public CSceneManager
{
public:
	CEditor();
	~CEditor();

	void Init(void);
	void Uninit(void);
};


#endif