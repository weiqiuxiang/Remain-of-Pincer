#include "CStageMaster.h"
#include "hitCheck.h"
#include "SceneTransition.h"
#include "CGameStage.h"
#include "CFontUI.h"
#include "CScrollBar.h"
#include "CResultScore.h"

#define SCALE_VALUE (1.2)
#define TIME_SCALE (30)
#define STAGE_INTERVAL (SCREEN_HEIGHT*0.22)

#define STAGE_FONT_OFFSET_X (60)
#define STAGE_FONT_WIDTH (268*0.7)
#define STAGE_FONT_HEIGHT (73*0.7)

#define STAGE_NUMBER_OFFSET_X (90)
#define STAGE_RANK_OFFSET_X (180)
#define STAGE_RANK_OFFSET_Y (70)

#define STAGE_RANK_WIDTH (100)
#define STAGE_RANK_HEIGHT (100)

#define STAGE_CLEAR_FONT_OFFSET_X (180)
#define STAGE_CLEAR_FONT_OFFSET_Y (70)

#define STAGE_CLEAR_FONT_WIDTH (184)
#define STAGE_CLEAR_FONT_HEIGHT (54)

#define NO_HIT_ANY_STAGE_FRAME (-1)

D3DXVECTOR3   CStageMaster::m_ScrollBarPos = { 0.0f,0.0f,0.0f };
float         CStageMaster::m_ScrollBarHeight = 0.0f;
D3DXVECTOR3   CStageMaster::m_SelectBarPos = { 0.0f,0.0f,0.0f };
float         CStageMaster::m_SelectBarHeight = 0.0f;
D3DXVECTOR3   CStageMaster::m_ScrollBarPosNow = { 0.0f,0.0f,0.0f };

CTitleTraBotton* CStageMaster::m_StageTraBotton[STAGE_MAX] = {};
CFontUIScale* CStageMaster::m_Rank[STAGE_MAX] = {};
CFontUIScale* CStageMaster::m_StageFont[STAGE_MAX] = {};
CScoreScale* CStageMaster::m_StageNumber[STAGE_MAX] = {};
CFontUIScale* CStageMaster::m_ClearFont[STAGE_MAX] = {};
CFontUI* CStageMaster::m_BarTop = NULL;
CFontUI* CStageMaster::m_BarBottom = NULL;

void CStageMaster::Init(void)
{
	m_ScrollBarPos = D3DXVECTOR3(SCREEN_WIDTH*0.8,SCREEN_HEIGHT*0.2,0.0f);
	m_ScrollBarHeight = SCREEN_HEIGHT*0.6;
	m_SelectBarPos = D3DXVECTOR3(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.2, 0.0f);
	m_SelectBarHeight = STAGE_INTERVAL * STAGE_MAX;
	m_ScrollBarPosNow = m_ScrollBarPos;

	for (int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++) 
	{
		m_StageTraBotton[nStageNum] = NULL;
		m_Rank[nStageNum] = NULL;
		m_StageFont[nStageNum] = NULL;
		m_StageNumber[nStageNum] = NULL;
		m_ClearFont[nStageNum] = NULL;
	}

	m_BarTop = NULL;
	m_BarBottom = NULL;
}

void CStageMaster::Update(void)
{
	int nStageNum = HitCheckMouseAndTitleObj();     //マウスとタイトルオブジェクトの当り判定
	TraBottonScaleUp(nStageNum);                                 //当り判定があったタイトルオブジェクトのスケールアップ
	TraBottonScaleDownNotHit(nStageNum);                         //当り判定がないタイトルオブジェのスケール減少
	Transition(nStageNum);                                       //マウスの左クリック判定

	ScrollBarLeftClick();              //スクロールバーに対するマウス左クリック判定
	ScrollBarMouseWheel();             //スクロールバーに対するマウスホイールの値判定
	ClickBarTopAndBottom();            //スクロールバーに対する上下ボタンを押す判定
	SetSelectBarPos();                 //選択バーの位置設定
	RightClickReturnTitle();           //タイトルに戻る判定
}

void CStageMaster::Uninit(void)
{
	for (int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++)
	{
		m_StageTraBotton[nStageNum] = NULL;
		m_Rank[nStageNum] = NULL;
		m_StageFont[nStageNum] = NULL;
		m_StageNumber[nStageNum] = NULL;
		m_ClearFont[nStageNum] = NULL;
	}

	m_BarTop = NULL;
	m_BarBottom = NULL;
}

