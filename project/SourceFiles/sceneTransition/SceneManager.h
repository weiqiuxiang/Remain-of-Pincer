
//
//ファイル名 : SceneManager.h
//説明 : シーン遷移時オブジェの生成と削除役
//////////////////////////////////////////////////
#pragma once
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "main.h"

//マクロ
#define CSCENE_OBJ_MAX (100)

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
};

#endif