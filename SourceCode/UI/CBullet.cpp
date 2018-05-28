#include "CBullet.h"
#include "CManager.h"
#include "renderer.h"
#include "CExplosion.h"
#include "CScore.h"
#include "CEnemy.h"

//前方宣言
class CManager;

//グロバール宣言
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

CBullet::CBullet()
{
	 
}

CBullet::~CBullet()
{

}

//プレーヤーのインスタンスを生成する関数
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 speed)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Init(pos);
	pBullet->BindTexture(m_pTexture);                        //テクスチャを割り当てる
	return pBullet;
}

//プレーヤーの初期化
HRESULT CBullet::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos);
	CScene2D::SetObjType(OBJTYPE_BULLET);
	return S_OK;
}

//更新処理
void CBullet::Update(void)
{
	VERTEX_2D *pVtx = NULL;

	if (m_pVtxBuff != NULL)
	{

		/***************************仮想アドレスを取得しバッファをロックする************************************/
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//ローカル座標
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y + 100.0f, 0.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		m_pVtxBuff->Unlock();
	}

	else
	{
		return;
	}

	m_pos.y -= 10;

	if (
		(m_pos.x < 0 || m_pos.x > SCREEN_WIDTH) ||
		(m_pos.y < 0 || m_pos.y > SCREEN_HEIGHT)
		)
	{
		Uninit();
		return;
	}

	for(int nCntScene = 0; nCntScene < SCENE_MAX_NUM; nCntScene++)
	{
		//シーン取得
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		//シンが存在する
		if(pScene != NULL)
		{
			CScene::OBJTYPE Objtype;
			Objtype = pScene->GetObjType();
			if(Objtype == CScene::OBJTYPE_ENEMY)
			{
				CEnemy *pEnemy = NULL;
				pEnemy = dynamic_cast<CEnemy*>(pScene);  //ダウンキャスト

				if (pEnemy != NULL)
				{
					D3DXVECTOR2 posEnemy;
					posEnemy = pEnemy->GetPos();             //座標代入

					//当り判定
					if ((m_pos.x <= (posEnemy.x + OBJ_WIDTH)) &&
						((m_pos.x + OBJ_WIDTH) >= posEnemy.x) &&
						(m_pos.y <= (posEnemy.y + OBJ_HEIGHT)) &&
						((m_pos.y + OBJ_HEIGHT) >= posEnemy.y)
						)
					{
						//弾を破棄
						Uninit();

						pEnemy->SetHit(true);
						pEnemy->SetLifeDown(1);
						
						return;
					}
				}
			}
		}
	}
}

//描画処理
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//テクスチャの読みごみ
HRESULT CBullet::Load(int TexType)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	if(m_pTexture == NULL)
	{
		//テクスチャの読み込み
		if (m_pTexture == NULL)
		{
			//
			//テクスチャ読み込む]
			//////////////////////////////////////////////////////
			switch (TexType)
			{
			case 0:
				// テクスチャの生成
				if (FAILED(D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAME, &m_pTexture)))
				{
					MessageBox(NULL, "テクスチャの読み込みが失敗しました", "エラー", MB_OK | MB_ICONHAND);
					return E_FAIL;
				}
				break;
			case 1:
				// テクスチャの生成
				if (FAILED(D3DXCreateTextureFromFile(pDevice, POLYGON01_TEXTURENAME, &m_pTexture)))
				{
					MessageBox(NULL, "テクスチャの読み込みが失敗しました", "エラー", MB_OK | MB_ICONHAND);
					return E_FAIL;
				}
				break;
			default:
				// テクスチャの生成
				if (FAILED(D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAME, &m_pTexture)))
				{
					MessageBox(NULL, "テクスチャの読み込みが失敗しました", "エラー", MB_OK | MB_ICONHAND);
					return E_FAIL;
				}
				break;
			}
		}
	}

	return S_OK;
}

//テクスチャの破棄
void CBullet::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}