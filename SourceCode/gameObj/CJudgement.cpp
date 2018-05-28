#include "CJudgement.h"
#include "CPlayer.h"
#include "CBall.h"
#include "CResultScore.h"

//グローバル
CJudge* CJudgement::m_pJudge = NULL;
bool CJudgement::m_bJudge = false;
int CJudgement::m_nJudgeEffectFrame = 0;

//マグロ
#define PLAYER_WIDTH (20.0f)
#define PLAYER_HEIGHT (100.0f)

#define JUDGE_ALPHA_MAX_FRAME (10)

void CJudgement::Init(void)
{
	m_pJudge = NULL;
	m_bJudge = false;
	m_nJudgeEffectFrame = 0;
}
void CJudgement::Update(void)
{
	Judge();
}

void CJudgement::Judge(void)
{
	if (JudgeCheck() == true)
	{
		CreateJudge();
	}
	ShowJudge();
}
bool CJudgement::JudgeCheck(void)
{
	CPlayer *pPlayer[2] = {};
	int PlayerNum = 0;

	int nPlayerPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//NULL確認
			pPlayer[PlayerNum] = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			PlayerNum++;
		}
	}

	//必要変数
	D3DXVECTOR3 pPlayer01Pos = pPlayer[0]->GetPos();
	D3DXVECTOR3 pPlayer02Pos = pPlayer[1]->GetPos();
	D3DXVECTOR3 pPlayer01Speed = pPlayer[0]->GetSpeed();
	D3DXVECTOR3 pPlayer02Speed = pPlayer[1]->GetSpeed();

	//距離判定
	bool bJudgeDistanceX = fabs(pPlayer01Pos.x - pPlayer02Pos.x) < PLAYER_WIDTH*1.2;
	bool bJudgeDistanceY = fabs(pPlayer01Pos.y - pPlayer02Pos.y) < FLOOR_BLOCK_SIZE*2.1;
	if ((bJudgeDistanceX && bJudgeDistanceY) == false) return false;

	//状態判定
	bool bPlayer01SpeedZero = (0 == pPlayer01Speed.x) && (0 == pPlayer01Speed.y);
	bool bPlayer02SpeedZero = (0 == pPlayer02Speed.x) && (0 == pPlayer02Speed.y);
	if (bPlayer01SpeedZero && bPlayer02SpeedZero) return true;
	return false;
}
void CJudgement::CreateJudge(void)
{
	CPlayer *pPlayer[2] = {};
	int PlayerNum = 0;
	int nBallNum = 0;

	int nPlayerPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPlayerPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//NULL確認
			pPlayer[PlayerNum] = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			PlayerNum++;
		}
	}

	int nPriority = CBall::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;

		//プレーヤー検索
		if (pScene->GetObjType() != CScene::OBJTYPE_BALL) continue;
		CBall* pBall = dynamic_cast<CBall*>(pScene);
		if (NULL == pBall) continue;
		if (pBall->GetDeadFlag() == true) continue;
		nBallNum++;
	}

	//必要変数
	D3DXVECTOR3 pPlayer01Pos = pPlayer[0]->GetPos();
	D3DXVECTOR3 pPlayer02Pos = pPlayer[1]->GetPos();
	D3DXVECTOR3 RankPos = (pPlayer01Pos + pPlayer02Pos) * 0.5;

	//評価
	int UV_Y = 0;
	if(CResultScore::GetUsePairMin() <= 1)
	{
		if (CResultScore::GetKillEnemyOneTurn() > 0)
		{
			if (nBallNum == 0) UV_Y = 0;
			else UV_Y = 1;
		}
		else UV_Y = 2;
	}

	else
	{
		if (CResultScore::GetKillEnemyOneTurn() > 0) UV_Y = 1;
		else UV_Y = 2;
	}

	//評価表示生成
	if (m_bJudge == false)
	{
		m_pJudge = CJudge::Create(
			RankPos, D3DXVECTOR3(140, 35, 0.0f),
			255, { 255,255,255 }, false,
			D3DXVECTOR2(0.0f, 0.3333*UV_Y), D3DXVECTOR2(1.0f, 0.3333),
			PERFECT_GOOD_BAD_TEX
		);
		m_bJudge = true;
		m_nJudgeEffectFrame = 0;
	}
}
void CJudgement::ShowJudge(void)
{
	if (NULL == m_pJudge) return;
	m_nJudgeEffectFrame++;
	m_pJudge->AddPosY(-1.0f);           //上昇

	if (m_nJudgeEffectFrame < JUDGE_ALPHA_MAX_FRAME) return;     //アルファ減少許可

																 //アルファ徐々減少
	int nAlpha = m_pJudge->GetAlpha();
	nAlpha -= 5;
	if (nAlpha < 0)
	{
		m_pJudge->Uninit();
		m_pJudge = NULL;
	}
	else m_pJudge->SetAlpha(nAlpha);
}