#pragma once
#ifndef SCENETRANSITION_H_
#define SCENETRANSITION_H_

#include "main.h"
#include "SceneManager.h"
#include "GameMaster.h"
#include "TutorialMaster.h"
#include "TutorialMaster02.h"
#include "ResultManager.h"
#include "input.h"
#include "inputmouse.h"
#include "renderer.h"
#include "CFade.h"

class CSceneTransition 
{
public:
	typedef enum
	{
		SCENE_TITLE = 0,
		SCENE_STAGE_SELECT,
		SCENE_TUTORIAL,
		SCENE_TUTORIAL02,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_EDITOR,
		SCENE_MAX
	}SCENE_NAME;

	typedef enum
	{
		FADE_NONE = 0,
		FADE_OUT,
		FADE_STOP,
		FADE_IN
	}FADE_MODE;

	//コンストラクタとデストラクタ
	CSceneTransition();
	~CSceneTransition();

	//Init,Uninit,Update,Draw関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//ゲッター
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);
	static CGameManager *GetGameMaster(void);
	static CTutorialMaster *GetTutorialMaster(void) { return m_pTutorialMaster; }
	static CTutorialMaster02 *GetTutorialMaster02(void) { return m_pTutorialMaster02; }
	static SCENE_NAME GetSceneNow(void) { return m_SceneNow; }

	//セッター
	static void SetScene(FADE_MODE fadeMode,SCENE_NAME sceneName);       //遷移したいシーン

	//他のファンクション関数
	static void DrawFade(void);

private:
	void SceneUpdateAndFadeUpdate(void);
	void SceneTransition(void);

	CSceneManager *m_SceneManager[SCENE_MAX];       //SceneManager

	static CFade m_FadeLeft;                                          //フェード
	static CFade m_FadeRight;
	static FADE_MODE m_FadeMode;                           //フェードの状態
	static SCENE_NAME m_SceneNow;                          //Sceneの状態
	static SCENE_NAME m_SceneOld;

	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;
	static CGameManager *m_pGameMaster;
	static CTutorialMaster *m_pTutorialMaster;
	static CTutorialMaster02 *m_pTutorialMaster02;
	static CResultManager *m_pResultManager;
	static int m_nFadeCnt;

};

#endif