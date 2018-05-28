//�t�@�C���� : GameManager.cpp
//�X�V�� : 20170424
//Author : i syuusyou
//���� : ���蔻��̏����ƃv���[���[�̃R���g���[��

#include "GameMaster.h"
#include "SceneTransition.h"
#include "scene.h"
#include "CPlayer.h"
#include "SceneTransition.h"
#include "input.h"
#include "inputmouse.h"
#include "CPlayer.h"
#include "CPlayerArrow.h"
#include "CResultScore.h"
#include "CPlayerGuild.h"
#include "CPlayerSelecter.h"
#include "CSceneTraBotton.h"
#include "CSpringPushPlayer.h"
#include "CSpringPushBall.h"
#include "CBall.h"
#include "sound.h"
#include "CResultScore.h"
#include "CJudgement.h"
#include "CPlayerHitFloorBreak.h"
#include "CPause.h"
#include "hitCheck.h"
#include "Effect.h"

#define POWER_UNI_X (1.0f)            //�����^�����x
#define ARROW_DISTANCE_FROM_PLAYER (5.0f)
#define EAGE_RANGE (15.0f)
#define PLAYER_KILL_FRAME (40)
#define CLEAR_FRAME (120)
#define COUNTDOWN_FRAME (0)
#define PLAYER_ARROW_DISTANCE (50.0f)

#define PLAYER_WIDTH (20.0f)
#define PLAYER_HEIGHT (100.0f)

#define PARTICLE_BASE_POSX (SCREEN_WIDTH * 0.4)
#define PARTICLE_BASE_POSY (SCREEN_HEIGHT * 0.4)
#define PARTICLE_BASE_RANGEX (256)
#define PARTICLE_BASE_RANGEY (144)

#define JUDGE_ALPHA_MAX_FRAME (10)

#define PARTICLE_ONCE_TIME (20)

CGameManager::CGameManager()
{
	m_Num_PlayerCanUse = 0;
	GamePadState = NULL;
}
CGameManager::~CGameManager()
{

}

void CGameManager::Init(void)
{
	m_Num_PlayerCanUse = 2;
	m_bGameStart = false;
	m_GameStep = STEP_CREATE_SCORE;
	GamePadState = NULL;
	GamePadState = new CXBOXController(1);
	m_nPlayerKill = 0;
	m_nCntGameClear = 0;
	m_nGameStartCnt = COUNTDOWN_FRAME;
	m_PlayerArrowLeft = NULL;
	m_PlayerArrowRight = NULL;
	m_pScore = NULL;
	CJudgement::Init();
	CResultScore::Init();
	CPause::Init();

	CreatePlayerSelecterEF();
	m_PlayerSelecter = NULL;

	m_ClearUI = NULL;
	m_bGamePause = false;

	m_ResetBotton = NULL;
	m_MenuBotton = NULL;

	m_ClearParticle = NULL;
	m_nParticleCounter = 0;
}

