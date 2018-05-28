#include "CPlayer.h"
#include "input.h"
#include "inputmouse.h"
#include "SceneTransition.h"
#include "renderer.h"
#include "CBullet.h"
#include "hitCheck.h"
#include "CPlayerGuild.h"
#include "CFloor.h"
#include "CEarthquake.h"
#include "sound.h"
#include "Effect.h"

#define DRAG_COEFFI_X (0.15f)
#define DRAG_COEFFI_Y (0.5)
#define Y_DISTANCE_PLAYER_FLOOR (10.0f)
#define Y_PUSH (7)

#define PLAYSOUND_DISTANCE (2.0f)
#define MAKE_PARTICLE_DISTANCE (4.0f)

#define HITFLOOR_PARTICLE_LIFE (5)

int CPlayer::s_nPriority = 3;

CPlayer::CPlayer() : CScene2D(3)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_StandFloor = false;
	m_MouseLock = false;
}

CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_StandFloor = false;
	m_MouseLock = false;
}

CPlayer::~CPlayer()
{
	if (m_Particle != NULL)
	{
		m_Particle->Uninit();
		m_Particle = NULL;
	}

	if (m_ParticleHitFloor != NULL)
	{
		m_ParticleHitFloor->Uninit();
		m_ParticleHitFloor = NULL;
	}
}

//プレーヤーのインスタンスを生成する関数
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(s_nPriority);
	pPlayer->Init(pos, size);
	pPlayer->LoadTexture(filePass);
	return pPlayer;
}

//プレーヤーの初期化
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size);
	CScene2D::SetObjType(OBJTYPE_PLAYER);
	m_StandFloor = false;
	m_StandFloorOld = m_StandFloor;
	m_MouseLock = true;
	m_bMoveDirection = false;
	m_mass = 3.0f;
	m_Power = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Particle = NULL;
	m_ParticleHitFloor = NULL;
	m_HitFloorTime = 0;
	return S_OK;
}

//更新処理
void CPlayer::Update(void)
{
	if (CSceneTransition::GetGameMaster()->GetPauseFlag() == true) { m_Power = D3DXVECTOR3(0.0f, 0.0f, 0.0f); return; }

	//位置制限
	bool BorderlineOut = (m_pos.x + m_size.x*0.5) > SCREEN_WIDTH || (m_pos.x - m_size.x*0.5) < 0;
	if (BorderlineOut == true) m_pos.x = m_posOld.x;

	CScene2D::VertexLock(); //頂点ロック
	m_posOld = m_pos;	//座標保存
	m_speedOld = m_speed;
	m_StandFloorOld = m_StandFloor;

	//特殊状態判定
	if (m_MouseLock == true) { HitFloorNormal(); return; } //マウスロックの状態判定
	if (GameNotStart() == true) return; //ゲームを始めることができない状態の判定
	
	PowerReset();

	float Gravity = m_mass * GRAVITY_ACC;  //重力

	//抗力
	D3DXVECTOR3 Drag = D3DXVECTOR3(0.0f,0.0f,0.0f);    //抗力
	Drag.x = -m_speed.x * DRAG_COEFFI_X;
	Drag.y = -m_speed.y * DRAG_COEFFI_Y;            //y方向抗力

	//外力合計
	float PowerX = m_Power.x + Drag.x;
	float PowerY = Gravity + Drag.y;

	//加速度計算
	D3DXVECTOR3 Acc;
	Acc.x = PowerX / m_mass;
	Acc.y = PowerY / m_mass;

	//外力リセット
	m_Power = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//速度計算
	m_speed.x += Acc.x;
	m_speed.y += Acc.y;

	//当り判定
	HitFloor(); //地面
	//HitFloorCanNotMove(); //地面に嵌らないように
	HitOtherPlayer();//別の挟み子
	SetEarthquake();

	//移動量計算
	if (m_StandFloor == true)
	{
		m_pos.x += m_speed.x;
	}
	m_pos.y += m_speed.y;

	//位置制限
	BorderlineOut = (m_pos.x + m_size.x*0.5) > SCREEN_WIDTH || (m_pos.x - m_size.x*0.5) < 0;
	if (BorderlineOut == true) { m_pos.x = m_posOld.x; m_speed.x = 0.0f; }

	PlayHitSound();
	MoveParticle();

	m_HitFloorTime--;
	if(m_HitFloorTime < 0)
	{
		m_HitFloorTime = 0;
		if(m_ParticleHitFloor != NULL)
		{
			m_ParticleHitFloor->Uninit();
			m_ParticleHitFloor = NULL;
		}
	}
}

