#include "CPause.h"
#include "hitCheck.h"
#include "SceneTransition.h"
#include "GameMaster.h"

//マクロ
#define FONT_WIDTH (291.0f)
#define FONT_HEIGHT (52.5f)

#define FONT_DISTANCEY (74.5f)

#define PAUSE_MENU_WIDTH (300)
#define PAUSE_MENU_HEIGHT (450)

#define RESUME_POSX (SCREEN_WIDTH*0.5)
#define RESUME_POSY (SCREEN_HEIGHT*0.33)

//グローバル変数
CPauseObj* CPause::m_MenuBar = NULL;
CPauseObj* CPause::m_FontResume = NULL;
CPauseObj* CPause::m_FontHelp = NULL;
CPauseObj* CPause::m_FontRitire = NULL;
CPauseObj* CPause::m_FontReturnTitle = NULL;
CPauseObj* CPause::m_FontReturnStageSelect = NULL;
CPauseObj* CPause::m_FontResumeEF = NULL;
CPauseObj* CPause::m_FontHelpEF = NULL;
CPauseObj* CPause::m_FontRitireEF = NULL;
CPauseObj* CPause::m_FontReturnTitleEF = NULL;
CPauseObj* CPause::m_FontReturnStageSelectEF = NULL;
CPauseObj* CPause::m_HelpImage = NULL;
bool CPause::m_bHelpFlag = false;

void CPause::Init(void)
{
	m_MenuBar = NULL;
	m_FontResume = NULL;
	m_FontHelp = NULL;
	m_FontRitire = NULL;
	m_FontReturnTitle = NULL;
	m_FontReturnStageSelect = NULL;
	m_FontResumeEF = NULL;
	m_FontHelpEF = NULL;
	m_FontRitireEF = NULL;
	m_FontReturnTitleEF = NULL;
	m_FontReturnStageSelectEF = NULL;
	m_bHelpFlag = false;
}

void CPause::DelectAllPauseObj(void)
{
	if( NULL != m_MenuBar){m_MenuBar->Uninit(); m_MenuBar = NULL;}                 //メニューバーの削除

	//フォントの削除
	if (NULL != m_FontResume){m_FontResume->Uninit(); m_FontResume = NULL;}
	if (NULL != m_FontHelp) { m_FontHelp->Uninit(); m_FontHelp = NULL; }
	if (NULL != m_FontRitire) { m_FontRitire->Uninit(); m_FontRitire = NULL; }
	if (NULL != m_FontReturnTitle){m_FontReturnTitle->Uninit(); m_FontReturnTitle = NULL;}
	if (NULL != m_FontReturnStageSelect){m_FontReturnStageSelect->Uninit(); m_FontReturnStageSelect = NULL;}

	//フォント効果の削除
	if (NULL != m_FontResumeEF) { m_FontResumeEF->Uninit(); m_FontResumeEF = NULL; }
	if (NULL != m_FontHelpEF) { m_FontHelpEF->Uninit(); m_FontHelpEF = NULL; }
	if (NULL != m_FontRitireEF) { m_FontRitireEF->Uninit(); m_FontRitireEF = NULL; }
	if (NULL != m_FontReturnTitleEF) { m_FontReturnTitleEF->Uninit(); m_FontReturnTitleEF = NULL; }
	if (NULL != m_FontReturnStageSelectEF) { m_FontReturnStageSelectEF->Uninit(); m_FontReturnStageSelectEF = NULL; }
}

void CPause::HitCheckMouseAndPauseObj(void)
{
	if (m_bHelpFlag == false)
	{
		HitFontResume();
		HitFontHelp();
		HitFontRetire();
		HitFontStageSelect();
		HitFontTitle();
	}

	else
	{
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) == false) return;
		if (NULL != m_HelpImage)
		{
			m_HelpImage->Uninit();
			m_HelpImage = NULL;
		}
		m_bHelpFlag = false;
	}
}

