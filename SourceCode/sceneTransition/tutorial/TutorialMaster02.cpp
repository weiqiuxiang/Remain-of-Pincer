//ファイル名 : GameManager.cpp
//更新日 : 20170424
//Author : i syuusyou
//説明 : 当り判定の処理とプレーヤーのコントロール

#include "TutorialMaster02.h"
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
#include "CFontUIEffect.h"
#include "CSpringPushBall.h"
#include "CSpringPushPlayer.h"
#include "sound.h"
#include "CJudgement.h"

#define POWER_UNI_X (1.0f)            //等速運動速度
#define ARROW_DISTANCE_FROM_PLAYER (5.0f)
#define EAGE_RANGE (15.0f)
#define PLAYER_KILL_FRAME (100)
#define TUTORIAL_START_FRAME (60)

#define UI_DRAG1_XMOVE (800)
#define UI_DRAG1_YMOVE (240)

#define UI_DRAG2_XMOVE (500)
#define UI_DRAG2_YMOVE (500)

#define UI_DRAG3_XMOVE (400)
#define UI_DRAG3_YMOVE (200)

#define UI_DRAG4_XMOVE (200)
#define UI_DRAG4_YMOVE (300)

#define COUNT_DOWN_FRAME (120)
#define PLAYER_ARROW_DISTANCE (50.0f)

#define FONT_FADE_SPEED (2)

void CTutorialMaster02::Init(void)
{
	m_Num_PlayerCanUse = 2;
	m_TutorialStartTime = 0;
	m_bGameStart = false;
	m_GameStep = STEP_NONE;
	m_nPlayerKill = 0;
	m_GameStartCountDown = NULL;
	m_CountDownFont = NULL;
	m_nGameStartCnt = COUNT_DOWN_FRAME;
	m_PlayerArrowLeft = NULL;
	m_PlayerArrowRight = NULL;
	m_FontEffect = NULL;
	m_FontFade = FADE_OUT;
	m_MakeFontTimeFlag = false;
	CJudgement::Init();
	CResultScore::Init();

	m_PlayerSelecterEF = NULL;
}

void CTutorialMaster02::Update(void)
{
	LockPlayerArrow();                  //プレーヤー進行方向矢印の固定
	SelecterEF();
	TutorialSkip();                 //チュートリアルスキップ
	switch (m_GameStep)
	{
	case STEP_NONE:
		TutorialStart();
		break;
	case STEP_CREATE_PLAYER1:
	{
		MouseCreatePlayer1();          //マウスでプレーヤーを配置
		break;
	}

	case STEP_DRAG_PLAYER1:
	{
		MouseDragPlayer1();        //マウスでプレーヤーをドラックする
		break;
	}

	case STEP_CREATE_PLAYER2:
	{
		MouseCreatePlayer2();          //マウスでプレーヤーを配置
		break;
	}

	case STEP_DRAG_PLAYER2:
	{
		MouseDragPlayer2();          //マウスでプレーヤーを配置
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
		GameStart();                            //ゲームをスタート
		CSpringPushPlayer::Update();
		CSpringPushBall::Update();
		if (m_nPlayerKill > 8) CJudgement::Update();
		GameFail();
		GamePlayerKill();
		GamePlayerReset();
		break;
	}
	}
}

void CTutorialMaster02::Uninit(void)
{
	m_PlayerArrowLeft = NULL;
	m_PlayerArrowRight = NULL;
}

void CTutorialMaster02::MouseDragPlayer1(void)
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
			//NULL確認
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;

			//マウスにロックされているかどうか確認
			bool mouseLock = pPlayer->GetMouseLock();
			if (mouseLock == true) pPlayer->SetPosition(MousePosition);
			else continue;         //ロックしていない

			//プレーヤー配置確認
			if (MousePosInClickZone() == false) continue;
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
			{
				pPlayer->SetMouseLock(false);
				m_GameStep = STEP_CREATE_PLAYER2;           //プレーヤー移動方向決める段階に移行

				//クリア
				ClearFontEffect();
				m_MakeFontTimeFlag = false;
				DeleteAllTutorialUI();                  //削除
				//作成
				CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89, SCREEN_HEIGHT*0.74, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
				m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89, SCREEN_HEIGHT*0.74, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
				CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.8, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
				CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);

				PlaySound(SE_SET_STONE_PILLAR);                            //サウンド再生

				m_PlayerSelecterEF = CPlayerSelecterEF::Create
				(
					D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(10, 50.0f, 0.0f),
					0, { 255,255,0 }, true, PLAYER_TEX
				);
				m_SelecterMode = FADE_IN;
			}
			return;
		}
	}
}

