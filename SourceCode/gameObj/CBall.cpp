#include "CBall.h"
#include "SceneTransition.h"
#include "renderer.h"
#include "CExplosion.h"
#include "CScore.h"
#include "CPlayer.h"
#include "hitCheck.h"
#include "CResultScore.h"
#include "CFloor.h"

int CBall::s_nPriority = 4;

#define DRAG_COEFFI_BALL (0.3f)  //ボールの抗力係数
#define Y_DISTANCE_BALL_FLOOR (10.0f)
#define Y_PUSH (2.0f)
#define BALL_IN_PLAYER_X_SPEED (10.0f)
#define BALL_IN_FLOOR_X_SPEED (4.0f)

#define DEAD_JUMP_SPEED (20.0f)
#define DAMAGE_TEX_SPEEDX (0.01f)
#define RORATE_SPEED (D3DX_PI*0.04)

CBall::CBall() : CScene2D(4)
{
	m_posOld = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CBall::CBall(int Priority) : CScene2D(Priority)
{
	
}

CBall::~CBall()
{

}

//プレーヤーのインスタンスを生成する関数
CBall *CBall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const char* filePass)
{
	CBall *pBall;
	pBall = new CBall(s_nPriority);
	pBall->Init(pos, size);
	pBall->LoadTexture(filePass);
	return pBall;
}

//プレーヤーの初期化
HRESULT CBall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_BALL);
	//当り判定用サイズ設定
	size.x -= 10;
	size.y -= 15;
	m_HitSize = size;

	m_mass = 2.0f;
	m_StandFloor = false;
	m_PowerOther = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDead = false;
	//UV部分
	m_nCntChangeUV = 0;
	m_UV = D3DXVECTOR2(0.0f, 0.0f);
	m_UVWH = D3DXVECTOR2(0.25f, 1.0f);
	m_nCntMotionChange = 1;
	m_TexChangeMove = false;
	m_fAngle = 0;
	m_bMoveDir = true;                 //右方向はデフォルト方向
	CScene2D::VertexLock();
	return S_OK;
}

//更新処理
void CBall::Update(void)
{
	//テクスチャ切り替えフラグ
	if (fabs(m_speed.x) > DAMAGE_TEX_SPEEDX) {   //ダメージモーション
		if (true != m_TexChangeMove) {
			m_fAngle = 0;                //角度は0度から
			m_TexChangeMove = true;
			m_size = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
			LoadTexture(BALL_DAMAGE_TEX);               //テクスチャ変更
		}
	}
	else {                             //ニュートラルモーション
		if (false != m_TexChangeMove) {
			m_TexChangeMove = false;
			m_UV = D3DXVECTOR2(0.0f, 0.0f);
			m_UVWH = D3DXVECTOR2(0.25f, 1.0f);
			m_size = D3DXVECTOR3(30.0f, 45.0f, 0.0f);
			LoadTexture(BALL_TEX);                      //テクスチャ変更
		}
	}

	//進行方向切り替えフラグ
	if (m_speed.x >= 0) { m_bMoveDir = true; }
	else m_bMoveDir = false;

	//頂点ロックパターン
	if(m_TexChangeMove == false) CScene2D::VertexLock();
	else {
		if(false == m_bMoveDir) VertexLockRorate(-RORATE_SPEED);
		else VertexLockRorate(RORATE_SPEED);
	}

	//早期リターン
	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_NAME::SCENE_EDITOR) return;
	if (CSceneTransition::GetGameMaster()->GetPauseFlag() == true) { return; }

	//UV変更(ニュートラル状態のみ)
	if (false == m_TexChangeMove) {
		m_nCntMotionChange++;
		m_nCntMotionChange = m_nCntMotionChange % 10;
		if (m_nCntMotionChange == 0)
		{
			m_nCntChangeUV++;
			m_nCntChangeUV = m_nCntChangeUV % 4;
			m_UV.x = m_nCntChangeUV*0.25f;
		}
	}

	if (m_bDead == false) BallAliveAction();           //生きている時のアクション
	else BallDeadAction();                             //死んだ時のアクション
}

