#include "CSpringPushBall.h"
#include "scene.h"
#include "CBall.h"
#include "CSpring.h"
#include "hitCheck.h"

void CSpringPushBall::Update(void)
{
	SpringPushBall();
}

void CSpringPushBall::SpringPushBall(void)
{
	float PowerFromSpring = 0;         //ばねから受けた力
	const int nPriorityBall = CBall::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriorityBall);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_BALL)       //ボールですか？
		{
			CBall *pBall = dynamic_cast<CBall*>(pScene);
			if (pBall == NULL) continue;
			CSpring* pSpring = BallHitSpring(pBall);
			if (pSpring == NULL) continue;                 //ボールはばねに当たってない
			AdjustSpring(pBall, pSpring);               //ばねの位置とサイズ調整
			PowerFromSpring = GetPowerFromSpring(pSpring); //ばねの弾力計算
			PushBall(pBall, PowerFromSpring * 2);         //ばねの弾力でボールを押す
		}
	}
}

CSpring* CSpringPushBall::BallHitSpring(CBall *pBall)
{
	if (pBall == NULL) return NULL;

	D3DXVECTOR3 BallPos = pBall->GetPos();
	D3DXVECTOR3 BallSize = pBall->GetSize();
	CSpring* pSpring = NULL;

	int nPrioritySpring = CSpring::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPrioritySpring);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SPRING)      //ばねですか？
		{
			pSpring = dynamic_cast<CSpring *>(pScene);
			D3DXVECTOR3 SpringPosOrigin = pSpring->GetPosOrigin();
			D3DXVECTOR3 SpringSizeOrigin = pSpring->GetSizeOrigin();

			bool HitCheck = CHitCheck::HitRect(SpringPosOrigin, SpringSizeOrigin, BallPos, BallSize);
			if (HitCheck)
			{
				return pSpring;
			}
		}
	}

	return NULL;
}

void CSpringPushBall::AdjustSpring(CBall *pBall, CSpring* pSpring)
{
	if (pBall == NULL) return;
	if (pSpring == NULL) return;

	bool bSpringFixDir = pSpring->GetFixDirection();
	D3DXVECTOR3 BallPos = pBall->GetPos();
	D3DXVECTOR3 BallSize = pBall->GetSize();
	D3DXVECTOR3 SpringPosOrigin = pSpring->GetPosOrigin();
	D3DXVECTOR3 SpringSizeOrigin = pSpring->GetSizeOrigin();

	if (bSpringFixDir == false)   //右に押す
	{
		float SpringLeft = SpringPosOrigin.x - SpringSizeOrigin.x*0.5;
		float BallLeft = BallPos.x - BallSize.x*0.5;
		float SpringSizeX = BallLeft - SpringLeft;
		float SpringPosX = SpringLeft + SpringSizeX*0.5;
		pSpring->SetPos(D3DXVECTOR3(SpringPosX, SpringPosOrigin.y, 0.0f));
		pSpring->SetSize(D3DXVECTOR3(SpringSizeX, SpringSizeOrigin.y, 0.0f));
	}

	else
	{
		float SpringRight = SpringPosOrigin.x + SpringSizeOrigin.x*0.5;
		float BallRight = BallPos.x + BallSize.x*0.5;
		float SpringSizeX = SpringRight - BallRight;
		float SpringPosX = SpringRight - SpringSizeX*0.5;
		pSpring->SetPos(D3DXVECTOR3(SpringPosX, SpringPosOrigin.y, 0.0f));
		pSpring->SetSize(D3DXVECTOR3(SpringSizeX, SpringSizeOrigin.y, 0.0f));
	}
}

float CSpringPushBall::GetPowerFromSpring(CSpring* pSpring)
{
	if (pSpring == NULL) return 0;

	float PowerX = 0;
	bool bSpringFixDir = pSpring->GetFixDirection();

	D3DXVECTOR3 SpringPos = pSpring->GetPos();
	D3DXVECTOR3 SpringSize = pSpring->GetSize();
	D3DXVECTOR3 SpringPosOrigin = pSpring->GetPosOrigin();
	D3DXVECTOR3 SpringSizeOrigin = pSpring->GetSizeOrigin();

	//左固定
	if (bSpringFixDir == false)
	{
		float SpringLeft = SpringPosOrigin.x - SpringSizeOrigin.x*0.5;
		float SpringRightOrigin = SpringPosOrigin.x + SpringSizeOrigin.x * 0.5;
		float SpringRightNow = SpringPos.x + SpringSize.x*0.5;
		PowerX = (SpringRightOrigin - SpringRightNow) * pSpring->GetElasticModulus();
	}

	//右固定
	else
	{
		float SpringRight = SpringPosOrigin.x + SpringSizeOrigin.x*0.5;
		float SpringLeftOrigin = SpringPosOrigin.x - SpringSizeOrigin.x * 0.5;
		float SpringLeftNow = SpringPos.x - SpringSize.x*0.5;
		PowerX = (SpringLeftOrigin - SpringLeftNow) * pSpring->GetElasticModulus();
	}

	return PowerX;
}

void CSpringPushBall::PushBall(CBall *pBall, float PowerFromSpring)
{
	if (pBall == NULL) return;
	pBall->AddPowerX(PowerFromSpring);           //ボールを押す
}
