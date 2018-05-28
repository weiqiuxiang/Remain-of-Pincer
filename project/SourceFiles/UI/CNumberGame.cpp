#include "CNumberGame.h"
#include "SceneTransition.h"
#include "renderer.h"
#include "CScore.h"
#include "TexManager.h"

CNumberGame::CNumberGame()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nValue = 0;
}

CNumberGame::~CNumberGame()
{

}

//
//定番関数
////////////////////////////////////////////////
HRESULT CNumberGame::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const char* TexPass)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();
	VERTEX_2D *pVtx = NULL;

	// ポリゴンの位置を設定
	m_pos = pos;
	m_size = size;

	m_TexID = CTexManager::LoadTex(TexPass);    //テクスチャ読み込み

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	/***************************仮想アドレスを取得しバッファをロックする************************************/
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ローカル座標
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + SCORE_WIDTH, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + SCORE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + SCORE_WIDTH, m_pos.y + SCORE_HEIGHT, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();

	return S_OK;
}

void CNumberGame::Uninit(void)
{
	
}

void CNumberGame::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();
	VERTEX_2D *pVtx = NULL;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ローカル座標
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(m_nValue*0.1, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nValue*0.1 + 0.1, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nValue*0.1, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nValue*0.1 + 0.1, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();
}

void CNumberGame::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneTransition::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));                     //VRAMからGPUにデータをストリーム

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, CTexManager::UseTex(m_TexID));												 //テクスチャの設定

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);                                  //描画
}

//
//ファクション関数
////////////////////////////////////////////////
CNumberGame *CNumberGame::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const char* TexPass, int Number)
{
	CNumberGame *pScore = new CNumberGame;
	pScore->Init(pos,size, TexPass);
	pScore->SetNumber(Number);
	return  pScore;
}

void CNumberGame::SetNumber(int nNumber)
{
	m_nValue = max(0,nNumber);
	m_nValue = min(9, m_nValue);
}

void CNumberGame::SetPos(const D3DXVECTOR3 *pos)
{
	m_pos = *pos;
}