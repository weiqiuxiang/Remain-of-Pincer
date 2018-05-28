#include "CWormHoleWarpPlayer.h"
#include "CPlayer.h"
#include "hitCheck.h"

void CWormHoleWarpPlayer::Update(void)
{
	WormHoleReturn();
	PlayerHitWormHole();
}

void CWormHoleWarpPlayer::PlayerHitWormHole(void)
{	
	int nPriority = CPlayer::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)       //プレーヤーですか？
		{
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);
			if (pPlayer == NULL) continue;
			CWormHole* pWormHole = OnePlayerHitAllWormHole(pPlayer);
			if (pWormHole == NULL) continue;                 //プレーヤーはばねに当たってない

			//当たったら,当たる時の命令を実行
			pPlayer->SetPos(pWormHole->GetPos());          //座標設定
			pWormHole->SetWarpFlag(true);
			AdjustTwoPlayerPos(pPlayer);                   //柱の位置の互換
		}
	}
}

CWormHole* CWormHoleWarpPlayer::OnePlayerHitAllWormHole(CPlayer *pPlayer)
{
	if (NULL == pPlayer) return NULL;

	CWormHole* pWormHole = NULL;

	int nPriority = CWormHole::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_WORM_HOLE) 
		{
			D3DXVECTOR3 WormHolePos = pScene->GetPos();
			D3DXVECTOR3 WormHoleSize = pScene->GetSize();
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
			D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

			bool bHit = CHitCheck::HitRect(WormHolePos, WormHoleSize, PlayerPos, PlayerSize);
			if ( (bHit == true) && (pWormHole->GetWarpFlag() == false))
			{
				pWormHole = dynamic_cast<CWormHole*>(pScene);
				break;
			}
		}
	}

	return pWormHole;
}

void CWormHoleWarpPlayer::AdjustTwoPlayerPos(CPlayer *pPlayer)
{
	if (NULL == pPlayer) return;
	int nPriority = CPlayer::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)       //プレーヤーですか？
		{
			if (pScene == pPlayer) continue;
			D3DXVECTOR3 pScenePos = pScene->GetPos();
			D3DXVECTOR3 pPlayerPos = pPlayer->GetPos();
			pScene->SetPos(pPlayerPos);
			pPlayer->SetPos(pScenePos);
		}
	}
}

void CWormHoleWarpPlayer::WormHoleReturn(void)
{
	int nPriority = CWormHole::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_WORM_HOLE)
		{
			CWormHole* pWormHole = dynamic_cast<CWormHole *>(pScene);
			if (pWormHole == NULL) continue;
			WormHoleNotHitAnyPlayer(pWormHole);
		}
	}
}

void CWormHoleWarpPlayer::WormHoleNotHitAnyPlayer(CWormHole* pWormHole)
{
	if (NULL == pWormHole) return;
	bool bHitOneTime = false;

	int nPriority = CPlayer::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)       //プレーヤーですか？
		{
			D3DXVECTOR3 WormHolePos = pWormHole->GetPos();
			D3DXVECTOR3 WormHoleSize = pWormHole->GetSize();
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			D3DXVECTOR3 PlayerSize = pScene->GetSize();

			bool bHit = CHitCheck::HitRect(WormHolePos, WormHoleSize, PlayerPos, PlayerSize);

			if (bHit)
			{
				bHitOneTime = true;
				break;
			}
		}
	}

	if (false == bHitOneTime) pWormHole->SetWarpFlag(false);
}