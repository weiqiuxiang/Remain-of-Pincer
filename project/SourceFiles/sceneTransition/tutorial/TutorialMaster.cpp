//�t�@�C���� : GameManager.cpp
//�X�V�� : 20170424
//Author : i syuusyou
//���� : ���蔻��̏����ƃv���[���[�̃R���g���[��

#include "TutorialMaster.h"
#include "SceneTransition.h"
#include "scene.h"
#include "CPlayer.h"
#include "SceneTransition.h"
#include "input.h"
#include "inputmouse.h"
#include "CPlayer.h"
#include "CFontUI.h"
#include "CTutorialBlack.h"
#include "CMouseClickZone.h"
#include "CResultScore.h"
#include "CPlayerSelecter.h"
#include "CSceneTraBotton.h"
#include "CPlayerGuild.h"
#include "sound.h"
#include "CJudgement.h"
#include "hitCheck.h"

#define SPEED_UNI_X (1.0f)            //�����^�����x
#define ARROW_DISTANCE_FROM_PLAYER (5.0f)
#define EAGE_RANGE (15.0f)
#define PLAYER_KILL_FRAME (100)
#define TUTORIAL_START_FRAME (30)

#define UI_DRAG0_XMOVE (960)
#define UI_DRAG0_YMOVE (620)

#define UI_DRAG1_XMOVE (800)
#define UI_DRAG1_YMOVE (300)

#define UI_DRAG2_XMOVE (1000)
#define UI_DRAG2_YMOVE (200)

#define UI_DRAG3_XMOVE (100)
#define UI_DRAG3_YMOVE (200)

#define UI_DRAG4_XMOVE (200)
#define UI_DRAG4_YMOVE (300)

#define COUNT_DOWN_FRAME (0)
#define PLAYER_ARROW_DISTANCE (50.0f)

#define FONT_FADE_SPEED (2)

void CTutorialMaster::Init(void)
{
	m_Num_PlayerCanUse = 2;
	m_TutorialStartTime = 0;
	m_bGameStart = false;
	m_GameStep = STEP_NONE;
	m_nPlayerKill = 0;
	m_nGameStartCnt = COUNT_DOWN_FRAME;
	m_PlayerArrowLeft = NULL;
	m_PlayerArrowRight = NULL;
	m_ExplainArrow = NULL;
	m_FontEffect = NULL;
	m_pScore = NULL;
	m_FontFade = FADE_OUT;
	CJudgement::Init();
	CResultScore::Init();

	CreatePlayerSelecterEF();
	m_PlayerSelecter = NULL;
}

void CTutorialMaster::Update(void)
{
	LockPlayerArrow();                  //�v���[���[�i�s�������̌Œ�
	SelecterEF();
	TutorialSkip();                 //�`���[�g���A���X�L�b�v
	SelecterScaleDown();            //�X�P�[���_�E���G�t�F�N�g
	if (m_pScore != NULL) m_pScore->SetScore(CResultScore::GetUsePairMin());
	switch (m_GameStep)
	{
	case STEP_NONE:
		TutorialStart();
		break;
	case STEP_CREATE_PLAYER1:
	{
		MouseCreatePlayer1();          //�}�E�X�Ńv���[���[��z�u
		break;
	}

	case STEP_DRAG_PLAYER1:
	{
		MouseDragPlayer1();        //�}�E�X�Ńv���[���[���h���b�N����
		break;
	}

	case STEP_CREATE_PLAYER2:
	{
		MouseCreatePlayer2();          //�}�E�X�Ńv���[���[��z�u
		break;
	}

	case STEP_SHOW_MOVE_DIR_LEFT:
	{
		ShowLeft();
		break;
	}

	case STEP_SHOW_MOVE_DIR_RIGHT:
	{
		ShowRight();
		break;
	}

	case STEP_DRAG_PLAYER2:
	{
		MouseDragPlayer2();          //�}�E�X�Ńv���[���[��z�u
		break;
	}

	case STEP_CREATE_COUNT:
	{
		GameCanStart();
		break;
	}

	case STEP_COUNT_DOWN:
	{
		CountDown();
		break;
	}

	case STEP_GAME_CAN_START:
	{
		GameStart();                            //�Q�[�����X�^�[�g
		if (m_nPlayerKill > 8) CJudgement::Update();
		GameFail();
		GamePlayerKill();
		GamePlayerReset();
		break;
	}
	}
}

