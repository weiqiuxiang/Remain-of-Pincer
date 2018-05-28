#include "SceneTraDecision.h"
#include "SceneTransition.h"

void CSceneTraDecision::SceneTraCheck(void)
{
	if(CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_Q))
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_W))
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TUTORIAL);
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_E))
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_GAME);
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_R))
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_RESULT);
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_T))
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_EDITOR);
	}
}