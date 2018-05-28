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
		//タイトル部分
		OBJTYPE_GOTOTITLE_BOTTON,
		OBJTYPE_GOTOSELECT_BOTTON,
		OBJTYPE_SCROLL_BAR,
		//チュートリアルUI部分
		OBJTYPE_TUTORIAL_BLACK,
		OBJTYPE_TUTORIAL_UI,
		OBJTYPE_TUTORIAL_EFFECT_UI,
		OBJTYPE_TUTORIAL_MOUSECLICKZONE,
		//リザルト部分
		OBJTYPE_NUMBER,
		OBJTYPE_SCORE,
		OBJTYPE_TEXTBOX,
		OBJTYPE_RETRY_BOTTON,
		OBJTYPE_NEXT_BOTTON,
		OBJTYPE_BACKGROUND,
		//エディター部分
		OBJTYPE_EDITOR_FLOOR,
		OBJTYPE_EDITOR_BALL,
		OBJTYPE_EDITOR_ERASER,
		OBJTYPE_EDITOR_SPRING,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene();
	CScene(int nPriority = 3);
	virtual ~CScene();

	//Init,Uninit,Update,Draw関数
	virtual HRESULT Init(void);
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
	//ゲッター
	virtual D3DXVECTOR3 GetPos(void) = 0;
	virtual D3DXVECTOR3 GetSize(void) = 0;
	OBJTYPE GetObjType(void);

	//セッター
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;
	virtual void SetSize(const D3DXVECTOR3& size) = 0;
	virtual void PowerReset(void) = 0;            //受ける力をリセット
	virtual void AddPowerX(float fPowerX) = 0;
	virtual void AddPowerY(float fPowerY) = 0;
	void SetObjType(OBJTYPE objType);

	//static関数
	static void UpdateAll(void);                                   //全て更新する
	static void DrawAll(void);                                     //全て描画する
	static void ReleaseAll(void);                                  //全て解放する
	static int GetNumScene(void);                         //オブジェクトの総数ゲット
	static CScene *GetScene(int nIdxScene, int nPriority);
	
protected:
	void Release(void);              //自分自身(CScene)を解放する
private:
	static CScene *m_apScene[PRIORITY_MAX_NUM][SCENE_MAX_NUM]; //Sceneオブジェ
	static int m_nNumScene;                  //オブジェクトの総数
	int m_nID;                               //オブジェクト固有ID
	int m_nPriority;
	OBJTYPE m_Objtype;                       //オブジェクトの種類
};

#endif