void CTutorialMaster::Uninit(void)
{
	m_PlayerArrowLeft = NULL;
	m_PlayerArrowRight = NULL;
	m_pScore = NULL;
}

void CTutorialMaster::MouseDragPlayer1(void)
{
	D3DXVECTOR3 MousePosition = GetMousePosInWindow();

	FontEffect();

	int nPlayerPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//NULL�m�F
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;

			//�}�E�X�Ƀ��b�N����Ă��邩�ǂ����m�F
			bool mouseLock = pPlayer->GetMouseLock();
			if (mouseLock == true) pPlayer->SetPosition(MousePosition);
			else continue;         //���b�N���Ă��Ȃ�

								   //�v���[���[�z�u�m�F
			if (MousePosInClickZone() == false) continue;
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
			{
				pPlayer->SetMouseLock(false);
				m_GameStep = STEP_CREATE_PLAYER2;           //�v���[���[�ړ��������߂�i�K�Ɉڍs

															//�N���A
				ClearFontEffect();
				DeleteAllTutorialUI();                  //�폜
														//�쐬
				CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89 - UI_DRAG0_XMOVE, SCREEN_HEIGHT*1.08 - UI_DRAG0_YMOVE, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
				m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89 - UI_DRAG0_XMOVE, SCREEN_HEIGHT*1.08 - UI_DRAG0_YMOVE, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
				CFontUI* pUI = CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG0_XMOVE, SCREEN_HEIGHT*1.02 - UI_DRAG0_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
				pUI->SetUV(D3DXVECTOR2(0.0f, 1.0f));
				pUI->SetUVWH(D3DXVECTOR2(1.0f, -1.0f));
				pUI->Update();
				CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.0395, 0.0f), D3DXVECTOR3(60, 60, 0.0f), 60, SKIP_WHITE_TEX);

				PlaySound(SE_SET_STONE_PILLAR);                            //�T�E���h�Đ�

				CreatePlayerSelecterEF();
			}
			return;
		}
	}
}

void CTutorialMaster::MouseCreatePlayer1(void)
{
	bool PlayerCanNotCreate = m_Num_PlayerCanUse <= 0;
	if (PlayerCanNotCreate == true) return;           //�v���[���[��������ȏ���Ȃ�

	FontEffect();                        //�t�H���g�G�t�F�N�g
	SelecterScaleUp();                   //�X�P�[���A�b�v�G�t�F�N�g

										 //�v���[���[�����
	int PlayerSelectPri = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, PlayerSelectPri);
		if (pScene == NULL) continue;

		//���̃V�[�����v���[���[�����A�C�R���̎�
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_SELECTER)
		{
			//�}�E�X���W�ƃv���[���[�����A�C�R���̓��蔻��
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			D3DXVECTOR3 PlayerSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float PlayerLeft = PlayerPos.x - PlayerSize.x*0.5;
			float PlayerRight = PlayerPos.x + PlayerSize.x*0.5;
			float PlayerTop = PlayerPos.y - PlayerSize.y*0.5;
			float PlayerBottom = PlayerPos.y + PlayerSize.y*0.5;

			bool HitX = (MousePos.x <= PlayerRight) && (MousePos.x >= PlayerLeft);
			bool HitY = (MousePos.y <= PlayerBottom) && (MousePos.y >= PlayerTop);

			//���萬��
			if (HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CPlayer::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(20, 100.0f, 0.0f), PLAYER_TEX);  //�v���[���[���
					m_Num_PlayerCanUse--;                      //�v���[���[���鑍��������
					m_GameStep = STEP_DRAG_PLAYER1;             //�v���[���[�z�u�Ɉڍs

					PlaySound(SE_DRAP_PILLAR);        //�T�E���h�Đ�

													  //�N���A
					ClearFontEffect();
					DeleteAllTutorialUI();                  //�폜
															//�쐬
					CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG1_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG1_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_SETPLAYER_TEX);
					m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG1_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG1_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_SETPLAYER_TEX);
					CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG1_XMOVE, SCREEN_HEIGHT*0.8 - UI_DRAG1_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
					CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG1_XMOVE, SCREEN_HEIGHT*0.9 - UI_DRAG1_YMOVE, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);

					if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->Uninit();
					m_PlayerSelecterEF = NULL;
				}
			}
		}
	}
}

