#include "SceneTransition.h"
#include "SceneTraDecision.h"
#include "scene.h"
#include "CExplosion.h"
#include "TexManager.h"
#include "CTitle.h"
#include "CTutorial.h"
#include "CTutorial02.h"
#include "CGame.h"
#include "CResult.h"
#include "CEditor.h"
#include "CEditorSetObj.h"
#include "CTitleMaster.h"
#include "CEarthquake.h"
#include "StageSelect.h"
#include "CStageMaster.h"
#include "sound.h"
#include "CResultScore.h"
#include "MouseParticle.h"
#include <time.h>

#define FADE_SPEED (20)
#define FADE_STOP_FRAME (30)

//�O���o�[��
CFade CSceneTransition::m_FadeLeft;
CFade CSceneTransition::m_FadeRight;
CSceneTransition::FADE_MODE CSceneTransition::m_FadeMode = CSceneTransition::FADE_NONE;
CSceneTransition::SCENE_NAME CSceneTransition::m_SceneNow = CSceneTransition::SCENE_TITLE;
CSceneTransition::SCENE_NAME CSceneTransition::m_SceneOld = CSceneTransition::SCENE_TITLE;
CRenderer *CSceneTransition::m_pRenderer = NULL;
CInputKeyboard *CSceneTransition::m_pInputKeyboard = NULL;
CInputMouse *CSceneTransition::m_pInputMouse = NULL;
CGameManager *CSceneTransition::m_pGameMaster = NULL;
CTutorialMaster *CSceneTransition::m_pTutorialMaster = NULL;
CTutorialMaster02 *CSceneTransition::m_pTutorialMaster02 = NULL;
CResultManager *CSceneTransition::m_pResultManager = NULL;
int CSceneTransition::m_nFadeCnt = 0;

//�R���X�g���N�^�ƃf�X�g���N�^
CSceneTransition::CSceneTransition()
{
	for (int i = 0; i < SCENE_MAX; i++)
	{
		m_SceneManager[i] = NULL;
	}
}

CSceneTransition::~CSceneTransition()
{
	
}

//Init,Uninit,Update,Draw�֐�
HRESULT CSceneTransition::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CTexManager::InitAll();               //�e�N�X�`���}�l�[�W���[������
	InitSound(hWnd);               //�T�E���h�̏�����

	//static�����o���̉��Ə�����
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	m_pInputMouse = new CInputMouse;
	m_pInputMouse->Init(hInstance, hWnd);
	m_pGameMaster = new CGameManager;
	m_pGameMaster->Init();
	m_pTutorialMaster = new CTutorialMaster;
	m_pTutorialMaster->Init();
	m_pTutorialMaster02 = new CTutorialMaster02;
	m_pTutorialMaster02->Init();
	m_pResultManager = new CResultManager;
	m_pResultManager->Init();

	//���g��r��
	for (int i = 0; i < SCENE_MAX; i++)
	{
		if (m_SceneManager[i] != NULL)
		{
			m_SceneManager[i]->Uninit();
			delete m_SceneManager[i];
			m_SceneManager[i] = NULL;
		}
	}

	//�eScene�}�l�[�W���[�̏�����
	for(int i = 0; i < SCENE_MAX; i++)
	{
		if (i == SCENE_TITLE) m_SceneManager[SCENE_TITLE] = new CTitle();
		if (i == SCENE_TUTORIAL) m_SceneManager[SCENE_TUTORIAL] = new CTutorial();
		if (i == SCENE_TUTORIAL02) m_SceneManager[SCENE_TUTORIAL02] = new CTutorial02();
		if (i == SCENE_STAGE_SELECT) m_SceneManager[SCENE_STAGE_SELECT] = new CStageSelect();
		if (i == SCENE_GAME) m_SceneManager[SCENE_GAME] = new CGame();
		if (i == SCENE_RESULT) m_SceneManager[SCENE_RESULT] = new CResult();
		if (i == SCENE_EDITOR) m_SceneManager[SCENE_EDITOR] = new CEditor();
	}

	//���̃����o�ϐ�������
	m_FadeMode = FADE_IN;
	m_SceneNow = SCENE_TITLE;

	m_SceneManager[m_SceneNow]->Init();             //�^�C�g���I�u�W�F�̏�����
	
	//�t�F�[�h������
	m_FadeLeft.Init(D3DXVECTOR3(-SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT, 0.0f), FADE_TEX);
	m_FadeRight.Init(D3DXVECTOR3(SCREEN_WIDTH*1.25, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT, 0.0f), FADE_TEX);
	m_FadeRight.SetUV(D3DXVECTOR2(1.0f,0.0f));
	m_FadeRight.SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));

	CResultScore::InitAllStageScore();                    //�X�R�A������

	CMouseParticle::Init();                    //�}�E�X�p�[�e�B�N���̏�����

	srand((unsigned)time(NULL));               //����

	return S_OK;
}