//描画処理
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CPlayer::Uninit(void)
{
	if (m_Particle != NULL)
	{
		m_Particle->Uninit();
		m_Particle = NULL;
	}
	CScene2D::Uninit();
}

void CPlayer::HitFloor(void)
{
	int nPriority = CFloor::GetPriority();
	bool StandFloor = false;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if(pScene->GetObjType() == OBJTYPE_FLOOR)
		{
			D3DXVECTOR3 FloorPos = pScene->GetPos();
			D3DXVECTOR3 FloorSize = pScene->GetSize();
			
			D3DXVECTOR3 PlayerNext = m_pos;
			if (m_bMoveDirection == false) PlayerNext.x = m_pos.x - FLOOR_BLOCK_SIZE*0.1;
			else PlayerNext.x = m_pos.x + FLOOR_BLOCK_SIZE*0.1;

			bool HitRect = CHitCheck::HitRect(PlayerNext, m_size, FloorPos, FloorSize);
			if (HitRect)
			{
				float BlockBottom = FloorPos.y + FloorSize.y*0.5;      //ブロックの底辺
				float PlayerBottom = m_pos.y + m_size.y*0.5;   //プレーヤーの底辺
				if((BlockBottom - PlayerBottom) > FLOOR_BLOCK_SIZE*0.7) m_speed.y = 0;

				StandFloor = true;

				float FloorTop = FloorPos.y - FloorSize.y * 0.5;
				bool XSpeedZero = (PlayerBottom - FloorTop) > Y_DISTANCE_PLAYER_FLOOR;
				if (XSpeedZero)
				{
					if(m_bMoveDirection == true) 
					{
						float FloorLeft = FloorPos.x - FloorSize.x*0.5;
						m_pos.x = FloorLeft - m_size.x * 0.5 - 1;
						m_speed.x = 0;
					}

					else
					{
						float FloorRight = FloorPos.x + FloorSize.x*0.5;
						m_pos.x = FloorRight + m_size.x * 0.5 + 1;
						m_speed.x = 0;
					}
				}

				else
				{
					if ((PlayerBottom - FloorTop) > Y_PUSH) m_pos.y -= 1;
				}
			}
		}
		else continue;
	}
	m_StandFloor = StandFloor;                         //
}