void CTutorialMaster::MouseDragPlayer2(void)
{
	D3DXVECTOR3 MousePosition = GetMousePosInWindow();

	FontEffect();

	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//NULL�m�F
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;

			//�}�E�X�Ƀ��b�N����Ă��邩�ǂ����m�F
			bool mouseLock = pPlayer->GetMouseLock();
			if (mouseLock == true) pPlayer->SetPosition(MousePosition);
			else continue;         //���b�N���Ă��Ȃ�

								   //�v���[���[�z�u�m�F
			if (MousePosInClickZone() == false) continue;
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
			{
				pPlayer->SetMouseLock(false);
				m_GameStep = STEP_CREATE_COUNT;           //�v���[���[�ړ��������߂�i�K�Ɉڍs

				DeletePlayerArrow();          //���폜
				DeleteAllTutorialUI();        //�`���[�g���A��UI�S�폜

				PlaySound(SE_SET_STONE_PILLAR);                            //�T�E���h�Đ�
			}
			return;
		}
	}
}

void CTutorialMaster::MouseCreatePlayer2(void)
{
	bool PlayerCanNotCreate = m_Num_PlayerCanUse <= 0;
	if (PlayerCanNotCreate == true) return;           //�v���[���[��������ȏ���Ȃ�

	FontEffect();
	SelecterScaleUp();                   //�X�P�[���A�b�v�G�t�F�N�g

	//�v���[���[�����
	int nPlayerSelectPri = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerSelectPri);
		if (pScene == NULL) continue;

		//���̃V�[�����v���[���[�����A�C�R���̎�
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_SELECTER)
		{
			//�}�E�X���W�ƃv���[���[�����A�C�R���̓��蔻��
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			D3DXVECTOR3 PlayerSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float PlayerLeft = PlayerPos.x - PlayerSize.x*0.5;
			float PlayerRight = PlayerPos.x + PlayerSize.x*0.5;
			float PlayerTop = PlayerPos.y - PlayerSize.y*0.5;
			float PlayerBottom = PlayerPos.y + PlayerSize.y*0.5;

			bool HitX = (MousePos.x <= PlayerRight) && (MousePos.x >= PlayerLeft);
			bool HitY = (MousePos.y <= PlayerBottom) && (MousePos.y >= PlayerTop);

			//���萬��
			if (HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CPlayer::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(20, 100.0f, 0.0f), PLAYER_TEX);  //�v���[���[���
					m_Num_PlayerCanUse--;                      //�v���[���[���鑍��������
					m_GameStep = STEP_SHOW_MOVE_DIR_LEFT;      //�v���[���[�����U���Ɉڍs

					PlaySound(SE_DRAP_PILLAR);        //�T�E���h�Đ�

													  //�N���A
					ClearFontEffect();
					DeleteAllTutorialUI();                  //�폜
															//�쐬
					CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.85, 0.0f), D3DXVECTOR3(420, 50, 0.0f), 255, { 100,100,200 }, false, FONT_EXPLAIN_ARROW_TEX);
					CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_MOVEPLAYER_TEX);
					m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_MOVEPLAYER_TEX);
					CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.8 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
					CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.9 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);

					CreatePlayerArrow();              //�����������

					if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->Uninit();
					m_PlayerSelecterEF = NULL;
				}
			}
		}
	}
}

void CTutorialMaster::GameStart(void)
{
	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//�v���[���[������
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer->GetMoveDirection() == false) pPlayer->AddPowerX(-SPEED_UNI_X);
			else pPlayer->AddPowerX(SPEED_UNI_X);
		}
	}
}

void CTutorialMaster::GameCanStart(void)
{
	if (m_Num_PlayerCanUse > 0) return;
	
	//�J�E���g�_�E�������
	int nCountDown = m_nGameStartCnt / 60;
	m_GameStep = STEP_COUNT_DOWN;
	DeleteAllAllTutorialUI();               //�`���[�g���A��UI�S�폜
}

void CTutorialMaster::CountDown(void)
{
	m_nGameStartCnt--;                       //�X�^�[�g�J�E���g�_�E��
	int nCountDown = m_nGameStartCnt / 60;
	if (m_nGameStartCnt > 0) return;

	m_GameStep = STEP_GAME_CAN_START;
	m_bGameStart = true;
	CResultScore::IncrementPairMin();
	m_nGameStartCnt = COUNT_DOWN_FRAME;

	DeletePlayerGuild();;                             //�v���[���[�K�C�h�폜
}