void CTutorialMaster02::MouseCreatePlayer1(void)
{
	bool PlayerCanNotCreate = m_Num_PlayerCanUse <= 0;
	if (PlayerCanNotCreate == true) return;           //プレーヤーもうそれ以上作れない

	FontEffect();                        //フォントエフェクト

	//プレーヤーを作る
	int PlayerSelectPri = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, PlayerSelectPri);
		if (pScene == NULL) continue;

		//このシーンがプレーヤー生成アイコンの時
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_SELECTER)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			D3DXVECTOR3 PlayerSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float PlayerLeft = PlayerPos.x - PlayerSize.x*0.5;
			float PlayerRight = PlayerPos.x + PlayerSize.x*0.5;
			float PlayerTop = PlayerPos.y - PlayerSize.y*0.5;
			float PlayerBottom = PlayerPos.y + PlayerSize.y*0.5;

			bool HitX = (MousePos.x <= PlayerRight) && (MousePos.x >= PlayerLeft);
			bool HitY = (MousePos.y <= PlayerBottom) && (MousePos.y >= PlayerTop);

			//判定成立
			if (HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CPlayer::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(20, 100.0f, 0.0f), PLAYER_TEX);  //プレーヤー作る
					m_Num_PlayerCanUse--;                      //プレーヤー作れる総数が減る
					m_GameStep = STEP_DRAG_PLAYER1;             //プレーヤー配置に移行

					PlaySound(SE_DRAP_PILLAR);        //サウンド再生

					//クリア
					ClearFontEffect();
					m_MakeFontTimeFlag = false;
					DeleteAllTutorialUI();                  //削除
					//作成
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

void CTutorialMaster02::MouseDragPlayer2(void)
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
			//NULL確認
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;

			//マウスにロックされているかどうか確認
			bool mouseLock = pPlayer->GetMouseLock();
			if (mouseLock == true) pPlayer->SetPosition(MousePosition);
			else continue;         //ロックしていない

			//プレーヤー配置確認
			if (MousePosInClickZone() == false) continue;
			if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
			{
				pPlayer->SetMouseLock(false);
				m_GameStep = STEP_CREATE_COUNT;           //プレーヤー移動方向決める段階に移行

				DeletePlayerArrow();          //矢印削除
				DeleteAllTutorialUI();        //チュートリアルUI全削除

				PlaySound(SE_SET_STONE_PILLAR);                            //サウンド再生
			}
			return;
		}
	}
}