void CBall:: VertexLockRorate(float fAngle)
{
	m_fAngle += fAngle;         //角度増加

	//角度範囲制限
	if (m_fAngle > D3DX_PI) m_fAngle -= D3DX_PI * 2;
	if (m_fAngle < -D3DX_PI) m_fAngle += D3DX_PI * 2;

	//頂点ロック必要変数
	VERTEX_2D *pVtx = NULL;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	//回転後四頂点の座標計算
	double X1, Y1, X2, Y2, X3, Y3, X4, Y4;             //左上,右下座標
	double Xc1, Yc1, Xc2, Yc2, Xc3, Yc3, Xc4, Yc4;         //回転した後の座標
	double XC, YC;                                   //中心座標

	D3DXVECTOR3 HalfSize = m_size * 0.5;

	X1 = m_pos.x - HalfSize.x;
	Y1 = m_pos.y - HalfSize.y;
	X2 = m_pos.x + HalfSize.x;
	Y2 = m_pos.y - HalfSize.y;
	X3 = m_pos.x - HalfSize.x;
	Y3 = m_pos.y + HalfSize.y;
	X4 = m_pos.x + HalfSize.x;
	Y4 = m_pos.y + HalfSize.y;

	XC = m_pos.x;
	YC = m_pos.y;
	float CosAngle = cos(m_fAngle);
	float SinAngle = sin(m_fAngle);

	Xc1 = (X1 - XC)*CosAngle - (Y1 - YC)*SinAngle + XC;
	Yc1 = (X1 - XC)*SinAngle + (Y1 - YC)*CosAngle + YC;

	Xc2 = (X2 - XC)*CosAngle - (Y2 - YC)*SinAngle + XC;
	Yc2 = (X2 - XC)*SinAngle + (Y2 - YC)*CosAngle + YC;

	Xc3 = (X3 - XC)*CosAngle - (Y3 - YC)*SinAngle + XC;
	Yc3 = (X3 - XC)*SinAngle + (Y3 - YC)*CosAngle + YC;

	Xc4 = (X4 - XC)*CosAngle - (Y4 - YC)*SinAngle + XC;
	Yc4 = (X4 - XC)*SinAngle + (Y4 - YC)*CosAngle + YC;

	//頂点ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(Xc1, Yc1, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Xc2, Yc2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Xc3, Yc3, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Xc4, Yc4, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);
	pVtx[1].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);
	pVtx[2].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);
	pVtx[3].color = D3DCOLOR_RGBA(m_Color.r, m_Color.g, m_Color.b, m_nAlpha);

	m_pVtxBuff->Unlock();
}

void CBall::BallAliveAction(void)
{
	//座標保存
	m_posOld = m_pos;

	//押す力
	HitPlayer();
	float PushPower = 0;
	if (m_powerBetween.powerLeft < 0) PushPower = m_powerBetween.powerLeft;
	if (m_powerBetween.powerRight > 0) PushPower = m_powerBetween.powerRight;

	//挟まれる判定
	bool BetweenYes = m_powerBetween.powerLeft < 0 && m_powerBetween.powerRight > 0;
	if (BetweenYes == true)   //挟まれたら
	{
		CResultScore::IncrementKillEnemyOneTurn();
		m_UV = D3DXVECTOR2(0.0f,1.0f);
		m_UVWH = D3DXVECTOR2(0.25f,-1.0f);
		m_speed.y -= DEAD_JUMP_SPEED;
		m_bDead = true;
		return;
	}

	PowerReset();                                                              //押される力を0にする

	//重力
	float Gravity = m_mass * GRAVITY_ACC;

	//抗力
	D3DXVECTOR3 Drag = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //抗力
	Drag.x = -m_speed.x * DRAG_COEFFI_BALL;            //x方向抗力
	Drag.y = -m_speed.y * DRAG_COEFFI_BALL;            //y方向抗力

	//端の弾く力
	bool BorderlineLeft = (m_pos.x - m_HitSize.x*0.5) < 10;
	bool BorderlineRight = (m_pos.x + m_HitSize.x*0.5) > SCREEN_WIDTH - 10;
	if (BorderlineLeft == true)
	{
		m_pos.x = 20;
		m_PowerOther.x += 4.0f;
	}
	if (BorderlineRight == true)
	{
		m_pos.x = SCREEN_WIDTH - 20;
		m_PowerOther.x -= 4.0f;
	}

	//外力合計
	float PowerX = PushPower + Drag.x + m_PowerOther.x;
	float PowerY = Gravity + Drag.y;

	//外力を0にする
	m_PowerOther = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//加速度計算
	float AccX = PowerX / m_mass;
	float AccY = PowerY / m_mass;

	//速度計算
	m_speed.x += AccX;
	m_speed.y += AccY;

	//地面との当り判定
	HitFloor();

	//移動量計算
	if (m_StandFloor == true) m_pos.x += m_speed.x;
	m_pos.y += m_speed.y;
}

