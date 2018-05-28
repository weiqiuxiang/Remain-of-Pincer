#include "CPlayerHitFloorBreak.h"
#include "CFloor.h"
#include "hitCheck.h"

void CPlayerHitFloorBreak::Update(void)
{
	//�v���[���[��T��
	int nPriority = CPlayer::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)       //�v���[���[�ł����H
		{
			PlayerHitAllFloor(pScene);
		}
	}
}

void CPlayerHitFloorBreak::PlayerHitAllFloor(CScene* pPlayer)
{
	if (NULL == pPlayer) return;
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 PlayerSize = pPlayer->GetSize();
	PlayerSize.x = PlayerSize.x - 10;
	//FLOOR��T��
	int nPriority = CFloor::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_FLOOR)
		{
			CFloor *pFloor = dynamic_cast<CFloor *>(pScene);
			if (NULL == pFloor) continue;
			if (pFloor->GetBlockType() == CFloor::TYPE_NORMAL) continue;

			//���蔻��
			D3DXVECTOR3 FloorPos = pFloor->GetPos();
			D3DXVECTOR3 FloorSize = pFloor->GetSize();

			bool bHit = CHitCheck::HitRect(PlayerPos, PlayerSize, FloorPos, FloorSize);
			float BlockBottom = FloorPos.y + FloorSize.y*0.5;      //�u���b�N�̒��
			float PlayerBottom = PlayerPos.y + PlayerSize.y*0.5;   //�v���[���[�̒��

			if((bHit == true) && (BlockBottom - PlayerBottom > FLOOR_BLOCK_SIZE*0.7))
			{
				pFloor->SetAlreadyHit(true);
			}
		}
	}
}

void CPlayerHitFloorBreak::DeleteFloorBreak(CFloor* pFloor)
{
	if (NULL == pFloor) return;
	D3DXVECTOR3 FloorPos = pFloor->GetPos();
	D3DXVECTOR3 FloorSize = pFloor->GetSize();


	//�v���[���[��T��
	int nPriority = CPlayer::GetPriority();
	for (int i = 0; i < SCENE_MAX_NUM; i++)
	{
		CScene *pScene = CScene::GetScene(i, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)       //�v���[���[�ł����H
		{
			D3DXVECTOR3 PlayerPos = pScene->GetPos();
			D3DXVECTOR3 PlayerSize = pScene->GetSize();

			bool bHit = CHitCheck::HitRect(PlayerPos, PlayerSize, FloorPos, FloorSize);

			if( (bHit == false) && (pFloor->GetAlreadyHit() == true) )
			{
				pFloor->Uninit();
				pFloor = NULL;
			}
		}
	}
}