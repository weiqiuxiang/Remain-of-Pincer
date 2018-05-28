#include "CSpringPushPlayer.h"
#include "scene.h"
#include "CPlayer.h"
#include "CSpring.h"
#include "hitCheck.h"
#include "sound.h"

void CSpringPushPlayer::Update(void)
{
	SpringReturn();                //�o�l�̉񕜍s��
	SpringPushPlayer();
}

void CSpringPushPlayer::SpringReturn(void)
{
	int nPrioritySpring = CSpring::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPrioritySpring);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SPRING)      //�΂˂ł����H
		{
			CSpring*pSpring = dynamic_cast<CSpring *>(pScene);
			if (pSpring == NULL) continue;
			pSpring->SetReturnFlag(true);
		}
	}
}

void CSpringPushPlayer::SpringPushPlayer(void)
{
	float PowerFromSpring = 0;         //�΂˂���󂯂���
	const int nPriorityPlayer = CPlayer::GetPriority();
	for(int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i,nPriorityPlayer);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)       //�v���[���[�ł����H
		{
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);
			if (pPlayer == NULL) continue;
			CSpring* pSpring = PlayerHitSpring(pPlayer);
			if (pSpring == NULL) continue;                 //�v���[���[�͂΂˂ɓ������ĂȂ�
			pSpring->SetReturnFlag(false);
			AdjustSpring(pPlayer, pSpring);               //�΂˂̈ʒu�ƃT�C�Y����
			PowerFromSpring = GetPowerFromSpring(pSpring); //�΂˂̒e�͌v�Z
			PushPlayer(pPlayer, PowerFromSpring);         //�΂˂̒e�͂Ńv���[���[������
		}
	}
}

CSpring* CSpringPushPlayer::PlayerHitSpring(CPlayer *pPlayer)
{
	if (pPlayer == NULL) return NULL;

	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
	CSpring* pSpring = NULL;

	int nPrioritySpring = CSpring::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPrioritySpring);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_SPRING)      //�΂˂ł����H
		{
			pSpring = dynamic_cast<CSpring *>(pScene);
			D3DXVECTOR3 SpringPosOrigin = pSpring->GetPosOrigin();
			D3DXVECTOR3 SpringSizeOrigin = pSpring->GetSizeOrigin();

			bool HitCheck = CHitCheck::HitRect(SpringPosOrigin, SpringSizeOrigin, PlayerPos, PlayerSize);
			if(HitCheck)
			{
				return pSpring;
			}
		}
	}

	return NULL;
}

void CSpringPushPlayer::AdjustSpring(CPlayer *pPlayer,CSpring* pSpring)
{
	if (pPlayer == NULL) return;
	if (pSpring == NULL) return;

	bool bSpringFixDir = pSpring->GetFixDirection();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
	D3DXVECTOR3 SpringPosOrigin = pSpring->GetPosOrigin();
	D3DXVECTOR3 SpringSizeOrigin = pSpring->GetSizeOrigin();

	if(bSpringFixDir == false)   //�E�ɉ���
	{
		float SpringLeft = SpringPosOrigin.x - SpringSizeOrigin.x*0.5;
		float PlayerLeft = PlayerPos.x - PlayerSize.x*0.5;
		float SpringSizeX = PlayerLeft - SpringLeft;
		float SpringPosX = SpringLeft + SpringSizeX*0.5;
		pSpring->SetPos(D3DXVECTOR3(SpringPosX, SpringPosOrigin.y,0.0f));
		pSpring->SetSize(D3DXVECTOR3(SpringSizeX, SpringSizeOrigin.y, 0.0f));
	}

	else
	{
		float SpringRight = SpringPosOrigin.x + SpringSizeOrigin.x*0.5;
		float PlayerRight = PlayerPos.x + PlayerSize.x*0.5;
		float SpringSizeX = SpringRight - PlayerRight;
		float SpringPosX = SpringRight - SpringSizeX*0.5;
		pSpring->SetPos(D3DXVECTOR3(SpringPosX, SpringPosOrigin.y, 0.0f));
		pSpring->SetSize(D3DXVECTOR3(SpringSizeX, SpringSizeOrigin.y, 0.0f));
	}
}

float CSpringPushPlayer::GetPowerFromSpring(CSpring* pSpring)
{
	if (pSpring == NULL) return 0;

	float PowerX = 0;
	bool bSpringFixDir = pSpring->GetFixDirection();

	D3DXVECTOR3 SpringPos = pSpring->GetPos();
	D3DXVECTOR3 SpringSize = pSpring->GetSize();
	D3DXVECTOR3 SpringPosOrigin = pSpring->GetPosOrigin();
	D3DXVECTOR3 SpringSizeOrigin = pSpring->GetSizeOrigin();

	//���Œ�
	if (bSpringFixDir == false)
	{
		float SpringLeft = SpringPosOrigin.x - SpringSizeOrigin.x*0.5;
		float SpringRightOrigin = SpringPosOrigin.x + SpringSizeOrigin.x * 0.5;
		float SpringRightNow = SpringPos.x + SpringSize.x*0.5;
		PowerX = (SpringRightOrigin - SpringRightNow) * pSpring->GetElasticModulus();
	}

	//�E�Œ�
	else
	{
		float SpringRight = SpringPosOrigin.x + SpringSizeOrigin.x*0.5;
		float SpringLeftOrigin = SpringPosOrigin.x - SpringSizeOrigin.x * 0.5;
		float SpringLeftNow = SpringPos.x - SpringSize.x*0.5;
		PowerX = (SpringLeftOrigin - SpringLeftNow) * pSpring->GetElasticModulus();
	}

	return PowerX;
}

void CSpringPushPlayer::PushPlayer(CPlayer *pPlayer,float PowerFromSpring)
{
	if (pPlayer == NULL) return;
	pPlayer->AddPowerX(PowerFromSpring);           //�v���[���[������
	D3DXVECTOR3 PlayerSpeed = pPlayer->GetSpeed();
	bool bPlayerDir = pPlayer->GetMoveDirection();
	if (bPlayerDir == false)         //�v���[���[�����ɍs��
	{
		if(PlayerSpeed.x > 0)
		{
			pPlayer->SetMoveDirection(true);
			PlaySound(SE_SPRING);
		}
	}

	else             //�v���[���[�E�ɍs��
	{
		if (PlayerSpeed.x < 0)
		{
			pPlayer->SetMoveDirection(false);
			PlaySound(SE_SPRING);
		}
	}
}
