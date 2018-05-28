
//
//�t�@�C���� : SceneManager.h
//���� : �V�[���J�ڎ��I�u�W�F�̐����ƍ폜��
//////////////////////////////////////////////////
#pragma once
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "main.h"

//�}�N��
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