void CPause::CreatePauseBar(void)
{
	m_MenuBar = CPauseObj::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(PAUSE_MENU_WIDTH, PAUSE_MENU_HEIGHT, 0.0f), 255, false, {255,255,255},PAUSE_MENU_TEX);

	m_FontResume = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 255, false, { 255,255,255 }, PAUSE_FONT_TEX);
	m_FontResume->SetUV(D3DXVECTOR2(0.0f,0.0f));
	m_FontResume->SetUVWH(D3DXVECTOR2(1.0f, 0.2f));
	m_FontResume->Update();

	m_FontRitire = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 255, false, { 255,255,255 }, PAUSE_FONT_TEX);
	m_FontRitire->SetUV(D3DXVECTOR2(0.0f, 0.2f));
	m_FontRitire->SetUVWH(D3DXVECTOR2(1.0f, 0.2f));
	m_FontRitire->Update();

	m_FontHelp = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY *2, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 255, false, { 255,255,255 }, PAUSE_FONT_TEX);
	m_FontHelp->SetUV(D3DXVECTOR2(0.0f, 0.4f));
	m_FontHelp->SetUVWH(D3DXVECTOR2(1.0f, 0.2f));
	m_FontHelp->Update();

	m_FontReturnStageSelect = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY * 3, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 255, false, { 255,255,255 }, PAUSE_FONT_TEX);
	m_FontReturnStageSelect->SetUV(D3DXVECTOR2(0.0f, 0.6f));
	m_FontReturnStageSelect->SetUVWH(D3DXVECTOR2(1.0f, 0.2f));
	m_FontReturnStageSelect->Update();

	m_FontReturnTitle = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY * 4 , 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 255, false, { 255,255,255 }, PAUSE_FONT_TEX);
	m_FontReturnTitle->SetUV(D3DXVECTOR2(0.0f, 0.8f));
	m_FontReturnTitle->SetUVWH(D3DXVECTOR2(1.0f, 0.2f));
	m_FontReturnTitle->Update();
}

void CPause::HitFontResume(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	if (NULL != m_FontResume)
	{
		D3DXVECTOR3 ResumePos = m_FontResume->GetPos();
		D3DXVECTOR3 ResumeSize = m_FontResume->GetSize();

		bool bHit = CHitCheck::HitPointRect(MousePos, ResumePos, ResumeSize);
		if (bHit)
		{
			if (NULL == m_FontResumeEF)
			{
				m_FontResumeEF = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 150, false, { 187,127,90 }, PAUSE_FONTEF_TEX);
				m_FontResumeEF->SetUV(D3DXVECTOR2(0.0f, 0.0f));
				m_FontResumeEF->SetUVWH(D3DXVECTOR2(1.0f, 0.20f));
				m_FontResumeEF->Update();
			}
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) == true)
			{
				DelectAllPauseObj();
				CSceneTransition::GetGameMaster()->SetPauseFlag(false);
				return;
			}
		}
		else
		{
			if (NULL != m_FontResumeEF) { m_FontResumeEF->Uninit(); m_FontResumeEF = NULL; }
		}
	}
}

void CPause::HitFontHelp(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	if (NULL != m_FontHelp)
	{
		D3DXVECTOR3 ResumePos = m_FontHelp->GetPos();
		D3DXVECTOR3 ResumeSize = m_FontHelp->GetSize();

		bool bHit = CHitCheck::HitPointRect(MousePos, ResumePos, ResumeSize);
		if (bHit)
		{
			if (NULL == m_FontHelpEF)
			{
				m_FontHelpEF = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY *2, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 150, false, { 187,127,90 }, PAUSE_FONTEF_TEX);
				m_FontHelpEF->SetUV(D3DXVECTOR2(0.0f, 0.4f));
				m_FontHelpEF->SetUVWH(D3DXVECTOR2(1.0f, 0.20f));
				m_FontHelpEF->Update();
			}
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) == true)
			{
				if(m_HelpImage == NULL) m_HelpImage = CPauseObj::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.7, SCREEN_HEIGHT*0.7, 0.0f), 255, false, { 255,255,255 }, PAUSE_HELP_TEX);
				m_bHelpFlag = true;

				//フォント効果削除
				if (NULL != m_FontResumeEF) { m_FontResumeEF->Uninit(); m_FontResumeEF = NULL; }
				if (NULL != m_FontHelpEF) { m_FontHelpEF->Uninit(); m_FontHelpEF = NULL; }
				if (NULL != m_FontRitireEF) { m_FontRitireEF->Uninit(); m_FontRitireEF = NULL; }
				if (NULL != m_FontReturnTitleEF) { m_FontReturnTitleEF->Uninit(); m_FontReturnTitleEF = NULL; }
				if (NULL != m_FontReturnStageSelectEF) { m_FontReturnStageSelectEF->Uninit(); m_FontReturnStageSelectEF = NULL; }
				return;
			}
		}
		else
		{
			if (NULL != m_FontHelpEF) { m_FontHelpEF->Uninit(); m_FontHelpEF = NULL; }
		}
	}
}