int CStageMaster::HitCheckMouseAndTitleObj(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	for (int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++)
	{
		if (NULL == m_StageTraBotton[nStageNum]) continue;   //NULLチェック
		bool hitCheck = CHitCheck::HitPointRect(MousePos, m_StageTraBotton[nStageNum]->GetPos(), m_StageTraBotton[nStageNum]->GetSize());
		if (hitCheck) return nStageNum;
		else continue;
	}

	return NO_HIT_ANY_STAGE_FRAME;
}

void CStageMaster::TraBottonScaleUp(int nStageNum)
{
	if (nStageNum == NO_HIT_ANY_STAGE_FRAME) return;

	//NULLチェック
	if (NULL == m_StageTraBotton[nStageNum]) return;
	if (NULL == m_Rank[nStageNum]) return;
	if (NULL == m_StageFont[nStageNum]) return;
	if (NULL == m_StageNumber[nStageNum]) return;

	D3DXVECTOR3 size = m_StageTraBotton[nStageNum]->GetSize();
	D3DXVECTOR3 sizeOrigin = m_StageTraBotton[nStageNum]->GetOriginSize();

	if (size.x < SCALE_VALUE * sizeOrigin.x)
	{
		float fScalePercent = size.x / (SCALE_VALUE * sizeOrigin.x); //現在倍数

		fScalePercent += 1.0f / TIME_SCALE;

		if(fScalePercent > 1 )
		{
			m_StageTraBotton[nStageNum]->SetSize(SCALE_VALUE * sizeOrigin);
			m_Rank[nStageNum]->SetScale(SCALE_VALUE);
			m_StageFont[nStageNum]->SetScale(SCALE_VALUE);
			m_StageNumber[nStageNum]->SetScale(SCALE_VALUE);
			if(NULL != m_ClearFont[nStageNum]) m_ClearFont[nStageNum]->SetScale(SCALE_VALUE);
		}

		else
		{
			m_StageTraBotton[nStageNum]->SetSize(fScalePercent*SCALE_VALUE * sizeOrigin);
			m_Rank[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
			m_StageFont[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
			m_StageNumber[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
			if (NULL != m_ClearFont[nStageNum]) m_ClearFont[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
		}
	}

	else
	{
		m_StageTraBotton[nStageNum]->SetSize(SCALE_VALUE * sizeOrigin);
		m_Rank[nStageNum]->SetScale(SCALE_VALUE);
		m_StageFont[nStageNum]->SetScale(SCALE_VALUE);
		m_StageNumber[nStageNum]->SetScale(SCALE_VALUE);
		if (NULL != m_ClearFont[nStageNum]) m_ClearFont[nStageNum]->SetScale(SCALE_VALUE);
	}
}

void CStageMaster::TraBottonScaleDown(int nStageNum)
{
	if (nStageNum == NO_HIT_ANY_STAGE_FRAME) return;

	//NULLチェック
	if (NULL == m_StageTraBotton[nStageNum]) return;
	if (NULL == m_Rank[nStageNum]) return;
	if (NULL == m_StageFont[nStageNum]) return;
	if (NULL == m_StageNumber[nStageNum]) return;

	D3DXVECTOR3 size = m_StageTraBotton[nStageNum]->GetSize();
	D3DXVECTOR3 sizeOrigin = m_StageTraBotton[nStageNum]->GetOriginSize();

	if (size.x > sizeOrigin.x)
	{
		float fScalePercent = size.x / (SCALE_VALUE * sizeOrigin.x); //現在倍数

		fScalePercent -= 1.0f / TIME_SCALE;

		if (fScalePercent < 0)
		{
			m_StageTraBotton[nStageNum]->SetSize(sizeOrigin);
			m_Rank[nStageNum]->SetScale(1.0f);
			m_StageFont[nStageNum]->SetScale(1.0f);
			m_StageNumber[nStageNum]->SetScale(1.0f);
			if (NULL != m_ClearFont[nStageNum]) m_ClearFont[nStageNum]->SetScale(1.0f);
		}

		else
		{
			m_StageTraBotton[nStageNum]->SetSize(fScalePercent*SCALE_VALUE * sizeOrigin);
			m_Rank[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
			m_StageFont[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
			m_StageNumber[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
			if (NULL != m_ClearFont[nStageNum]) m_ClearFont[nStageNum]->SetScale(fScalePercent*SCALE_VALUE);
		}
	}
}

void CStageMaster::TraBottonScaleDownNotHit(int nStageNumNoDown)
{
	int Priority = CTitleTraBotton::GetPriority();
	for (int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++)
	{
		if(nStageNumNoDown != nStageNum) TraBottonScaleDown(nStageNum);
	}
}

void CStageMaster::Transition(int nStageNum)
{
	if (nStageNum == NO_HIT_ANY_STAGE_FRAME) return;
	if (NULL == m_StageTraBotton[nStageNum]) return;

	if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
	{
		CGameStage::SetStageNumber(m_StageTraBotton[nStageNum]->GetStageNum());
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_GAME);
	}
}

void CStageMaster::DeleteAllStageSelectObj(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;

		nPriority = CTitleTraBotton::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_TITLE_TRA_OBJ)
		{
			//NULL確認
			CTitleTraBotton *pTitleTra = dynamic_cast <CTitleTraBotton *> (pScene);
			if (pTitleTra == NULL) continue;
			pTitleTra->Uninit();
		}

		nPriority = CFontUI::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_TUTORIAL_UI)
		{
			CFontUI *pTuUI= dynamic_cast <CFontUI *> (pScene);
			if (pTuUI == NULL) continue;
			pTuUI->Uninit();
		}

		nPriority = CScrollBar::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SCROLL_BAR)
		{
			CScrollBar *pScrollBar = dynamic_cast <CScrollBar *> (pScene);
			if (pScrollBar == NULL) continue;
			pScrollBar->Uninit();
		}
	}
}

void CStageMaster::CreateStageSelectBar(void)
{
	float fInterval = m_SelectBarHeight / (STAGE_MAX - 1);
	DeleteAllStageSelectObj();

	for (int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++)
	{
		//フレームバー
		m_StageTraBotton[nStageNum] = CTitleTraBotton::Create(D3DXVECTOR3(m_SelectBarPos.x, m_SelectBarPos.y + nStageNum * fInterval, 0.0f), D3DXVECTOR3(375, 150, 0.0f), nStageNum + 1, STAGE_FRAME_TEX);

		//ランク文字
		m_Rank[nStageNum] = CFontUIScale::Create(
			D3DXVECTOR3(m_SelectBarPos.x - STAGE_RANK_OFFSET_X, m_SelectBarPos.y + nStageNum * fInterval - STAGE_RANK_OFFSET_Y, 0.0f), D3DXVECTOR3(STAGE_RANK_WIDTH, STAGE_RANK_HEIGHT, 0.0f),
			D3DXVECTOR3(m_SelectBarPos.x, m_SelectBarPos.y + nStageNum * fInterval, 0.0f),
			255, RESULT_RANK_VARIETY_TEX
		);
		int nStageScore = CResultScore::GetStageScore(nStageNum);
		//ランク設定
		switch (nStageScore)
		{
		case 0:
		case 1:
			m_Rank[nStageNum]->SetUV(D3DXVECTOR2(0.0f, 0.0f));
			m_Rank[nStageNum]->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		case 2:
			m_Rank[nStageNum]->SetUV(D3DXVECTOR2(0.25f, 0.0f));
			m_Rank[nStageNum]->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		case 3:
			m_Rank[nStageNum]->SetUV(D3DXVECTOR2(0.50f, 0.0f));
			m_Rank[nStageNum]->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		default:
			m_Rank[nStageNum]->SetUV(D3DXVECTOR2(0.75f, 0.0f));
			m_Rank[nStageNum]->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		}
		m_Rank[nStageNum]->Update();

		//ステージフォント
		m_StageFont[nStageNum] = CFontUIScale::Create(
			D3DXVECTOR3(m_SelectBarPos.x - STAGE_FONT_OFFSET_X, m_SelectBarPos.y + nStageNum * fInterval, 0.0f), D3DXVECTOR3(STAGE_FONT_WIDTH, STAGE_FONT_HEIGHT, 0.0f),
			D3DXVECTOR3(m_SelectBarPos.x, m_SelectBarPos.y + nStageNum * fInterval, 0.0f),
			255, STAGE_FONT_TEX
		);

		//ステージクリアフォント
		if (CResultScore::GetStageClearFlag(nStageNum) == true)
		{
			m_ClearFont[nStageNum] = CFontUIScale::Create(
				D3DXVECTOR3(m_SelectBarPos.x + STAGE_CLEAR_FONT_OFFSET_X, m_SelectBarPos.y + nStageNum * fInterval - STAGE_CLEAR_FONT_OFFSET_Y, 0.0f), D3DXVECTOR3(STAGE_CLEAR_FONT_WIDTH, STAGE_CLEAR_FONT_HEIGHT, 0.0f),
				D3DXVECTOR3(m_SelectBarPos.x, m_SelectBarPos.y + nStageNum * fInterval, 0.0f),
				255, STAGE_CLEAR_FONT_TEX
			);
		}

		//ステージナンバー
		m_StageNumber[nStageNum] = CScoreScale::Create(
			D3DXVECTOR3(m_SelectBarPos.x + STAGE_NUMBER_OFFSET_X, m_SelectBarPos.y + nStageNum * fInterval , 0.0f),
			D3DXVECTOR3(STAGE_FONT_HEIGHT*0.78,STAGE_FONT_HEIGHT,0.0f),
			D3DXVECTOR3(m_SelectBarPos.x, m_SelectBarPos.y + nStageNum * fInterval, 0.0f),
			2, STAGE_NUMBER_TEX
		);
		m_StageNumber[nStageNum]->SetScore(nStageNum+1);
		m_StageNumber[nStageNum]->Update();
	}
	
	//バー作る
	CFontUI::Create(D3DXVECTOR3(m_ScrollBarPos.x, m_ScrollBarPos.y + m_ScrollBarHeight * 0.5f, 0.0f), D3DXVECTOR3(40, m_ScrollBarHeight + 150.0f, 0.0f), 255, BAR_TEX);
	CScrollBar::Create(D3DXVECTOR3(m_ScrollBarPos.x, m_ScrollBarPos.y, 0.0f), D3DXVECTOR3(50, 100, 0.0f), 255, SLIDE_TEX);
	m_BarTop = CFontUI::Create(D3DXVECTOR3(m_ScrollBarPos.x, m_ScrollBarPos.y-75.0f, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, BAR_TOP_TEX);
	m_BarBottom = CFontUI::Create(D3DXVECTOR3(m_ScrollBarPos.x, m_ScrollBarPos.y+ m_ScrollBarHeight +75.0f, 0.0f), D3DXVECTOR3(50, 50, 0.0f), 255, BAR_BOTTOM_TEX);
}

void CStageMaster::RightClickReturnTitle(void)
{
	if(CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_RIGHT))
	{
		CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
	}
}

void CStageMaster::ScrollBarLeftClick(void)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();

	int nPriority = CScrollBar::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SCROLL_BAR)
		{
			CScrollBar *pScrollBar = dynamic_cast <CScrollBar *> (pScene);
			if (pScrollBar == NULL) continue;

			//マウスロックされているか
			bool bMouseLock = pScrollBar->GetMouseLock();
			if(bMouseLock == true)
			{
				if(CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
				{
					m_ScrollBarPosNow.y = MousePos.y;

					//範囲外移動防止
					m_ScrollBarPosNow.y = min(m_ScrollBarPosNow.y, m_ScrollBarPos.y + m_ScrollBarHeight);
					m_ScrollBarPosNow.y = max(m_ScrollBarPosNow.y, m_ScrollBarPos.y);

					pScrollBar->SetPos(m_ScrollBarPosNow); //座標代入
				}

				else pScrollBar->SetMouseLock(false);
			}
			else
			{
				D3DXVECTOR3 pos = pScrollBar->GetPos();
				D3DXVECTOR3 size = pScrollBar->GetSize();
				bool HitCheck = CHitCheck::HitPointRect(MousePos, pos, size);
				if (HitCheck == false) continue;
				if (CSceneTransition::GetInputMouse()->GetMousePress(MOUSE_LEFT))
				{
					m_ScrollBarPosNow.y = MousePos.y;

					//範囲外移動防止
					m_ScrollBarPosNow.y = min(m_ScrollBarPosNow.y, m_ScrollBarPos.y + m_ScrollBarHeight);
					m_ScrollBarPosNow.y = max(m_ScrollBarPosNow.y, m_ScrollBarPos.y);

					pScrollBar->SetPos(m_ScrollBarPosNow);
					pScrollBar->SetMouseLock(true);
				}
			}
		}
	}
}