void CTutorialMaster02::MouseCreatePlayer2(void)
{
	bool PlayerCanNotCreate = m_Num_PlayerCanUse <= 0;
	if (PlayerCanNotCreate == true) return;           //プレーヤーもうそれ以上作れない

	FontEffect();

	//プレーヤーを作る
	int nPlayerSelectPri = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerSelectPri);
		if (pScene == NULL) continue;

		//このシーンがプレーヤー生成アイコンの時
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_SELECTER)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			D3DXVECTOR3 PlayerSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float PlayerLeft = PlayerPos.x - PlayerSize.x*0.5;
			float PlayerRight = PlayerPos.x + PlayerSize.x*0.5;
			float PlayerTop = PlayerPos.y - PlayerSize.y*0.5;
			float PlayerBottom = PlayerPos.y + PlayerSize.y*0.5;

			bool HitX = (MousePos.x <= PlayerRight) && (MousePos.x >= PlayerLeft);
			bool HitY = (MousePos.y <= PlayerBottom) && (MousePos.y >= PlayerTop);

			//判定成立
			if (HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CPlayer::Create(D3DXVECTOR3(MousePos.x, MousePos.y, 0.0f), D3DXVECTOR3(20, 100.0f, 0.0f), PLAYER_TEX);  //プレーヤー作る
					m_Num_PlayerCanUse--;                      //プレーヤー作れる総数が減る
					m_GameStep = STEP_DRAG_PLAYER2;      //プレーヤー方向誘導に移行

					PlaySound(SE_DRAP_PILLAR);        //サウンド再生

					//クリア
					ClearFontEffect();
					m_MakeFontTimeFlag = false;
					DeleteAllTutorialUI();                  //削除
					//作成
					CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.85, 0.0f), D3DXVECTOR3(370, 50, 0.0f), 255, { 100,100,200 }, false, FONT_EXPLAIN_PLAYER_SKY_TEX);
					CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_SETPLAYER_TEX);
					m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.74 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(157.5, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_SETPLAYER_TEX);
					CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.8 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, SKIP_TU_ARROW_TEX);
					CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9 - UI_DRAG2_XMOVE, SCREEN_HEIGHT*0.9 - UI_DRAG2_YMOVE, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);

					CreatePlayerArrow();              //方向矢印を作る

					if (NULL != m_PlayerSelecterEF) m_PlayerSelecterEF->Uninit();
					m_PlayerSelecterEF = NULL;
				}
			}
		}
	}
}

void CTutorialMaster02::GameStart(void)
{
	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//プレーヤーを検索
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer->GetMoveDirection() == false) pPlayer->AddPowerX(-POWER_UNI_X);
			else pPlayer->AddPowerX(POWER_UNI_X);
		}
	}
}

void CTutorialMaster02::GameCanStart(void)
{
	if (m_Num_PlayerCanUse > 0) return;
	
	//カウントダウンを作る
	m_GameStartCountDown = CScoreGame::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(37.06f, 53.3f, 0.0f), 38.0f, 1, SCORE_TEX);
	m_CountDownFont = CSceneTraBotton::Create(D3DXVECTOR3(SCREEN_WIDTH*0.4, SCREEN_HEIGHT*0.935, 0.0f), D3DXVECTOR3(320.0f, 47.3f, 0.0f), COUNT_DOWN_TEX);
	int nCountDown = m_nGameStartCnt / 60;
	m_GameStartCountDown->SetScore(nCountDown);
	m_GameStartCountDown->Update();
	m_GameStep = STEP_COUNT_DOWN;
	DeleteAllAllTutorialUI();               //チュートリアルUI全削除
}

void CTutorialMaster02::CountDown(void)
{
	m_nGameStartCnt--;                       //スタートカウントダウン
	int nCountDown = m_nGameStartCnt / 60;
	if (NULL == m_GameStartCountDown) return;    //カウントダウンNULLチェック
	if (NULL == m_CountDownFont) return;
	m_GameStartCountDown->SetScore(nCountDown);
	if (m_nGameStartCnt > 0) return;

	m_GameStep = STEP_GAME_CAN_START;
	m_bGameStart = true;
	CResultScore::IncrementPairMin();
	m_nGameStartCnt = COUNT_DOWN_FRAME;

	//表示スコア削除
	m_GameStartCountDown->Uninit();
	m_GameStartCountDown = NULL;
	m_CountDownFont->Uninit();
	m_CountDownFont = NULL;

	DeletePlayerGuild();;                             //プレーヤーガイド削除
}

void CTutorialMaster02::GameFail(void)
{
	int nFailTimes = 0;            //失敗回数
	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//プレーヤー検索
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
		if (pPlayer == NULL) continue;

		//壁際との判定
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerPosOld = pPlayer->GetPosOld();

		if (PlayerPos == PlayerPosOld)
		{
			nFailTimes++;
		}
	}
	if (nFailTimes == 2) m_nPlayerKill++;
}