void CTutorialMaster::GameFail(void)
{
	int nFailTimes = 0;            //���s��
	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
		if (pPlayer == NULL) continue;

		//�ǍۂƂ̔���
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerPosOld = pPlayer->GetPosOld();

		if (PlayerPos == PlayerPosOld)
		{
			nFailTimes++;
		}
	}
	if (nFailTimes == 2) m_nPlayerKill++;
}

void CTutorialMaster::GamePlayerKill(void)
{
	if (m_nPlayerKill <= PLAYER_KILL_FRAME) return;

	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
		if (pPlayer == NULL) continue;

		pPlayer->ChangeAlpha(-5);
		int PlayerAlpha = pPlayer->GetAlpha();
		if (PlayerAlpha == 0)
		{
			CResultScore::CheckKillEnemyOneTurnMax();    //1�^�[���E�����G�̐��͍ő傩�ǂ���
			pPlayer->Uninit();
		}
	}
}

void CTutorialMaster::GamePlayerReset(void)
{
	int nPlayerNum = 0;            //���s��
	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		nPlayerNum++;
	}

	//�v���[���[�̍Ĕz�u�񐔂�0�ȏ�̎�
	if (nPlayerNum != 0) return;
	PlaySound(SE_CLEAR);
	CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
}

void CTutorialMaster::TutorialSkip(void)
{
	int nTraBottonPri = CSceneTraBotton::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nTraBottonPri);
		if (pScene == NULL) continue;

		//���Z�b�g�{�^������
		if (pScene->GetObjType() == CScene::OBJTYPE_RESET_BOTTON)
		{
			//�}�E�X���W�ƃv���[���[�����A�C�R���̓��蔻��
			D3DXVECTOR3 BottonPos = pScene->GetPos();
			D3DXVECTOR3 BottonSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float BottonLeft = BottonPos.x - BottonSize.x*0.5;
			float BottonRight = BottonPos.x + BottonSize.x*0.5;
			float BottonTop = BottonPos.y - BottonSize.y*0.5;
			float BottonBottom = BottonPos.y + BottonSize.y*0.5;

			bool HitX = (MousePos.x <= BottonRight) && (MousePos.x >= BottonLeft);
			bool HitY = (MousePos.y <= BottonBottom) && (MousePos.y >= BottonTop);

			CSceneTraBotton* pTra = dynamic_cast<CSceneTraBotton*>(pScene);
			if (NULL == pTra) return;

			//���萬��
			if (HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
				}

				pTra->SetScale(1.2f);
			}

			else pTra->SetScale(1.0f);
		}
	}
}

void CTutorialMaster::TutorialStart(void)
{
	m_TutorialStartTime++;
	if (m_TutorialStartTime < TUTORIAL_START_FRAME) return;

	//�N���A
	ClearFontEffect();
	DeleteAllTutorialUI();                  //�폜
	//�쐬
	CTutorialBlack::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 120, SKIP_BLACK_TEX);
	CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89 - UI_DRAG0_XMOVE, SCREEN_HEIGHT*1.08 - UI_DRAG0_YMOVE, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
	m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89 - UI_DRAG0_XMOVE, SCREEN_HEIGHT*1.08 - UI_DRAG0_YMOVE, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
	CFontUI* pUI = CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG0_XMOVE, SCREEN_HEIGHT*1.02 - UI_DRAG0_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
	pUI->SetUV(D3DXVECTOR2(0.0f,1.0f));
	pUI->SetUVWH(D3DXVECTOR2(1.0f, -1.0f));
	pUI->Update();
	CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.0395, 0.0f), D3DXVECTOR3(60, 60, 0.0f), 60, SKIP_WHITE_TEX);
	m_pScore = CScoreGame::Create(D3DXVECTOR3(SCREEN_WIDTH*0.822, SCREEN_HEIGHT*0.013, 0.0f), D3DXVECTOR3(30.0f, 42.85, 0.0f), 26.0f, 2, SCORE_TEX);
	m_PlayerSelecter = CPlayerSelecter::Create
	(
		D3DXVECTOR3(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.0395, 0.0f), D3DXVECTOR3(45.0f, 45.0f, 0.0f),
		255, { 255,255,255 }, false, PLAYER_SELECT_BLADE_TEX
	);

	//���̃X�e�b�v�ڍs
	m_GameStep = STEP_CREATE_PLAYER1;
}