void CPlayer::MouseCreatePlayerGuild(bool bHitPlayerAndFloor)
{
	D3DXVECTOR3 MousePos = GetMousePosInWindow();
	CScene *pSceneGuild = NULL;
	int nPriority;

	//当り判定ある場合
	if (bHitPlayerAndFloor == true)
	{
		bool GuildIsExist = false;
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			CScene *pScene = NULL;
			nPriority = CPlayerGuild::GetPriority();
			pScene = CScene::GetScene(nCnt, nPriority);
			if (pScene == NULL) continue;

			//プレーヤーを検索
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER_GUILD)
			{
				GuildIsExist = true;
				pSceneGuild = pScene;
				break;
			}
		}

		if (GuildIsExist == false)
		{
			CPlayerGuild::Create(MousePos, D3DXVECTOR3(20, 100.0f, 0.0f), 100, PLAYER_TEX);
		}

		else
		{
			pSceneGuild->SetPos(m_pos);
			while (1)
			{
				D3DXVECTOR3 GuildPosNow = pSceneGuild->GetPos();
				D3DXVECTOR3 GuildSize = pSceneGuild->GetSize();
				bool HitAnyFloor = false;
				for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
				{
					CScene *pScene = NULL;
					nPriority = CFloor::GetPriority();
					pScene = CScene::GetScene(nCnt, nPriority);
					if (pScene == NULL) continue;
					if (pScene->GetObjType() == OBJTYPE_FLOOR)
					{
						D3DXVECTOR3 FloorPos = pScene->GetPos();
						D3DXVECTOR3 FloorSize = pScene->GetSize();

						bool HitRect = CHitCheck::HitRect(GuildPosNow, GuildSize, FloorPos, FloorSize);
						if (HitRect)
						{
							float FloorTop = FloorPos.y - FloorSize.y * 0.5;
							GuildPosNow.y = FloorTop - GuildSize.y*0.5 - 1;
							pSceneGuild->SetPos(D3DXVECTOR3(m_pos.x,GuildPosNow.y,0.0f));
							HitAnyFloor = true;
							break;
						}
					}
				}
				if (HitAnyFloor == false)
				{
					pSceneGuild->SetPos(D3DXVECTOR3(m_pos.x, GuildPosNow.y, 0.0f));
					break;
				}
			}
		}
	}

	else
	{
		for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
		{
			CScene *pScene = NULL;
			nPriority = CPlayerGuild::GetPriority();
			pScene = CScene::GetScene(nCnt, nPriority);
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
}

void CPlayer::HitFloorCanNotMove(void)
{
	bool hitAny = false;
	if (m_speed.x != 0) return;
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CFloor::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_FLOOR)
		{
			D3DXVECTOR3 FloorPos = pScene->GetPos();
			D3DXVECTOR3 FloorSize = pScene->GetSize();

			bool HitRect = CHitCheck::HitRect(m_pos, m_size, FloorPos, FloorSize);
			if (HitRect)
			{
				hitAny = true;
				m_speed.y = 0;
				m_StandFloor = true;

				float FloorTop = FloorPos.y - FloorSize.y * 0.5;
				float PlayerBottom = m_pos.y + m_size.y * 0.5;
				bool XSpeedZero = (PlayerBottom - FloorTop) > Y_DISTANCE_PLAYER_FLOOR;
				if (XSpeedZero)
				{
					if (m_pos.x < FloorPos.x)
					{
						float FloorLeft = FloorPos.x - FloorSize.x*0.5;
						m_pos.x = FloorLeft - m_size.x * 0.5 - 2;
					}

					if(m_pos.x > FloorPos.x)
					{
						float FloorRight = FloorPos.x + FloorSize.x*0.5;
						m_pos.x = FloorRight + m_size.x * 0.5 + 2;
					}
					m_speed.x = 0;
				}
				else
				{
					if ((PlayerBottom - FloorTop) > Y_PUSH) m_pos.y -= 1;
				}
				return;
			}
			else m_StandFloor = false;
		}

		else continue;
	}

	if (hitAny == false) m_speed.y = m_speedOld.y;
}

void CPlayer::HitFloorBeforeGameStart(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CFloor::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_FLOOR)
		{
			D3DXVECTOR3 FloorPos = pScene->GetPos();
			D3DXVECTOR3 FloorSize = pScene->GetSize();

			bool HitRect = CHitCheck::HitRect(m_pos, m_size, FloorPos, FloorSize);
			if (HitRect)
			{
				m_speed.y = 0;
				m_StandFloor = true;

				float FloorTop = FloorPos.y - FloorSize.y * 0.5;
				m_pos.y = FloorTop - m_size.y*0.5 + 2;
				return;
			}
			else m_StandFloor = false;
		}

		else continue;
	}
}

void CPlayer::HitOtherPlayer(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CPlayer::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer == this) continue;

			D3DXVECTOR3 OtherPlayerPos = pScene->GetPos();
			D3DXVECTOR3 OtherPlayerSize = pScene->GetSize();

			//矩形の上下左右辺の位置の計算
			float PlayerLeft = m_pos.x - m_size.x*0.5;
			float PlayerRight = m_pos.x + m_size.x*0.5;
			float PlayerTop = m_pos.y - m_size.y*0.5;
			float PlayerBottom = m_pos.y + m_size.y*0.5;

			float OtherPlayerLeft = OtherPlayerPos.x - OtherPlayerSize.x*0.5;
			float OtherPlayerRight = OtherPlayerPos.x + OtherPlayerSize.x*0.5;
			float OtherPlayerTop = OtherPlayerPos.y - OtherPlayerSize.y*0.5;
			float OtherPlayerBottom = OtherPlayerPos.y + OtherPlayerSize.y*0.5;

			bool HitX = (PlayerLeft <= OtherPlayerRight) && (PlayerRight >= OtherPlayerLeft);  //X方向判定
			bool HitY = (PlayerTop <= OtherPlayerBottom) && (PlayerBottom >= OtherPlayerTop);  //X方向判定

			if (HitX && HitY)
			{
				float DistanceToPlaySound = m_pos.x - m_posOld.x;
				DistanceToPlaySound = fabs(DistanceToPlaySound);
				if (DistanceToPlaySound > PLAYSOUND_DISTANCE)
				{
					PlaySound(SE_HASAMU);
				}
				m_speed.x = 0;
			}
		}

		else continue;
	}
}

