//ファイル名 : ResultManager.cpp
//更新日 : 20170513
//Author : nakanishi yusuke
//説明 : リザルトの管理

#include "ResultManager.h"
#include "SceneTransition.h"
#include "CResultScore.h"
#include "CRetryBotton.h"
#include "CNextBotton.h"
#include "CNumber.h"
#include "CScore.h"
#include "Particle.h"
#include "CBackground.h"
#include "input.h"
#include "inputmouse.h"
#include "d3d.h"
#include "CStageMaster.h"
#include "CGameStage.h"
#include "Effect.h"

#define SPEED_UNI_X (5.0f)            //等速運動速度
#define ARROW_DISTANCE_FROM_PLAYER (5.0f)
#define EAGE_RANGE (15.0f)

#define CRANK_SHOW_FRAME (10)
#define CRANK_SPEED_Y (5)

CTextBox*     CResultManager::m_Clear = NULL;
CTextBox*     CResultManager::m_ClearBox = NULL;
CNumber*      CResultManager::m_UsePair = NULL;
CTextBox*     CResultManager::m_UsePairBox = NULL;
CTextBox*	  CResultManager::m_UsePairText = NULL;
CTextBox*     CResultManager::m_Rank = NULL;
CTextBox*     CResultManager::m_RankBox = NULL;
CTextBox*     CResultManager::m_RankText = NULL;
CRetryBotton* CResultManager::m_RetryButton = NULL;
CNextBotton*  CResultManager::m_NextButton = NULL;
CGoToSelect*  CResultManager::m_SelectButton = NULL;
CGoToTitle*   CResultManager::m_TitleButton = NULL;
CParticle*	  CResultManager::m_Particle = NULL;

CResultManager::CResultManager()
{
}

CResultManager::~CResultManager()
{

}

void CResultManager::Init(void)
{
	m_ResultStep = STEP_1;
	m_timer = 0;
	m_skip = false;
	m_changeAlpha = 3;
	m_changeValue = 1.0f;
	m_changePosRate = 1.0f;
	m_startPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_endPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deltaY = 0.0f;

	if (m_RetryButton) m_RetryButton->SetAlpha(0);
	if (m_NextButton) m_NextButton->SetAlpha(0);
	m_nCRankFrameCount = 0;
	m_bFlagRankCJump = false;

	m_Particle = NULL;                  //パーティクルにNULLを入れる
}

void CResultManager::Update(void)
{
	if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
	{
		m_skip = true;
	}

	switch (m_ResultStep)
	{
	case STEP_1:
	{
		SetUp();
		break;
	}
	case STEP_2:
	{
		UpdateClear();
		break;
	}
	case STEP_3:
	case STEP_4:
	{
		UpdateUsePair();
		break;
	}
	case STEP_5:
	{
		UpdateRank();
		break;
	}

	case STEP_6:
	{
		if (CResultScore::GetUsePairMin() == 0 || CResultScore::GetUsePairMin() == 1)
		{
			if (NULL == m_Particle) m_Particle = CParticle::Create(
				m_RankBox->GetPos().x, m_RankBox->GetPos().y, 0.000,
				-4.000,
				23.600, 23.600, 23.600,
				0.000, 0.000, 0.000,
				0.000, 0.000, 0.000,
				0.001, 0.001, 0.001,
				1, 31.000, 0.000, 0.000,
				1.0, 1.0, 1.0, 1.0,
				0.000, 0.000, 0.000, 60.000, 60.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 246.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1,RESULT_PARTICLE_01);
			m_Particle->SetStop(true);
		}
		m_ResultStep = STEP_7;
		break;
	}

	case STEP_7:
	{
		UpdateRankVariety();
		break;
	}

	case STEP_8:
	{
		RetryGame();
		NextGame();
		//GoToTitle();
		GoToSelect();
		break;
	}
	}
}

void CResultManager::Uninit(void)
{
}

void CResultManager::SetUp(void)
{
	if (m_ClearBox)
	{
		m_ClearBox->SetEndSize(m_ClearBox->GetSize());
		m_ClearBox->SetSize(D3DXVECTOR3(2000.0f, 2000.f, 0.0f));
		m_ClearBox->SetDeltaSize((m_ClearBox->GetEndSize() - m_ClearBox->GetSize()) * 0.001f);
	}

	m_ResultStep = STEP_2;
}

void CResultManager::UpdateClear(void)
{
	if (m_skip)
	{
		m_changeValue = 10000.0f;
		m_changeAlpha = 1000.0f;
		m_timer = 100;
	}

	m_ClearBox->ChangeAlpha(m_changeAlpha);
	if (m_ClearBox->GetAlpha() >= 255)
	{
		m_ClearBox->SetAlpha(255);
	}

	m_ClearBox->ChangeSize(m_ClearBox->GetDeltaSize() * m_changeValue);
	if (m_ClearBox->GetSize().x <= m_ClearBox->GetEndSize().x)
	{
		m_ClearBox->SetSize(m_ClearBox->GetEndSize());
	}

	if (m_timer > 90)
	{
		m_ClearBox->SetAlpha(255);
		m_ResultStep = STEP_3;
		m_timer = 0;
		m_changeValue = 0.0f;
	}

	m_timer++;

	m_changeValue += 1.0f;
}