void CTutorialMaster::DeleteAllTutorialUI(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CFontUI::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene != NULL)
		{
			bool TutorialUIYes = pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_UI;
			if (TutorialUIYes)
			{
				CFontUI *pTUI = dynamic_cast <CFontUI *> (pScene);
				if (pTUI == NULL) continue;
				pTUI->Uninit();
			}
		}

		nPriority = CFontUIEffect::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene != NULL)
		{
			bool TutorialUIYes = pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_EFFECT_UI;
			if (TutorialUIYes)
			{
				CFontUIEffect *pTUI = dynamic_cast <CFontUIEffect *> (pScene);
				if (pTUI == NULL) continue;
				pTUI->Uninit();
			}
		}

		nPriority = CMouseClickZone::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene != NULL)
		{
			bool MouseClickZoneYes = pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_MOUSECLICKZONE;
			if (MouseClickZoneYes)
			{
				CMouseClickZone *pMouseZone = dynamic_cast <CMouseClickZone *> (pScene);
				if (pMouseZone == NULL) continue;
				pMouseZone->Uninit();
			}
		}
	}
}

void CTutorialMaster::DeleteAllAllTutorialUI(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		nPriority = CFontUI::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene != NULL)
		{
			bool TutorialUIYes = pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_UI;
			if (TutorialUIYes)
			{
				CFontUI *pTUI = dynamic_cast <CFontUI *> (pScene);
				if (pTUI == NULL) continue;
				pTUI->Uninit();
			}
		}

		nPriority = CMouseClickZone::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene != NULL)
		{
			bool MouseClickZoneYes = pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_MOUSECLICKZONE;

			if (MouseClickZoneYes)
			{
				CMouseClickZone *pMouseZone = dynamic_cast <CMouseClickZone *> (pScene);
				if (pMouseZone == NULL) continue;
				pMouseZone->Uninit();
			}
		}


		nPriority = CTutorialBlack::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene != NULL)
		{
			bool TutorialBlack = pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_BLACK;
			if (TutorialBlack)
			{
				CTutorialBlack *pTutorialBlack = dynamic_cast <CTutorialBlack *> (pScene);
				if (pTutorialBlack == NULL) continue;
				pTutorialBlack->Uninit();
			}
		}
	}
}

bool CTutorialMaster::MousePosInClickZone(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	int nPriority = CMouseClickZone::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//���Z�b�g�{�^������
		if (pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_MOUSECLICKZONE)
		{
			//�}�E�X���W�ƃv���[���[�����A�C�R���̓��蔻��
			D3DXVECTOR3 BottonPos = pScene->GetPos();
			D3DXVECTOR3 BottonSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float BottonLeft = BottonPos.x - BottonSize.x*0.5;
			float BottonRight = BottonPos.x + BottonSize.x*0.5;
			float BottonTop = BottonPos.y - BottonSize.y*0.5;
			float BottonBottom = BottonPos.y + BottonSize.y*0.5;

			bool HitX = (MousePos.x <= BottonRight) && (MousePos.x >= BottonLeft);
			bool HitY = (MousePos.y <= BottonBottom) && (MousePos.y >= BottonTop);
			if (HitX && HitY) return true;
		}
	}

	return false;
}

void CTutorialMaster::LockPlayerArrow(void)
{
	if (NULL == m_PlayerArrowLeft) return;
	if (NULL == m_PlayerArrowRight) return;

	//�v���[���[��T��
	D3DXVECTOR3 PlayerPos[2];
	int PlayerNum = 0;
	int nPriority = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//���̃V�[�����v���[���[�����A�C�R���̎�
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			PlayerPos[PlayerNum] = pScene->GetPos();
			PlayerNum++;
			if (PlayerNum == 2) break;
		}
	}

	//�ʒu�ݒ�
	D3DXVECTOR3 LeftPos, RightPos;
	if (PlayerPos[0].x > PlayerPos[1].x)
	{
		LeftPos = PlayerPos[1];
		LeftPos.x = LeftPos.x + PLAYER_ARROW_DISTANCE;
		RightPos = PlayerPos[0];
		RightPos.x = RightPos.x - PLAYER_ARROW_DISTANCE;
	}
	else
	{
		LeftPos = PlayerPos[0];
		LeftPos.x = LeftPos.x + PLAYER_ARROW_DISTANCE;
		RightPos = PlayerPos[1];
		RightPos.x = RightPos.x - PLAYER_ARROW_DISTANCE;
	}

	m_PlayerArrowLeft->SetPos(LeftPos);
	m_PlayerArrowRight->SetPos(RightPos);
}