void CGameManager::Update(void)
{
	UpdateGamePause();                    //�|�[�Y����
	GameReset();                          //���Z�b�g�{�^������������
	
	if (true == m_bGamePause) return;
	ScaleMenuBotton();
	ScaleResetBotton();
	SelecterScaleDown();                //�X�P�[���_�E������

	LockPlayerArrow();                  //�v���[���[�i�s�������̌Œ�
	SelecterEF();
	if (m_pScore != NULL) m_pScore->SetScore(CResultScore::GetUsePairMin());
	
	switch (m_GameStep)
	{
	case STEP_CREATE_SCORE:
	{
		m_pScore = CScoreGame::Create(D3DXVECTOR3(SCREEN_WIDTH*0.822, SCREEN_HEIGHT*0.013, 0.0f), D3DXVECTOR3(30.0f, 42.85, 0.0f), 26.0f, 2, SCORE_TEX);
		m_ResetBotton = CFontUIScale::Create(D3DXVECTOR3(SCREEN_WIDTH*0.94, SCREEN_HEIGHT*0.04, 0.0f),D3DXVECTOR3(120, 30, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.94, SCREEN_HEIGHT*0.04, 0.0f), 255, RESET_BUTTON_TEX);
		m_ResetBotton->Update();
		m_MenuBotton = CFontUIScale::Create(D3DXVECTOR3(SCREEN_WIDTH*0.06, SCREEN_HEIGHT*0.04, 0.0f), D3DXVECTOR3(120, 30, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*0.06, SCREEN_HEIGHT*0.04, 0.0f), 255, MENU_BUTTON_TEX);
		m_MenuBotton->Update();
		m_PlayerSelecter = CPlayerSelecter::Create
		(
			D3DXVECTOR3(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.0395, 0.0f), D3DXVECTOR3(45.0f, 45.0f, 0.0f),
			255, { 255,255,255 }, false, PLAYER_SELECT_BLADE_TEX
		);
		m_GameStep = STEP_CREATE_PLAYER;
		break;
	}
	case STEP_CREATE_PLAYER:
	{
		MouseCreatePlayer();          //�}�E�X�Ńv���[���[��z�u
		GameCanStart();
		break;
	}

	case STEP_DRAG_PLAYER:
	{
		MouseDragPlayer();        //�}�E�X�Ńv���[���[���h���b�N����
		break;
	}

	case STEP_COUNT_DOWN:
		CountDown();
		break;

	case STEP_GAME_CAN_START:
	{
		GameStart();                            //�Q�[�����X�^�[�g
		CSpringPushPlayer::Update();
		CSpringPushBall::Update();
		if(m_nPlayerKill > 8) CJudgement::Update();                     //���ݕ]��
		CPlayerHitFloorBreak::Update();
		GameFail();
		GamePlayerKill();
		GamePlayerReset();
		GameClear();
		break;
	}

	case STEP_CLEAR:
		ShowClear();
		break;

	}
}

void CGameManager::Uninit(void)
{
	delete GamePadState;
	GamePadState = NULL;
	m_pScore = NULL;

	m_bGamePause = false;
}

void CGameManager::MouseDragPlayer(void)
{
	D3DXVECTOR3 MousePosition = GetMousePosInWindow();

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

			//�v���[���[�z�u�L�����Z��
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_RIGHT)) 
			{
				pPlayer->Uninit();
				m_GameStep = STEP_CREATE_PLAYER;                     //�v���[���[create�i�K�ɖ߂�
				if (m_Num_PlayerCanUse == 1) DeletePlayerArrow();

				CreatePlayerSelecterEF();

				DeletePlayerGuild();             //�v���[���[�K�C�h�폜

				return; 
			}

			//�v���[���[�z�u�m�F
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
			{
				pPlayer->SetMouseLock(false);
				m_Num_PlayerCanUse--;                      //�v���[���[���鑍��������
				m_GameStep = STEP_CREATE_PLAYER;           //�v���[���[�ړ��������߂�i�K�Ɉڍs

				PlaySound(SE_SET_STONE_PILLAR);         //���ʉ��Đ�

				CreatePlayerSelecterEF();

				DeletePlayerGuild();             //�v���[���[�K�C�h�폜
			}
			return;
		}
	}
}

