#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"

#define SCENE_MAX_NUM (1200)
#define PRIORITY_MAX_NUM (16)

class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_SCORE_GAME,
		OBJTYPE_PLAYER_SELECTER,
		OBJTYPE_PLAYER_SELECTER_EF,
		OBJTYPE_WORM_HOLE,
		OBJTYPE_PLAYER_ARROW,
		OBJTYPE_RESET_BOTTON,
		OBJTYPE_PLAYER_GUILD,
		OBJTYPE_PLAYER,
		OBJTYPE_BALL,
		OBJTYPE_SPRING,
		OBJTYPE_FLOOR,
		OBJTYPE_EXPLOSION,
		OBJTYPE_JUDGE,
		OBJTYPE_PAUSE,
		OBJTYPE_GOTOTITLE,
		OBJTYPE_TITLE_TRA_OBJ,
		//�^�C�g������
		OBJTYPE_GOTOTITLE_BOTTON,
		OBJTYPE_GOTOSELECT_BOTTON,
		OBJTYPE_SCROLL_BAR,
		//�`���[�g���A��UI����
		OBJTYPE_TUTORIAL_BLACK,
		OBJTYPE_TUTORIAL_UI,
		OBJTYPE_TUTORIAL_EFFECT_UI,
		OBJTYPE_TUTORIAL_MOUSECLICKZONE,
		//���U���g����
		OBJTYPE_NUMBER,
		OBJTYPE_SCORE,
		OBJTYPE_TEXTBOX,
		OBJTYPE_RETRY_BOTTON,
		OBJTYPE_NEXT_BOTTON,
		OBJTYPE_BACKGROUND,
		//�G�f�B�^�[����
		OBJTYPE_EDITOR_FLOOR,
		OBJTYPE_EDITOR_BALL,
		OBJTYPE_EDITOR_ERASER,
		OBJTYPE_EDITOR_SPRING,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene();
	CScene(int nPriority = 3);
	virtual ~CScene();

	//Init,Uninit,Update,Draw�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
	//�Q�b�^�[
	virtual D3DXVECTOR3 GetPos(void) = 0;
	virtual D3DXVECTOR3 GetSize(void) = 0;
	OBJTYPE GetObjType(void);

	//�Z�b�^�[
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;
	virtual void SetSize(const D3DXVECTOR3& size) = 0;
	virtual void PowerReset(void) = 0;            //�󂯂�͂����Z�b�g
	virtual void AddPowerX(float fPowerX) = 0;
	virtual void AddPowerY(float fPowerY) = 0;
	void SetObjType(OBJTYPE objType);

	//static�֐�
	static void UpdateAll(void);                                   //�S�čX�V����
	static void DrawAll(void);                                     //�S�ĕ`�悷��
	static void ReleaseAll(void);                                  //�S�ĉ������
	static int GetNumScene(void);                         //�I�u�W�F�N�g�̑����Q�b�g
	static CScene *GetScene(int nIdxScene, int nPriority);
	
protected:
	void Release(void);              //�������g(CScene)���������
private:
	static CScene *m_apScene[PRIORITY_MAX_NUM][SCENE_MAX_NUM]; //Scene�I�u�W�F
	static int m_nNumScene;                  //�I�u�W�F�N�g�̑���
	int m_nID;                               //�I�u�W�F�N�g�ŗLID
	int m_nPriority;
	OBJTYPE m_Objtype;                       //�I�u�W�F�N�g�̎��
};

#endif