void CBall::BallDeadAction(void)
{
	float Gravity = m_mass * GRAVITY_ACC;       //重力影響

	D3DXVECTOR3 Drag = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //抗力
	Drag.y = -m_speed.y * DRAG_COEFFI_BALL;              //y方向抗力

	float PowerY = Gravity + Drag.y;                     //Y方向力合計

	float AccY = PowerY / m_mass;                        //Y方向加速度

	m_speed.y += AccY;                                   //速度計算

	m_pos.y += m_speed.y;                                //位置移動

	//境界線外に行く判定
	bool BorderlineOut = (m_pos.y + m_HitSize.y*0.5) > SCREEN_HEIGHT*1.2;
	if (BorderlineOut == true)
	{
		Uninit();        //自分自身を消す
		return;
	}
}

//描画処理
void CBall::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CBall::Uninit(void)
{
	CScene2D::Uninit();
}

void CBall::HitFloor(void)
{
	int nPriority = CFloor::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_FLOOR)
		{
			D3DXVECTOR3 FloorPos = pScene->GetPos();
			D3DXVECTOR3 FloorSize = pScene->GetSize();

			bool HitRect = CHitCheck::HitRect(m_pos, m_HitSize, FloorPos, FloorSize);
			if (HitRect)
			{
				m_speed.y = 0;
				m_StandFloor = true;

				float FloorTop = FloorPos.y - FloorSize.y * 0.5;
				float PlayerBottom = m_pos.y + m_HitSize.y * 0.5;
				bool XSpeedZero = (PlayerBottom - FloorTop) > Y_DISTANCE_BALL_FLOOR;
				if (XSpeedZero)
				{
					if (m_pos.x < FloorPos.x) m_speed.x = -BALL_IN_FLOOR_X_SPEED;
					else m_speed.x = BALL_IN_FLOOR_X_SPEED;
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
}

void CBall::HitPlayer(void)
{
	if (GameNotStart() == true) return; //ゲームを始めることができない状態の判定

	int nPriority = CPlayer::GetPriority();
	for (int nCnt = 0; nCnt < SCENE_MAX_NUM; nCnt++)
	{
		CScene *pScene = NULL;
		pScene = CScene::GetScene(nCnt, nPriority);
		if (pScene == NULL) continue;
		if (pScene->GetObjType() == OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = dynamic_cast <CPlayer *> (pScene);
			if (pPlayer == NULL) continue;
			if (pPlayer->GetMouseLock() == true) continue;

			//プレーヤーからPos,PosOld,Sizeなどを取得
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
			D3DXVECTOR3 PlayerPosOld = pPlayer->GetPosOld();
			D3DXVECTOR3 PlayerSize = pPlayer->GetSize();

			//当り判定
			bool isPlayerHitBall = CHitCheck::HitCheckMoveAndStill_RectX(PlayerPos, PlayerPosOld, PlayerSize, m_pos, m_HitSize);
			bool isBallHitPlayer = CHitCheck::HitCheckMoveAndStill_RectX(m_pos, m_posOld, m_HitSize, PlayerPos, PlayerSize);

			//当たった時の処理
			if (isPlayerHitBall || isBallHitPlayer)
			{
				if (PlayerPos.x < PlayerPosOld.x)//プレーヤー左に行く
				{
					m_pos.x = PlayerPos.x - PlayerSize.x*0.5 - m_HitSize.x*0.5;//当り判定の範囲外に座標移動
					m_powerBetween.powerLeft = -10; //押し出す
				}
				else if ((PlayerPos.x > PlayerPosOld.x)) //プレーヤー右に行く
				{
					m_pos.x = PlayerPos.x + PlayerSize.x*0.5 + m_HitSize.x*0.5;//当り判定の範囲外に座標移動
					m_powerBetween.powerRight = 10; //押し出す
				}
				
				else //プレーヤー動いていない(バグ)
				{
					if (isBallHitPlayer)
					{
						if (m_posOld.x < PlayerPos.x) m_powerBetween.powerLeft = -5;
						else m_powerBetween.powerRight = 5;
					}
				}
			}
		}

		else continue;
	}
}

bool CBall::GameNotStart(void)
{
	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_TUTORIAL)
	{
		if (CSceneTransition::GetTutorialMaster()->GetGameStartFlag() == true) return false;
		return true;
	}

	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_TUTORIAL02)
	{
		if (CSceneTransition::GetTutorialMaster02()->GetGameStartFlag() == true) return false;
		return true;
	}

	if (CSceneTransition::GetSceneNow() == CSceneTransition::SCENE_GAME)
	{
		if (CSceneTransition::GetGameMaster()->GetGameStartFlag() == true) return false;
		return true;
	}

	return false;
}