void CStageMaster::ScrollBarMouseWheel(void)
{
	int nPriority = CScrollBar::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SCROLL_BAR)
		{
			CScrollBar *pScrollBar = dynamic_cast <CScrollBar *> (pScene);
			if (pScrollBar == NULL) continue;

			//マウスロックされているか
			bool bMouseLock = pScrollBar->GetMouseLock();
			if (bMouseLock == false)
			{
				DIMOUSESTATE *pMouseState = CSceneTransition::GetInputMouse()->GetMouseStates();
				m_ScrollBarPosNow.y -= pMouseState->lZ*0.1;

				//範囲外移動防止
				m_ScrollBarPosNow.y = min(m_ScrollBarPosNow.y, m_ScrollBarPos.y + m_ScrollBarHeight);
				m_ScrollBarPosNow.y = max(m_ScrollBarPosNow.y, m_ScrollBarPos.y);

				pScrollBar->SetPos(m_ScrollBarPosNow);
			}
		}
	}
}

void CStageMaster::SetSelectBarPos(void)         //ステージフレームはバーと同期する
{
	float fPercent = (m_ScrollBarPosNow.y - m_ScrollBarPos.y) / m_ScrollBarHeight;
	D3DXVECTOR3 SelectBarStartPos = m_SelectBarPos;
	SelectBarStartPos.y = m_SelectBarPos.y - m_SelectBarHeight * fPercent;

	float fInterval = m_SelectBarHeight / (STAGE_MAX - 1);

	for (int nStageNum = 0; nStageNum < STAGE_MAX; nStageNum++)
	{
		//位置制御
		if (NULL != m_StageTraBotton[nStageNum]) m_StageTraBotton[nStageNum]->SetPos(D3DXVECTOR3(SelectBarStartPos.x, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
		if (NULL != m_Rank[nStageNum]) {
			m_Rank[nStageNum]->SetOriginPos(D3DXVECTOR3(SelectBarStartPos.x - STAGE_RANK_OFFSET_X, SelectBarStartPos.y + nStageNum*fInterval - STAGE_RANK_OFFSET_Y, SelectBarStartPos.z));
			m_Rank[nStageNum]->SetScalePoint(D3DXVECTOR3(SelectBarStartPos.x, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
		}
		if (NULL != m_StageFont[nStageNum]) {
			m_StageFont[nStageNum]->SetOriginPos(D3DXVECTOR3(SelectBarStartPos.x - STAGE_FONT_OFFSET_X, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
			m_StageFont[nStageNum]->SetScalePoint(D3DXVECTOR3(SelectBarStartPos.x, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
		}
		if (NULL != m_StageNumber[nStageNum]) {
			m_StageNumber[nStageNum]->SetPosToSetOrigin(D3DXVECTOR3(SelectBarStartPos.x + STAGE_NUMBER_OFFSET_X, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
			m_StageNumber[nStageNum]->SetScalePoint(D3DXVECTOR3(SelectBarStartPos.x, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
		}

		if (NULL != m_ClearFont[nStageNum]) {
			m_ClearFont[nStageNum]->SetOriginPos(D3DXVECTOR3(SelectBarStartPos.x + STAGE_CLEAR_FONT_OFFSET_X, SelectBarStartPos.y + nStageNum*fInterval - STAGE_CLEAR_FONT_OFFSET_Y, SelectBarStartPos.z));
			m_ClearFont[nStageNum]->SetScalePoint(D3DXVECTOR3(SelectBarStartPos.x, SelectBarStartPos.y + nStageNum*fInterval, SelectBarStartPos.z));
		}
	}
}

void CStageMaster::ClickBarTopAndBottom(void)
{
	if (NULL == m_BarTop) return;
	if (NULL == m_BarBottom) return;

	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	float OldPos = m_ScrollBarPosNow.y;                          //座標保存
	if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
	{
		D3DXVECTOR3 TopPos = m_BarTop->GetPos();
		D3DXVECTOR3 TopSize = m_BarTop->GetSize();
		bool bHitTop = CHitCheck::HitPointRect(MousePos, TopPos, TopSize);
		if (bHitTop)
		{
			m_ScrollBarPosNow.y -= 20;
		}

		D3DXVECTOR3 BottomPos = m_BarBottom->GetPos();
		D3DXVECTOR3 BottomSize = m_BarBottom->GetSize();
		bool bHitBottom = CHitCheck::HitPointRect(MousePos, BottomPos, BottomSize);
		if(bHitBottom)
		{
			m_ScrollBarPosNow.y += 20;
		}
	}

	if (m_ScrollBarPosNow.y == OldPos) return;
	int nPriority = CScrollBar::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SCROLL_BAR)
		{
			CScrollBar *pScrollBar = dynamic_cast <CScrollBar *> (pScene);
			if (pScrollBar == NULL) continue;

			//マウスロックされているか
			bool bMouseLock = pScrollBar->GetMouseLock();
			if (bMouseLock == false)
			{
				DIMOUSESTATE *pMouseState = CSceneTransition::GetInputMouse()->GetMouseStates();
				m_ScrollBarPosNow.y -= pMouseState->lZ*0.1;

				//範囲外移動防止
				m_ScrollBarPosNow.y = min(m_ScrollBarPosNow.y, m_ScrollBarPos.y + m_ScrollBarHeight);
				m_ScrollBarPosNow.y = max(m_ScrollBarPosNow.y, m_ScrollBarPos.y);

				pScrollBar->SetPos(m_ScrollBarPosNow);
			}
		}
	}
}