void CPause::HitFontRetire(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	if (NULL != m_FontRitire)
	{
		D3DXVECTOR3 RetirePos = m_FontRitire->GetPos();
		D3DXVECTOR3 RetireSize = m_FontRitire->GetSize();

		bool bHit = CHitCheck::HitPointRect(MousePos, RetirePos, RetireSize);
		if (bHit)
		{
			if (NULL == m_FontRitireEF)
			{
				m_FontRitireEF = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 150, false, { 187,127,90 }, PAUSE_FONTEF_TEX);
				m_FontRitireEF->SetUV(D3DXVECTOR2(0.0f, 0.20f));
				m_FontRitireEF->SetUVWH(D3DXVECTOR2(1.0f, 0.20f));
				m_FontRitireEF->Update();
			}
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) == true)
			{
				CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_GAME);
				DelectAllPauseObj();
				CSceneTransition::GetGameMaster()->SetPauseFlag(false);
				return;
			}
		}
		else
		{
			if (NULL != m_FontRitireEF) { m_FontRitireEF->Uninit(); m_FontRitireEF = NULL; }
		}
	}
}

void CPause::HitFontStageSelect(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	if (NULL != m_FontReturnStageSelect)
	{
		D3DXVECTOR3 ReturnStageSelectPos = m_FontReturnStageSelect->GetPos();
		D3DXVECTOR3 ReturnStageSelectSize = m_FontReturnStageSelect->GetSize();

		bool bHit = CHitCheck::HitPointRect(MousePos, ReturnStageSelectPos, ReturnStageSelectSize);
		if (bHit)
		{
			if (NULL == m_FontReturnStageSelectEF)
			{
				m_FontReturnStageSelectEF = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY * 3, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 150, false, { 187,127,90 }, PAUSE_FONTEF_TEX);
				m_FontReturnStageSelectEF->SetUV(D3DXVECTOR2(0.0f, 0.60f));
				m_FontReturnStageSelectEF->SetUVWH(D3DXVECTOR2(1.0f, 0.20f));
				m_FontReturnStageSelectEF->Update();
			}
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) == true)
			{
				CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_STAGE_SELECT);
				DelectAllPauseObj();
				CSceneTransition::GetGameMaster()->SetPauseFlag(false);
				return;
			}
		}
		else
		{
			if (NULL != m_FontReturnStageSelectEF) { m_FontReturnStageSelectEF->Uninit(); m_FontReturnStageSelectEF = NULL; }
		}
	}
}

void CPause::HitFontTitle(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	if (NULL != m_FontReturnTitle)
	{
		D3DXVECTOR3 ReturnTitlePos = m_FontReturnTitle->GetPos();
		D3DXVECTOR3 ReturnTitleSize = m_FontReturnTitle->GetSize();

		bool bHit = CHitCheck::HitPointRect(MousePos, ReturnTitlePos, ReturnTitleSize);
		if (bHit)
		{
			if (NULL == m_FontReturnTitleEF)
			{
				m_FontReturnTitleEF = CPauseObj::Create(D3DXVECTOR3(RESUME_POSX, RESUME_POSY + FONT_DISTANCEY * 4, 0.0f), D3DXVECTOR3(FONT_WIDTH, FONT_HEIGHT, 0.0f), 150, false, { 187,127,90 }, PAUSE_FONTEF_TEX);
				m_FontReturnTitleEF->SetUV(D3DXVECTOR2(0.0f, 0.8f));
				m_FontReturnTitleEF->SetUVWH(D3DXVECTOR2(1.0f, 0.20f));
				m_FontReturnTitleEF->Update();
			}
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) == true)
			{
				CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
				DelectAllPauseObj();
				CSceneTransition::GetGameMaster()->SetPauseFlag(false);
				return;
			}
		}
		else
		{
			if (NULL != m_FontReturnTitleEF) { m_FontReturnTitleEF->Uninit(); m_FontReturnTitleEF = NULL; }
		}
	}
}