void CGameManager::MouseCreatePlayer(void)
{
	bool PlayerCanNotCreate = m_Num_PlayerCanUse <= 0;
	if (PlayerCanNotCreate == true) return;           //�v���[���[��������ȏ���Ȃ�

	SelecterScaleUp();                                //�X�P�[���A�b�v����

	//�v���[���[�����
	int nPriority = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
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
			if(HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CPlayer::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f), PLAYER_TEX);  //�v���[���[���
					m_GameStep = STEP_DRAG_PLAYER;             //�v���[���[�z�u�Ɉڍs

					PlaySound(SE_DRAP_PILLAR);

					if (m_Num_PlayerCanUse == 1)
					{
						CreatePlayerArrow();               //�������
					}

					if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->Uninit();
					m_PlayerSelecterEF = NULL;

				}
			}
		}
	}

	if(m_Num_PlayerCanUse == 1)
	{
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_RIGHT) == false) return;

		int nPriority = CPlayer::GetPriority();
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			CScene *pScene = NULL;
			pScene = CScene::GetScene(nCnt, nPriority);
			if (pScene == NULL) continue;

			//���̃V�[�����v���[���[�����A�C�R���̎�
			if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
			
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);
			if (pPlayer == NULL) continue;
			pPlayer->Uninit();
			pPlayer = NULL;
			m_Num_PlayerCanUse = 2;                        //�ݒu���߂�
			DeletePlayerArrow();                           //�v���[���[���폜
			return;

		}
	}
}

void CGameManager::CreatePlayerArrow(void)
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
	if(PlayerPos[0].x > PlayerPos[1].x)
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
	
	m_PlayerArrowLeft = CPlayerArrow::Create(LeftPos, D3DXVECTOR3(50.0f,50.0f,0.0f), ARROW_TEX);
	m_PlayerArrowRight = CPlayerArrow::Create(RightPos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), ARROW_TEX);
	m_PlayerArrowLeft->SetUV(D3DXVECTOR2(1.0f,0.0f));
	m_PlayerArrowLeft->SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));
	m_PlayerArrowLeft->Update();
}

void CGameManager::DeletePlayerArrow(void)
{
	if(NULL != m_PlayerArrowLeft)
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

void CGameManager::DeletePlayerGuild(void)
{
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

void CGameManager::LockPlayerArrow(void)
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

void CGameManager::GameStart(void)
{
	int nPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//�v���[���[������
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer->GetMoveDirection() == false) pPlayer->AddPowerX(-POWER_UNI_X);
			else pPlayer->AddPowerX(POWER_UNI_X);
		}
	}
}

void CGameManager::GameCanStart(void)
{
	if (m_Num_PlayerCanUse > 0) return;

	//�J�E���g�_�E�������
	int nCountDown = m_nGameStartCnt / 60;
	m_GameStep = STEP_COUNT_DOWN;

	if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->Uninit();
	m_PlayerSelecterEF = NULL;
}

void CGameManager::CountDown(void)
{
	m_nGameStartCnt--;                       //�X�^�[�g�J�E���g�_�E��
	int nCountDown = m_nGameStartCnt / 60;

	//�J�E���g�_�E���ɒl���
	if (m_nGameStartCnt > 0) return;

	//�Q�[�����n�߂����Ԃɐݒ�
	m_GameStep = STEP_GAME_CAN_START;
	m_bGameStart = true;
	CResultScore::IncrementPairMin();
	m_nGameStartCnt = COUNTDOWN_FRAME;

	DeletePlayerGuild();             //�v���[���[�K�C�h�폜

	DeletePlayerArrow();             //�v���[���[���̍폜
}

void CGameManager::GameFail(void)
{
	int nFailTimes = 0;            //���s��
	int nPlayerPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPriority);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
		if (pPlayer == NULL) continue;

		//�ǍۂƂ̔���
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerPosOld = pPlayer->GetPosOld();
		
		if (PlayerPos == PlayerPosOld || PlayerOutRange() == true)
		{
			nFailTimes++;
		}
	}
	if (nFailTimes == 2) m_nPlayerKill++;
} 

void CGameManager::GamePlayerKill(void)
{
	if (m_nPlayerKill <= PLAYER_KILL_FRAME) return;

	int nPlayerPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPriority);
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

void CGameManager::GamePlayerReset(void)
{
	int nPlayerNum = 0;            //���s��
	int nPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		nPlayerNum++;
	}

	//�v���[���[�̍Ĕz�u�񐔂�0�ȏ�̎�
	if (nPlayerNum != 0) return;
	m_Num_PlayerCanUse = 2;
	m_bGameStart = false;
	m_GameStep = STEP_CREATE_PLAYER;
	m_nPlayerKill = 0;
	CJudgement::ResetCreateFlag();

	CreatePlayerSelecterEF();
}