void CResultManager::UpdateUsePair(void)
{
	if (m_skip)
	{
		m_changeValue = 2000.0f;
		m_timer = 100;
	}

	m_UsePairText->ChangePos(D3DXVECTOR3(m_changeValue, 0.0f, 0.0f));
	if (m_UsePairText->GetPos().x > m_UsePairText->GetEndPos().x)
	{
		m_UsePairText->SetPos(m_UsePairText->GetEndPos());
	}

	m_UsePairBox->ChangePos(D3DXVECTOR3(m_changeValue, 0.0f, 0.0f));
	if (m_UsePairBox->GetPos().x > m_UsePairBox->GetEndPos().x)
	{
		m_UsePairBox->SetPos(m_UsePairBox->GetEndPos());
	}

	m_UsePair->ChangePos(D3DXVECTOR3(m_changeValue, 0.0f, 0.0f));
	if (m_UsePair->GetPos().x > (m_UsePair->GetEndPos().x))
	{
		m_UsePair->SetPos(m_UsePair->GetEndPos());
	}

	if (m_timer > 90)
	{
		m_ResultStep = STEP_5;
		m_timer = 0;
		m_changeValue = 0.0f;
	}

	m_timer++;
	m_changeValue += 1.0f;
}

void CResultManager::UpdateRank(void)
{
	if (m_skip)
	{
		m_changeAlpha = 1000.0f;
		m_changeValue = 2000.0f;
		m_timer = 100;
	}

	m_RankText->ChangePos(D3DXVECTOR3(m_changeValue, 0.0f, 0.0f));
	if (m_RankText->GetPos().x > m_RankText->GetEndPos().x)
	{
		m_RankText->SetPos(m_RankText->GetEndPos());
	}

	m_RankBox->ChangePos(D3DXVECTOR3(m_changeValue, 0.0f, 0.0f));
	if (m_RankBox->GetPos().x > m_RankBox->GetEndPos().x)
	{
		m_RankBox->SetPos(m_RankBox->GetEndPos());
	}

	m_Rank->ChangePos(D3DXVECTOR3(m_changeValue, 0.0f, 0.0f));
	if (m_Rank->GetPos().x > (m_Rank->GetEndPos().x))
	{
		m_Rank->SetPos(m_Rank->GetEndPos());
	}

	if (m_timer > 90)
	{
		m_ResultStep = STEP_6;
		m_timer = 0;
		m_changeValue = 1.0f;

		switch (CResultScore::GetUsePairMin())
		{
		case 0:
		case 1:
			m_Rank->SetEndSize(m_Rank->GetSize());
			m_Rank->SetSize(D3DXVECTOR3(2000.0f, 2000.f, 0.0f));
			m_Rank->SetDeltaSize((m_Rank->GetSize() - m_Rank->GetEndSize()) * 0.0001f);
			m_Rank->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		case 2:
			m_Rank->SetAlpha(255);
			m_Rank->SetPos(D3DXVECTOR3(-m_Rank->GetSize().x, m_Rank->GetPos().y, 0.0f));
			m_Rank->SetDirVec((m_Rank->GetEndPos() - m_Rank->GetPos()) * 0.0001f);
			m_Rank->SetUV(D3DXVECTOR2(0.25f, 0.0f));
			m_Rank->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		case 3:
			m_Rank->SetUV(D3DXVECTOR2(0.50f, 0.0f));
			m_Rank->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		default:
			m_Rank->SetAlpha(255);
			m_Rank->SetPos(D3DXVECTOR3(m_Rank->GetPos().x, -m_Rank->GetSize().y, 0.0f));
			m_Rank->SetDirVec((m_Rank->GetEndPos() - m_Rank->GetPos()) * 0.0001f);
			m_Rank->SetUV(D3DXVECTOR2(0.75f, 0.0f));
			m_Rank->SetUVWH(D3DXVECTOR2(0.25f, 1.0f));
			break;
		}
	}

	m_timer++;
	m_changeValue += 1.0f;
}