void CPlayer::PlayHitSound(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CPlayer::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer == this) continue;

			D3DXVECTOR3 OtherPlayerPos = pScene->GetPos();
			D3DXVECTOR3 OtherPlayerSize = pScene->GetSize();

			//矩形の上下左右辺の位置の計算
			float PlayerLeft = m_pos.x - m_size.x*0.5;
			float PlayerRight = m_pos.x + m_size.x*0.5;
			float PlayerTop = m_pos.y - m_size.y*0.5;
			float PlayerBottom = m_pos.y + m_size.y*0.5;

			float OtherPlayerLeft = OtherPlayerPos.x - OtherPlayerSize.x*0.5;
			float OtherPlayerRight = OtherPlayerPos.x + OtherPlayerSize.x*0.5;
			float OtherPlayerTop = OtherPlayerPos.y - OtherPlayerSize.y*0.5;
			float OtherPlayerBottom = OtherPlayerPos.y + OtherPlayerSize.y*0.5;

			bool HitX = (PlayerLeft <= OtherPlayerRight) && (PlayerRight >= OtherPlayerLeft);  //X方向判定
			bool HitY = (PlayerTop <= OtherPlayerBottom) && (PlayerBottom >= OtherPlayerTop);  //X方向判定

			if (HitX && HitY)
			{
				float DistanceToPlaySound = m_pos.x - m_posOld.x;
				DistanceToPlaySound = fabs(DistanceToPlaySound);
				if (DistanceToPlaySound > PLAYSOUND_DISTANCE)
				{
					PlaySound(SE_HASAMU);
				}
			}
		}

		else continue;
	}
}

void CPlayer::ChangeDirectionSeeOtherPlayer(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CPlayer::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer == this) continue;

			D3DXVECTOR3 OtherPlayerPos = pScene->GetPos();

			if (m_StandFloorOld == false)
			{
				if (m_StandFloor != m_StandFloorOld)
				{
					if (m_pos.x < OtherPlayerPos.x)
					{
						m_bMoveDirection = true;
						pPlayer->SetMoveDirection(false);
					}
					else
					{
						m_bMoveDirection = false;
						pPlayer->SetMoveDirection(true);
					}
					CEarthquake::SetAngle(D3DX_PI);
					CEarthquake::SetAmplitude(10.0f);
					CEarthquake::SetDecrement(0.3f);
				}
			}
		}
	}
}

void CPlayer::ChangeDirectionSeeOtherPlayerGameNotStart(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CPlayer::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer == this) continue;

			D3DXVECTOR3 OtherPlayerPos = pScene->GetPos();

			if (m_pos.x < OtherPlayerPos.x)
			{
				m_bMoveDirection = true;
				pPlayer->SetMoveDirection(false);
			}
			else
			{
				m_bMoveDirection = false;
				pPlayer->SetMoveDirection(true);
			}
		}
	}
}

void CPlayer::PushOtherPlayer(int SceneID)
{
	CScene *pScene = NULL;
	int nPriority = CPlayer::GetPriority();
	pScene = CScene::GetScene(SceneID, nPriority);
	if (pScene == NULL) return;
	if (pScene->GetObjType() == OBJTYPE_PLAYER)
	{
		pScene->AddPowerX(m_mass*m_speed.x);  //ボールに押す力を与える
	}
}

bool CPlayer::GameNotStart(void)
{
	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_TUTORIAL)
	{
		if (CSceneTransition::GetTutorialMaster()->GetGameStartFlag() == true) return false;
		HitFloorBeforeGameStart();
		ChangeDirectionSeeOtherPlayerGameNotStart();
		return true;
	}

	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_TUTORIAL02)
	{
		if (CSceneTransition::GetTutorialMaster02()->GetGameStartFlag() == true) return false;
		HitFloorBeforeGameStart();
		ChangeDirectionSeeOtherPlayerGameNotStart();
		return true;
	}

	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_GAME)
	{
		if (CSceneTransition::GetGameMaster()->GetGameStartFlag() == true) return false;
		HitFloorBeforeGameStart();
		ChangeDirectionSeeOtherPlayerGameNotStart();
		return true;
	}

	return false;
}