void CGameManager::GameClear(void)
{
	int nBallNum = 0;
	int nPlayerNum = 0;
	
	int nPriority = CBall::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_BALL) continue;
		CBall* pBall = dynamic_cast<CBall*>(pScene);
		if (NULL == pBall) continue;
		if (pBall->GetDeadFlag() == true) continue;
		nBallNum++;
	}

	nPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		nPlayerNum++;
	}

	if (nBallNum == 0 && nPlayerNum == 0)
	{
		m_GameStep = STEP_CLEAR;
		m_ClearUI = CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.5,0.0f), D3DXVECTOR3(532,65.5,0.0f),0, CLEAR_TEX);
		m_ClearUI->Update();
		if (NULL == m_ClearParticle)
		{
			m_ClearParticle = CParticle::Create(635.000, 360.000, 0.000, 0.000, 40.300, 40.300, 40.300, -0.009, -0.009, -0.009, 4.200, 4.200, 4.200, 0.000, 0.000, 0.000, 21, 60.000, -0.460, -1.400, 0.00, 0.00, 0.00, 1.00, 0.000, 1.900, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 180.000, 0.000, 1.00, 1.00, 1.00, 0.00, 0, -1, PARTICLE_BASE_TEX);
			m_ClearParticle->SetStopFlag(true);
		}
		PlaySound(SE_CLEAR);
	}
}

void CGameManager::ShowClear(void)
{
	//���o������
	m_nCntGameClear++;                       //���o���ԃJ�E���g�A�b�v

	//�ԉ΂̉��o
	if(NULL != m_ClearParticle)
	{
		D3DXVECTOR3 ParticlePos;
		ParticlePos.x = PARTICLE_BASE_POSX + rand()% PARTICLE_BASE_RANGEX;
		ParticlePos.y = PARTICLE_BASE_POSY + rand() % PARTICLE_BASE_RANGEY;
		ParticlePos.z = 0.0f;

		m_ClearParticle->SetPosXYZ(ParticlePos);
		CEffect::Load(PARTICLE_BASE_TEX);

		m_nParticleCounter--;
		if(m_nParticleCounter < 0)
		{
			m_ClearParticle->SetStopFlag(false);
			m_nParticleCounter = PARTICLE_ONCE_TIME;
		}

		else m_ClearParticle->SetStopFlag(true);
	}

	//�N���A�t�H���g�������オ��
	int nAlpha = m_ClearUI->GetAlpha();
	nAlpha += 5;
	if (nAlpha > 255) nAlpha = 255;
	m_ClearUI->SetAlpha(nAlpha);

	//�N���A���o�I��->���U���g��
	if (m_nCntGameClear < CLEAR_FRAME) return;
	m_ClearUI = NULL;
	m_ClearParticle = NULL;
	CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_RESULT);
}

void CGameManager::GameReset(void)
{
	if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT) && HitResetBotton() == true)
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_GAME);
	}
}

void CGameManager::SetScorePointer(CScoreGame *pScore)
{
	m_pScore = pScore;
}