void CResultManager::UpdateRankVariety(void)
{
	if (m_skip)
	{
		m_changeAlpha = 1000.0f;
		m_changeValue = 100000.0f;
		m_timer = 200;
	}

	switch (CResultScore::GetUsePairMin())
	{
	case 0:
	case 1:
		m_Rank->ChangeAlpha(m_changeAlpha);
		if (m_Rank->GetAlpha() >= 255)
		{
			m_Rank->SetAlpha(255);
			m_Rank->SetSize(m_Rank->GetEndSize());
		}

		m_Rank->ChangePos(m_Rank->GetDirVec() * m_changeValue);
		if (m_Rank->GetPos().x >= m_Rank->GetEndPos().x)
		{
			m_Rank->SetPos(m_Rank->GetEndPos());
		}

		m_Rank->ChangeSize(-m_Rank->GetDeltaSize() * m_changeValue);
		if (m_Rank->GetSize().x <= m_Rank->GetEndSize().x)
		{
			m_Rank->SetSize(m_Rank->GetEndSize());
			m_Particle->SetStop(false);
		}

		m_changeValue *= 1.2f;

		if (m_timer > 90)
		{
			m_ResultStep = STEP_8;
			m_timer = 0;
		}

		break;

	case 2:
		m_Rank->ChangePos(m_Rank->GetDirVec() * m_changeValue);
		if (m_Rank->GetPos().x >= m_Rank->GetEndPos().x)
		{
			m_Rank->SetPos(m_Rank->GetEndPos());
		}

		m_changeValue *= 1.1f;

		if (m_timer > 90)
		{
			m_ResultStep = STEP_8;
			m_timer = 0;
		}

		break;

	case 3:
		m_Rank->ChangeAlpha(m_changeAlpha);
		if (m_Rank->GetAlpha() >= 255)
		{
			m_Rank->SetAlpha(255);
		}

		if (m_timer > 60)
		{
			m_ResultStep = STEP_8;
			m_timer = 0;
		}

		break;

	default:
		m_Rank->AddDirVec(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_Rank->ChangePos(m_Rank->GetDirVec());

		if (m_Rank->GetPos().y >= m_Rank->GetEndPos().y)
		{
			m_Rank->SetPos(m_Rank->GetEndPos());
			m_Rank->MultiDirVec(-0.6f);
		}

		if (m_timer > 120)
		{
			m_Rank->SetPos(m_Rank->GetEndPos());
			m_ResultStep = STEP_8;
			m_timer = 0;
		}

		break;
	}

	m_timer++;
}

void CResultManager::RetryGame(void)
{
	m_RetryButton->ChangeAlpha(m_changeAlpha);

	//マウス座標とボタンの当り判定
	D3DXVECTOR3 BottonPos = m_RetryButton->GetPos();
	D3DXVECTOR3 BottonSize = m_RetryButton->GetSize();
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
		m_RetryButton->SetSize(D3DXVECTOR3(200.0f, 200.0f, 0.0f));
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
		{
			// リトライ処理
			CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_GAME);
		}
	}
	else
	{
		m_RetryButton->SetSize(D3DXVECTOR3(150.0f, 150.0f, 0.0f));
	}

	m_changeValue += 1.0f;
}

void CResultManager::NextGame(void)
{
	m_NextButton->ChangeAlpha(m_changeAlpha);

	//マウス座標とボタンの当り判定
	D3DXVECTOR3 BottonPos = m_NextButton->GetPos();
	D3DXVECTOR3 BottonSize = m_NextButton->GetSize();
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
		m_NextButton->SetSize(D3DXVECTOR3(200.0f, 200.0f, 0.0f));
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
		{
			// ネクスト処理
			int StageNumber = CGameStage::GetStageNumber();
			StageNumber++;
			if (StageNumber > STAGE_MAX)
			{
				CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
				StageNumber = 1;
			}
			else
			{
				CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_GAME);
			}
			CGameStage::SetStageNumber(StageNumber);
			
		}
	}
	else
	{
		m_NextButton->SetSize(D3DXVECTOR3(150.0f, 150.0f, 0.0f));
	}
}

void CResultManager::GoToTitle(void)
{
	m_TitleButton->ChangeAlpha(m_changeAlpha);

	//マウス座標とボタンの当り判定
	D3DXVECTOR3 BottonPos = m_TitleButton->GetPos();
	D3DXVECTOR3 BottonSize = m_TitleButton->GetSize();
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
		m_TitleButton->SetSize(D3DXVECTOR3(150.0f, 150.0f, 0.0f));
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
		{
			// タイトルへ戻る
			CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_TITLE);
		}
	}
	else
	{
		m_TitleButton->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	}

}

void CResultManager::GoToSelect(void)
{
	m_SelectButton->ChangeAlpha(m_changeAlpha);

	//マウス座標とボタンの当り判定
	D3DXVECTOR3 BottonPos = m_SelectButton->GetPos();
	D3DXVECTOR3 BottonSize = m_SelectButton->GetSize();
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
		m_SelectButton->SetSize(D3DXVECTOR3(350.0f, 87.50f, 0.0f));
		if (CSceneTransition::GetInputMouse()->GetMouseTrigger(MOUSE_LEFT))
		{
			// ネクスト処理
			CSceneTransition::SetScene(CSceneTransition::FADE_OUT, CSceneTransition::SCENE_STAGE_SELECT);
		}
	}
	else
	{
		m_SelectButton->SetSize(D3DXVECTOR3(300.0f, 75.0f, 0.0f));
	}
}

void  CResultManager::NullAllPointer(void)
{
	m_Clear = NULL;
	m_ClearBox = NULL;
	m_UsePair = NULL;
	m_UsePairBox = NULL;
	m_UsePairText = NULL;
	m_Rank = NULL;
	m_RankBox = NULL;
	m_RankText = NULL;
	m_RetryButton = NULL;
	m_NextButton = NULL;
	m_SelectButton = NULL;
	m_TitleButton = NULL;
	m_Particle = NULL;
}

