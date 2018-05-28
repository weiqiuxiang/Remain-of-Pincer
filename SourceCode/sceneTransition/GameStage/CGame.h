#pragma once
#ifndef _CGAME_H_
#define _CGAME_H_

#include "SceneManager.h"

class CGame : public CSceneManager
{
public:
	void Init(void);
	void Uninit(void);

private :
	char m_aStageData[VERTICAL_BLOCK_MAX + SAFE_DUMMY][HORIZON_BLOCK_MAX + SAFE_DUMMY];
};

#endif