void CSceneTransition::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	CScene::ReleaseAll();
	CExplosion::Unload();

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�L�[�{�[�h�|�C���g�j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�}�E�X�j��
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//�Q�[���}�X�^�[�̔j��
	if (m_pGameMaster != NULL)
	{
		m_pGameMaster->Uninit();
		delete m_pGameMaster;
		m_pGameMaster = NULL;
	}

	//�`���[�g���A���}�X�^�[�̔j��
	if (m_pTutorialMaster != NULL)
	{
		m_pTutorialMaster->Uninit();
		delete m_pTutorialMaster;
		m_pTutorialMaster = NULL;
	}

	//�eScene�}�l�[�W���[���
	for (int i = 0; i < SCENE_MAX; i++)
	{
		if (m_SceneManager[i] != NULL)
		{
			m_SceneManager[i]->Uninit();
			delete m_SceneManager[i];
			m_SceneManager[i] = NULL;
		}
	}

	//���̃����o�ϐ����
	m_FadeLeft.Uninit();
	m_FadeRight.Uninit();
	CTexManager::UninitAll();

	UninitSound();                      //�T�E���h�̉��
}

void CSceneTransition::Update(void)
{
	SceneUpdateAndFadeUpdate();              //�V�[���}�l�[�W���[�ƃt�F�[�h�̍X�V
}

void CSceneTransition::Draw(void)
{
	if (m_pRenderer != NULL) m_pRenderer->Draw();
}

void CSceneTransition::SceneUpdateAndFadeUpdate(void)
{
	m_FadeLeft.Update();
	m_FadeRight.Update();
	CEarthquake::Update();

	switch (m_FadeMode)
	{
	case FADE_OUT:
	{
		D3DXVECTOR3 Pos;
		m_FadeLeft.AddPosX(FADE_SPEED);
		m_FadeRight.AddPosX(-FADE_SPEED);
		Pos = m_FadeLeft.GetPos();
		float percent = (Pos.x + SCREEN_WIDTH*0.25f) / (SCREEN_WIDTH*0.5f);
		SetAllSoundVolum(1.0f - percent);					//�T�E���h�̃t�F�[�h�A�E�g
		if (Pos.x >= SCREEN_WIDTH*0.25)
		{
			m_FadeLeft.SetPosX(SCREEN_WIDTH*0.25);
			m_FadeRight.SetPosX(SCREEN_WIDTH*0.75);
			//�G�t�F�N�g�Z�b�g
			CEarthquake::SetAngle(D3DX_PI);
			CEarthquake::SetAmplitude(5.0f);
			CEarthquake::SetDecrement(0.3f);
			StopSound();						//�S�ẴT�E���h��~
			SetAllSoundVolum(1.0f);
			PlaySound(SE_GATE_CLOSE);

			m_FadeMode = FADE_STOP;             //���̃V�[�����[�h�Ɉڍs
		}
		break;
	}
	case FADE_STOP:
		m_nFadeCnt++;
		if(m_nFadeCnt > FADE_STOP_FRAME)
		{
			m_nFadeCnt = 0;
			m_FadeMode = FADE_IN;
			SetAllSoundVolum(0.0f);
			SetSoundVolume(SE_GATE_OPEN,1.0f);
			PlaySound(SE_GATE_OPEN);
			SceneTransition();       //�V�[���J�ڊJ�n
		}
		break;
	case FADE_IN:
	{
		D3DXVECTOR3 Pos;
		m_FadeLeft.AddPosX(-FADE_SPEED);
		m_FadeRight.AddPosX(FADE_SPEED);
		Pos = m_FadeLeft.GetPos();
		float percent = (Pos.x + SCREEN_WIDTH*0.25) / (SCREEN_WIDTH*0.5f);
		SetAllSoundVolumOutOne(SE_GATE_OPEN,1.0f - percent);					//�T�E���h�̃t�F�[�h�C��
		if (Pos.x <= -SCREEN_WIDTH*0.25)
		{
			SetAllSoundVolum(1.0f);
			m_FadeLeft.SetPosX(-SCREEN_WIDTH*0.25);
			m_FadeRight.SetPosX(SCREEN_WIDTH*1.25);
			m_FadeMode = FADE_NONE;
		}
		break;
	}
	default:
		if (m_pInputKeyboard != NULL) m_pInputKeyboard->Update();  //�L�[�{�[�h�̍X�V����
		if (m_pInputMouse != NULL) m_pInputMouse->Update();
		if (m_pRenderer != NULL) m_pRenderer->Update();            //�����_���[�̍X�V����

		CMouseParticle::Update();     //�}�E�X�p�[�e�B�N��
		//�e�V�[���̓��ꏈ��
		switch (m_SceneNow)
		{
		case SCENE_TITLE:
			CTitleMaster::Update();
			break;
		case SCENE_STAGE_SELECT:
			CStageMaster::Update();
			break;
		case SCENE_TUTORIAL:
			if (m_pTutorialMaster != NULL) m_pTutorialMaster->Update();
			break;
		case SCENE_TUTORIAL02:
			if (m_pTutorialMaster02 != NULL) m_pTutorialMaster02->Update();
			break;
		case SCENE_GAME:
			if (m_pGameMaster != NULL) m_pGameMaster->Update();
			break;
		case SCENE_RESULT:
			if (m_pResultManager != NULL) m_pResultManager->Update();
			break;
		case SCENE_EDITOR:
			CEditorSetObj::Update();
			break;
		}
#ifdef _DEBUG
		CSceneTraDecision::SceneTraCheck();                      //�V�[���J�ڔ���
#endif
		break;
	}
}

void CSceneTransition::SceneTransition(void)
{
	//�Â��V�[���̃I�u�W�F���
	switch (m_SceneOld)
	{
	case SCENE_TITLE:
		m_SceneManager[SCENE_TITLE]->Uninit();
		break;
	case SCENE_STAGE_SELECT:
		m_SceneManager[SCENE_STAGE_SELECT]->Uninit();
		break;
	case SCENE_TUTORIAL:
		m_SceneManager[SCENE_TUTORIAL]->Uninit();
		break;
	case SCENE_TUTORIAL02:
		m_SceneManager[SCENE_TUTORIAL02]->Uninit();
		break;
	case SCENE_GAME:
		m_SceneManager[SCENE_GAME]->Uninit();
		break;
	case SCENE_RESULT:
		m_SceneManager[SCENE_RESULT]->Uninit();
		break;
	case SCENE_EDITOR:
		m_SceneManager[SCENE_EDITOR]->Uninit();
		break;
	}

	CMouseParticle::Uninit();

	//�J�ڐ�V�[���̃I�u�W�F������
	switch (m_SceneNow)
	{
	case SCENE_TITLE:
		m_SceneManager[SCENE_TITLE]->Init();
		CTitleMaster::Init();
		break;
	case SCENE_STAGE_SELECT:
		m_SceneManager[SCENE_STAGE_SELECT]->Init();
		break;
	case SCENE_TUTORIAL:
		m_SceneManager[SCENE_TUTORIAL]->Init();
		m_pTutorialMaster->Init();
		break;
	case SCENE_TUTORIAL02:
		m_SceneManager[SCENE_TUTORIAL02]->Init();
		m_pTutorialMaster02->Init();
		break;
	case SCENE_GAME:
		m_SceneManager[SCENE_GAME]->Init();
		m_pGameMaster->Init();
		break;
	case SCENE_RESULT:
		m_SceneManager[SCENE_RESULT]->Init();
		m_pResultManager->Init();
		break;
	case SCENE_EDITOR:
		m_SceneManager[SCENE_EDITOR]->Init();
		break;
	}

	CMouseParticle::Init();

	m_SceneOld = m_SceneNow;
}

//�Q�b�^�[
CRenderer *CSceneTransition::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyboard *CSceneTransition::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CInputMouse *CSceneTransition::GetInputMouse(void)
{
	return m_pInputMouse;
}

CGameManager *CSceneTransition::GetGameMaster(void)
{
	return m_pGameMaster;
}

//�Z�b�^�[
void CSceneTransition::SetScene(FADE_MODE fadeMode, SCENE_NAME sceneName)
{
	m_FadeMode = fadeMode;
	m_SceneOld = m_SceneNow;
	m_SceneNow = sceneName;
}

void CSceneTransition::DrawFade(void)
{
	m_FadeLeft.Draw();
	m_FadeRight.Draw();
}