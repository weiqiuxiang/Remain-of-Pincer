#pragma once
#ifndef _CEDITOR_SET_OBJ_H_
#define _CEDITOR_SET_OBJ_H_

#include "SceneManager.h"
#include "CSpring.h"

class CEditorSetObj
{
	typedef enum
	{
		TYPE_FLOOR = 0,
		TYPE_FLOOR_BREAK,
		TYPE_BALL,
		TYPE_SPRING,
		TYPE_ERASER
	}CREATE_OBJ_TYPE;

	typedef enum
	{
		STEP_MAIN = 0,
		STEP_CREATE_SPRING
	}STEP;

public:
	static void Init(void);
	static void Update(void);

private:
	//�����o�֐�
	static void ChangeCreateObjType(void);
	static void LockEditorObjInMouse(void);
	static void CreateObj(void);
	//�f�[�^�̓��o�͂Ɋւ���֐�
	static void SaveStageData(void);
	static void LoadDataFromFile(void);
	//�폜�Ɋ֘A����֐�
	static void DeleteObjFloor(void);
	static void DeleteObjBall(void);
	static void DeleteObjSpring(void);
	static void DeleteEditorObj(void);
	//�΂˂Ɋւ���֐�
	static bool CanSpringSet(int Y,int X);
	static void CreateSpringAndAdjustDir(void);

	//�����o�ϐ�
	static CREATE_OBJ_TYPE m_CreatType; 
	static STEP m_Step;
	static char m_aStageData[VERTICAL_BLOCK_MAX][HORIZON_BLOCK_MAX + 1];

	static CSpring *m_Spring;
	static D3DXVECTOR2 m_SpringPos;
};

#endif