void CTutorialMaster::CreatePlayerArrow(void)
{
	//�v���[���[��T��
	D3DXVECTOR3 PlayerPos[2];
	int PlayerNum = 0;
	int nPriority = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//���̃V�[�����v���[���[�����A�C�R���̎�
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			PlayerPos[PlayerNum] = pScene->GetPos();
			PlayerNum++;
			if (PlayerNum == 2) break;
		}
	}

	D3DXVECTOR3 LeftPos, RightPos;
	if (PlayerPos[0].x > PlayerPos[1].x)
	{
		LeftPos = PlayerPos[1];
		LeftPos.x = LeftPos.x + PLAYER_ARROW_DISTANCE;
		RightPos = PlayerPos[0];
		RightPos.x = RightPos.x - PLAYER_ARROW_DISTANCE;
	}
	else
	{
		LeftPos = PlayerPos[0];
		LeftPos.x = LeftPos.x + PLAYER_ARROW_DISTANCE;
		RightPos = PlayerPos[1];
		RightPos.x = RightPos.x - PLAYER_ARROW_DISTANCE;
	}

	m_PlayerArrowLeft = CPlayerArrow::Create(LeftPos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), ARROW_TEX);
	m_PlayerArrowRight = CPlayerArrow::Create(RightPos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), ARROW_TEX);
	m_ExplainArrow = CPlayerArrow::Create(D3DXVECTOR3(SCREEN_WIDTH*0.32, SCREEN_HEIGHT*0.85, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), ARROW_TEX);
	m_PlayerArrowLeft->SetUV(D3DXVECTOR2(1.0f, 0.0f));
	m_PlayerArrowLeft->SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));
	m_PlayerArrowLeft->Update();
}

void CTutorialMaster::DeletePlayerArrow(void)
{
	if (NULL != m_PlayerArrowLeft)
	{
		m_PlayerArrowLeft->Uninit();
		m_PlayerArrowLeft = NULL;
	}

	if (NULL != m_PlayerArrowRight)
	{
		m_PlayerArrowRight->Uninit();
		m_PlayerArrowRight = NULL;
	}
}

void CTutorialMaster::DeletePlayerGuild(void)
{
	//�v���[���[�K�C�h�폜
	int PlayerGuildPri = CPlayerGuild::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, PlayerGuildPri);
		if (pScene == NULL) continue;

		//�v���[���[������
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_GUILD)
		{
			CPlayerGuild *pPlayerGuild = dynamic_cast <CPlayerGuild *> (pScene);
			if (pPlayerGuild == NULL) continue;
			pPlayerGuild->Uninit();
		}
	}
}

void CTutorialMaster::ShowLeft(void)
{
	D3DXVECTOR3 MousePosition = GetMousePosInWindow();

	FontEffect();

	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//NULL�m�F
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;

			//�}�E�X�Ƀ��b�N����Ă��邩�ǂ����m�F
			bool mouseLock = pPlayer->GetMouseLock();
			if (mouseLock == true) pPlayer->SetPosition(MousePosition);
			else continue;         //���b�N���Ă��Ȃ�
		}
	}

	if (MousePosInClickZone() == false) return;
	m_GameStep = STEP_SHOW_MOVE_DIR_RIGHT;         //�E�����U���Ɉڍs

	//UI���
	//�N���A
	ClearFontEffect();
	DeleteAllTutorialUI();                  //�폜
											//�쐬
	CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.85, 0.0f), D3DXVECTOR3(420, 50, 0.0f), 255, { 100,100,200 }, false, FONT_EXPLAIN_ARROW_TEX);
	CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG3_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG3_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_MOVEPLAYER_TEX);
	m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG3_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG3_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_MOVEPLAYER_TEX);
	CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG3_XMOVE, SCREEN_HEIGHT*0.8 - UI_DRAG3_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
	CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG3_XMOVE, SCREEN_HEIGHT*0.9 - UI_DRAG3_YMOVE, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);
}