void CTutorialMaster02::GamePlayerKill(void)
{
	if (m_nPlayerKill <= PLAYER_KILL_FRAME) return;

	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//プレーヤー検索
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
		if (pPlayer == NULL) continue;

		pPlayer->ChangeAlpha(-5);
		int PlayerAlpha = pPlayer->GetAlpha();
		if (PlayerAlpha == 0)
		{
			CResultScore::CheckKillEnemyOneTurnMax();    //1ターン殺した敵の数は最大かどうか
			pPlayer->Uninit();
		}
	}
}

void CTutorialMaster02::GamePlayerReset(void)
{
	int nPlayerNum = 0;            //失敗回数
	int nPlayerPri = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPri);
		if (pScene == NULL) continue;

		//プレーヤー検索
		if (pScene->GetObjType() != CScene::OBJTYPE_PLAYER) continue;
		nPlayerNum++;
	}

	//プレーヤーの再配置回数は0以上の時
	if (nPlayerNum != 0) return;
	CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
}

void CTutorialMaster02::TutorialSkip(void)
{
	int nTraBottonPri = CSceneTraBotton::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nTraBottonPri);
		if (pScene == NULL) continue;

		//リセットボタン検索
		if (pScene->GetObjType() == CScene::OBJTYPE_RESET_BOTTON)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
			D3DXVECTOR3 BottonPos = pScene->GetPos();
			D3DXVECTOR3 BottonSize = pScene->GetSize();
			D3DXVECTOR3 MousePos = GetMousePosInWindow();

			float BottonLeft = BottonPos.x - BottonSize.x*0.5;
			float BottonRight = BottonPos.x + BottonSize.x*0.5;
			float BottonTop = BottonPos.y - BottonSize.y*0.5;
			float BottonBottom = BottonPos.y + BottonSize.y*0.5;

			bool HitX = (MousePos.x <= BottonRight) && (MousePos.x >= BottonLeft);
			bool HitY = (MousePos.y <= BottonBottom) && (MousePos.y >= BottonTop);

			//判定成立
			if (HitX && HitY)
			{
				if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
				{
					CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
				}
			}
		}
	}
}

void CTutorialMaster02::TutorialStart(void)
{
	m_TutorialStartTime++;
	if (m_TutorialStartTime < TUTORIAL_START_FRAME) return;

	//UIオブジェクトを生成
	if (m_MakeFontTimeFlag == false)
	{
		CTutorialBlack::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 120, SKIP_BLACK_TEX);
		CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.85, 0.0f), D3DXVECTOR3(400, 50, 0.0f), 255, { 100,100,200 },false, FONT_EXPLAIN_SPRING_TEX);
		CMouseClickZone::Create(D3DXVECTOR3(FLOOR_BLOCK_SIZE*26 + FLOOR_BLOCK_HALFSIZE, FLOOR_BLOCK_SIZE * 12, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE * 3.5, FLOOR_BLOCK_SIZE * 2.5, 0.0f), 60, SKIP_WHITE_TEX);
		CMouseClickZone::Create(D3DXVECTOR3(FLOOR_BLOCK_SIZE + FLOOR_BLOCK_HALFSIZE, FLOOR_BLOCK_SIZE * 21, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE * 3.5, FLOOR_BLOCK_SIZE * 2.5, 0.0f), 60, SKIP_WHITE_TEX);
		CMouseClickZone::Create(D3DXVECTOR3(FLOOR_BLOCK_SIZE*41 + FLOOR_BLOCK_HALFSIZE, FLOOR_BLOCK_SIZE * 21, 0.0f), D3DXVECTOR3(FLOOR_BLOCK_SIZE * 3.5, FLOOR_BLOCK_SIZE * 2.5, 0.0f), 60, SKIP_WHITE_TEX);
		CreateFontEffect();
		m_MakeFontTimeFlag = true;
	}

	FontEffect();

	//次のステップ移行
	if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
	{
		m_GameStep  = STEP_CREATE_PLAYER1;

		//フォント関連クリア
		ClearFontEffect();
		m_MakeFontTimeFlag = false;
		DeleteAllTutorialUI();                  //削除

		CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89, SCREEN_HEIGHT*0.74, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
		m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.89, SCREEN_HEIGHT*0.74, 0.0f), D3DXVECTOR3(300, 37.5, 0.0f), 150, { 187,127,90 }, true, SKIP_TU_GETPLAYER_TEX);
		CFontUI::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.8, 0.0f), D3DXVECTOR3(50, 50, 0.0f),255, SKIP_TU_ARROW_TEX);
		CMouseClickZone::Create(D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 60, SKIP_WHITE_TEX);

		m_PlayerSelecterEF = CPlayerSelecterEF::Create
		(
			D3DXVECTOR3(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(10, 50.0f, 0.0f),
			0, { 255,255,0 }, true, PLAYER_TEX
		);
		m_SelecterMode = FADE_IN;
	}
}