void CGameManager::SelecterEF(void)
{
	if (NULL == m_PlayerSelecterEF) return;

	int nAlpha = m_PlayerSelecterEF->GetAlpha();

	if(m_SelecterMode == FADE_OUT)
	{
		nAlpha -= 2;
		if(nAlpha < 0)
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

void CGameManager::UpdateGamePause(void)
{
	CPause::HitCheckMouseAndPauseObj();
	if (CPause::GetHelpFlag() == true) return;

	bool bMousePause = false;
	if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
	{
		if (HitMenuBotton() == true && false == m_bGamePause)
		{
			bMousePause = true;
		}
	}

	if (CSceneTransition::GetInputKeyboard()->GetKeyTrigger(DIK_ESCAPE) || bMousePause)
	{
		if (false == m_bGamePause)                     //��|�[�Y���
		{
			CPause::CreatePauseBar();                               //�|�[�Y�o�[���
			m_bGamePause = true;
		}

		else                                          //�|�[�Y���
		{
			CPause::DelectAllPauseObj();                            //�|�[�Y�o�[�폜
			m_bGamePause = false;
		}
	}

	if (false == m_bGamePause) return;
}

bool CGameManager::HitMenuBotton(void)
{
	if (NULL == m_MenuBotton) return false;

	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	D3DXVECTOR3 Pos = m_MenuBotton->GetPos();
	D3DXVECTOR3 Size = m_MenuBotton->GetSize();

	bool bHit = CHitCheck::HitPointRect(MousePos, Pos,Size);

	return bHit;
}

bool CGameManager::HitResetBotton(void)
{
	if (NULL == m_ResetBotton) return false;

	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	D3DXVECTOR3 Pos = m_ResetBotton->GetPos();
	D3DXVECTOR3 Size = m_ResetBotton->GetSize();

	bool bHit = CHitCheck::HitPointRect(MousePos, Pos, Size);

	return bHit;
}

void CGameManager::ScaleMenuBotton(void)
{
	if (NULL == m_MenuBotton) return;

	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	D3DXVECTOR3 Pos = m_MenuBotton->GetPos();
	D3DXVECTOR3 Size = m_MenuBotton->GetSize();

	bool bHit = CHitCheck::HitPointRect(MousePos, Pos, Size);

	if (bHit == true)
	{
		m_MenuBotton->SetScale(1.2);
	}
	else
	{
		m_MenuBotton->SetScale(1.0);
	}
}

void CGameManager::ScaleResetBotton(void)
{
	if (NULL == m_ResetBotton) return;

	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	D3DXVECTOR3 Pos = m_ResetBotton->GetPos();
	D3DXVECTOR3 Size = m_ResetBotton->GetSize();

	bool bHit = CHitCheck::HitPointRect(MousePos, Pos, Size);

	if (bHit == true)
	{
		m_ResetBotton->SetScale(1.2);
	}
	else
	{
		m_ResetBotton->SetScale(1.0);
	}
}

void CGameManager::CreatePlayerSelecterEF(void)
{
	m_PlayerSelecterEF = CPlayerSelecterEF::Create
	(
		D3DXVECTOR3(SCREEN_WIDTH*0.15, SCREEN_HEIGHT*0.0395, 0.0f), D3DXVECTOR3(45.0f, 45.0f, 0.0f),
		0, { 255,255,0 }, true, SKIP_WHITE_TEX
	);
	m_SelecterMode = FADE_IN;
}

bool CGameManager::PlayerOutRange(void)
{
	bool bPlayerOutRange = false;

	int nPlayerPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPriority);
		if (pScene == NULL) continue;

		//�v���[���[����
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		
		D3DXVECTOR3 PlayerPos = pScene->GetPos();
		if (PlayerPos.y > SCREEN_HEIGHT) bPlayerOutRange = true;
	}

	return bPlayerOutRange;
}

void CGameManager::SelecterScaleUp(void)
{
	if (NULL == m_PlayerSelecter) return;
	bool bHit = CHitCheck::HitPointRect(GetMousePosInWindow(), m_PlayerSelecter->GetPos(), m_PlayerSelecter->GetSize());
	if(bHit == true)
	{
		m_PlayerSelecter->SetScale(1.2);
		if(NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->SetScale(1.2);
	}
}

void CGameManager::SelecterScaleDown(void)
{
	if (NULL == m_PlayerSelecter) return;
	bool bHit = CHitCheck::HitPointRect(GetMousePosInWindow(), m_PlayerSelecter->GetPos(), m_PlayerSelecter->GetSize());
	if (bHit == false)
	{
		m_PlayerSelecter->SetScale(1.0);
		if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->SetScale(1.0);
	}
}