void CPlayer::HitFloorNormal(void)
{
	int nPriority;
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		nPriority = CFloor::GetPriority();
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_FLOOR)
		{
			D3DXVECTOR3 FloorPos = pScene->GetPos();
			D3DXVECTOR3 FloorSize = pScene->GetSize();

			bool HitRect = CHitCheck::HitRect(m_pos, m_size, FloorPos, FloorSize);
			if (HitRect)
			{
				float FloorTop = FloorPos.y - FloorSize.y * 0.5;
				MouseCreatePlayerGuild(true);
				return;
			}
			else m_StandFloor = false;
		}

		else continue;
	}
	MouseCreatePlayerGuild(false);
}

void CPlayer::SetEarthquake(void)
{
	if (m_StandFloorOld == false)
	{
		if (m_StandFloor != m_StandFloorOld)
		{
			CEarthquake::SetAngle(D3DX_PI);
			CEarthquake::SetAmplitude(5.0f);
			CEarthquake::SetDecrement(0.3f);
			PlaySound(SE_HASAMU);              //落下音

			D3DXVECTOR2 ParticlePos = D3DXVECTOR2(m_pos.x, m_pos.y + m_size.y*0.5);
			if (NULL != m_ParticleHitFloor)
			{
				m_ParticleHitFloor->SetPosXYZ(D3DXVECTOR3(ParticlePos.x, ParticlePos.y,0.0f));
				m_HitFloorTime = HITFLOOR_PARTICLE_LIFE;
			}
			else
			{
				m_ParticleHitFloor = CParticle::Create(ParticlePos.x, ParticlePos.y, 0.000, 0.000, 65.900, 65.900, 65.900, 0.009, 0.009, 0.009, 2.800, 2.800, 2.800, -0.008, -0.008, -0.008, 9, 46.000, 0.000, 0.000, 0.61, 0.46, 0.34, 0.38, 0.000, -6.400, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 199.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, PARTICLE_EF02_TEX);
				m_HitFloorTime = HITFLOOR_PARTICLE_LIFE;
			}

		}
	}
}

void CPlayer::MoveParticle(void)
{
	float DistanceToMakeParticle = m_pos.x - m_posOld.x;
	DistanceToMakeParticle = fabs(DistanceToMakeParticle);
	if (DistanceToMakeParticle <= MAKE_PARTICLE_DISTANCE)
	{
		if (m_Particle != NULL)
		{
			m_Particle->Uninit();
			m_Particle = NULL;
		}
		return;
	}

	//距離満足した場合
	//左に移動する場合
	D3DXVECTOR2 ParticlePos = D3DXVECTOR2(m_pos.x, m_pos.y + m_size.y*0.5);   //発射位置

	float fSpeed = m_speed.x;
	fSpeed = fabs(fSpeed);
	int nBaseAngle = 0;
	if (m_bMoveDirection == false) nBaseAngle = 0;
	else nBaseAngle = 135;

	if (NULL != m_Particle)
	{
		m_Particle->SetPosXYZ(D3DXVECTOR3(ParticlePos.x, ParticlePos.y,0.0f));
		return;
	}
	m_Particle = CParticle::Create(ParticlePos.x, ParticlePos.y, 0.000, 
		0.000, 65.900, 65.900, 65.900, 
		0.000, 0.000, 0.000, 
		3.100, 3.100, 3.100,
		0.042, 0.042, 0.042,
		5, 60.000, 0.000, 0.000,
		0.61, 0.46, 0.00, 0.17, 0.000, -6.400, 0.000, 5.000, 5.000, 5.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 199.000, 0.000, 0.00, 0.00, 0.00, 0.00, 0, -1, PARTICLE_EF02_TEX);
}

int CPlayer::GetPlayerId(void)
{
	return m_PlayerID;
}

void CPlayer::AddMove(float SpeedX)
{
	m_speed.x = SpeedX;
}

D3DXVECTOR3 CPlayer::GetSpeed(void)
{
	return m_speed;
}
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}

void CPlayer::SetPosition(const D3DXVECTOR3& playerPos)
{
	m_pos = playerPos;
}