void CTutorialMaster02::DeleteAllTutorialUI(void)
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

void CTutorialMaster02::DeleteAllAllTutorialUI(void)
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

bool CTutorialMaster02::MousePosInClickZone(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	int nPriority = CMouseClickZone::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//リセットボタン検索
		if (pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_MOUSECLICKZONE)
		{
			//マウス座標とプレーヤー生成アイコンの当り判定
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

void CTutorialMaster02::LockPlayerArrow(void)
{
	if (NULL == m_PlayerArrowLeft) return;
	if (NULL == m_PlayerArrowRight) return;

	//プレーヤーを探す
	D3DXVECTOR3 PlayerPos[2];
	int PlayerNum = 0;
	int nPriority = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//このシーンがプレーヤー生成アイコンの時
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			PlayerPos[PlayerNum] = pScene->GetPos();
			PlayerNum++;
			if (PlayerNum == 2) break;
		}
	}

	//位置設定
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

void CTutorialMaster02::CreatePlayerArrow(void)
{
	//プレーヤーを探す
	D3DXVECTOR3 PlayerPos[2];
	int PlayerNum = 0;
	int nPriority = CPlayerSelecter::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//このシーンがプレーヤー生成アイコンの時
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
	m_PlayerArrowLeft->SetUV(D3DXVECTOR2(1.0f, 0.0f));
	m_PlayerArrowLeft->SetUVWH(D3DXVECTOR2(-1.0f, 1.0f));
	m_PlayerArrowLeft->Update();
}

void CTutorialMaster02::DeletePlayerArrow(void)
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

void CTutorialMaster02::DeletePlayerGuild(void)
{
	//プレーヤーガイド削除
	int PlayerGuildPri = CPlayerGuild::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, PlayerGuildPri);
		if (pScene == NULL) continue;

		//プレーヤーを検索
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_GUILD)
		{
			CPlayerGuild *pPlayerGuild = dynamic_cast <CPlayerGuild *> (pScene);
			if (pPlayerGuild == NULL) continue;
			pPlayerGuild->Uninit();
		}
	}
}

void CTutorialMaster02::FontEffect(void)
{
	if (NULL == m_FontEffect) return;
	int AlphaNow = 0;
	switch(m_FontFade)
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

void CTutorialMaster02::CreateFontEffect(void)
{
	CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(270, 50, 0.0f), 150, { 187,127,90 },true, FONT_NEXT_TEX);
	m_FontEffect = CFontUIEffect::Create(D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.9, 0.0f), D3DXVECTOR3(270, 50, 0.0f), 150, { 187,127,90 },true, FONT_NEXT_TEX);
}

void CTutorialMaster02::ClearFontEffect(void)
{
	m_FontEffect = NULL;
	m_FontFade = FADE_OUT;
}

void CTutorialMaster02::SelecterEF(void)
{
	if (NULL == m_PlayerSelecterEF) return;

	int nAlpha = m_PlayerSelecterEF->GetAlpha();

	if (m_SelecterMode == FADE_OUT)
	{
		nAlpha -= 5;
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
		nAlpha += 5;
		if (nAlpha > 255)
		{
			nAlpha = 255;
			m_PlayerSelecterEF->SetAlpha(nAlpha);
			m_SelecterMode = FADE_OUT;
		}
		m_PlayerSelecterEF->SetAlpha(nAlpha);
	}
}