void CTutorialMaster::ShowRight(void)
{
	D3DXVECTOR3 MousePosition = GetMousePosInWindow();

	FontEffect();

	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//NULL�m�F
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;

			//�}�E�X�Ƀ��b�N����Ă��邩�ǂ����m�F
			bool mouseLock = pPlayer->GetMouseLock();
			if (mouseLock == true) pPlayer->SetPosition(MousePosition);
			else continue;         //���b�N���Ă��Ȃ�
		}
	}

	if (MousePosInClickZone() == false) return;
	m_GameStep = STEP_DRAG_PLAYER2;         //�E�����U���Ɉڍs

	if(NULL != m_ExplainArrow) m_ExplainArrow->Uninit();
	m_ExplainArrow = NULL;
	ClearFontEffect();
	DeleteAllTutorialUI();                  //�폜
											//�쐬
	CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG4_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG4_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_SETPLAYER_TEX);
	m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG4_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG4_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_SETPLAYER_TEX);
	CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG4_XMOVE, SCREEN_HEIGHT*0.8 - UI_DRAG4_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
	CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG4_XMOVE, SCREEN_HEIGHT*0.9 - UI_DRAG4_YMOVE, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);
}

void CTutorialMaster::ClearFontEffect(void)
{
	m_FontEffect = NULL;
	m_FontFade = FADE_OUT;
}

void CTutorialMaster::FontEffect(void)
{
	if (NULL == m_FontEffect) return;
	int AlphaNow = 0;
	switch (m_FontFade)
	{
	case FADE_OUT:
		AlphaNow = m_FontEffect->GetAlpha();
		AlphaNow -= FONT_FADE_SPEED;
		if (AlphaNow < 0)
		{
			AlphaNow = 0;
			m_FontFade = FADE_IN;
		}
		break;

	case FADE_IN:
		AlphaNow = m_FontEffect->GetAlpha();
		AlphaNow += FONT_FADE_SPEED;
		if (AlphaNow > 100)
		{
			AlphaNow = 100;
			m_FontFade = FADE_OUT;
		}
		break;
	}
	m_FontEffect->SetAlpha(AlphaNow);
}

void CTutorialMaster::SelecterEF(void)
{
	if (NULL == m_PlayerSelecterEF) return;

	int nAlpha = m_PlayerSelecterEF->GetAlpha();

	if (m_SelecterMode == FADE_OUT)
	{
		nAlpha -= 2;
		if (nAlpha < 0)
		{
			nAlpha = 0;
			m_PlayerSelecterEF->SetAlpha(nAlpha);
			m_SelecterMode = FADE_IN;
		}
		m_PlayerSelecterEF->SetAlpha(nAlpha);
	}

	else
	{
		nAlpha += 2;
		if (nAlpha > 100)
		{
			nAlpha = 100;
			m_PlayerSelecterEF->SetAlpha(nAlpha);
			m_SelecterMode = FADE_OUT;
		}
		m_PlayerSelecterEF->SetAlpha(nAlpha);
	}
}

void CTutorialMaster::CreatePlayerSelecterEF(void)
{
	m_PlayerSelecterEF = CPlayerSelecterEF::Create
	(
		D3DXVECTOR3(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.0395, 0.0f), D3DXVECTOR3(45.0f, 45.0f, 0.0f),
		0, { 255,255,0 }, true, SKIP_WHITE_TEX
	);
	m_SelecterMode = FADE_IN;
}

void CTutorialMaster::SelecterScaleUp(void)
{
	if (NULL == m_PlayerSelecter) return;
	bool bHit = CHitCheck::HitPointRect(GetMousePosInWindow(), m_PlayerSelecter->GetPos(), m_PlayerSelecter->GetSize());
	if (bHit == true)
	{
		m_PlayerSelecter->SetScale(1.2);
		if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->SetScale(1.2);
	}
}

void CTutorialMaster::SelecterScaleDown(void)
{
	if (NULL == m_PlayerSelecter) return;
	bool bHit = CHitCheck::HitPointRect(GetMousePosInWindow(), m_PlayerSelecter->GetPos(), m_PlayerSelecter->GetSize());
	if (bHit == false)
	{
		m_PlayerSelecter->SetScale(1.0);
		if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->SetScale(1.0);
	}
}