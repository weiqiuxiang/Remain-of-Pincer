#include "CFade.h"
#include "SceneTransition.h"
#include "renderer.h"
#include "TexManager.h"
#include "CEarthquake.h"

CFade::CFade() :
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_pVtxBuffer(NULL),
	m_TexID(NULL)
{
	m_RGBA = {255,255,255,255};
}

CFade::CFade(const D3DXVECTOR3 &Pos, const D3DXVECTOR3 &pSize) :
	m_size(pSize),
	m_pVtxBuffer(NULL),
	m_TexID(NULL)
{
	m_RGBA = { 255,255,255,255 };
}

CFade::~CFade()
{
	if (m_TexID != NULL)
	{
		delete m_TexID;
		m_TexID = NULL;
	}

	if (m_pVtxBuffer != NULL)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}
}


HRESULT CFade::Init(const D3DXVECTOR3 &Pos, const D3DXVECTOR3 &pSize, const char* filePass)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();
	if (m_TexID == NULL) m_TexID = new TEX_ID;   //テクスチャIDの実体化
	
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffer, NULL)))
	{
		MessageBox(NULL, "頂点バッファ確保が失敗しました", "エラー", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//テクスチャ読み込み
	*m_TexID = CTexManager::LoadTex(filePass);    //テクスチャをロードする

	m_pos = Pos;
	m_size = pSize;
	m_RGBA = { 255,255,255,255 };
	m_UV = D3DXVECTOR2(0.0f, 0.0f);
	m_UVWH = D3DXVECTOR2(1.0f, 1.0f);

	SetRenderStates();                  //レンダーステートに関する諸設定
	VertexBufferLock();                 //頂点ロック
	
	return S_OK;
}

void CFade::Update(void)
{
	SetRenderStates();
	VertexBufferLock();
}

void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, CTexManager::UseTex(*m_TexID));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);                    //描画
}

void CFade::Uninit(void)
{
	if (m_TexID != NULL)
	{
		delete m_TexID;
		m_TexID = NULL;
	}

	if (m_pVtxBuffer != NULL)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}
}

void CFade::SetRenderStates(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneTransition::GetRenderer()->GetDevice();

	//レンダステート設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);   //引数1:設定名カリング 引数2:設定値(D3DCULL_CCW:逆時計回りを裏面をする)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}

void CFade::VertexBufferLock(void)
{
	VERTEX_2D *pVtx = NULL;

	D3DXVECTOR3 HalfSize = m_size * 0.5;

	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - HalfSize.x, m_pos.y - HalfSize.y + CEarthquake::GetChangeY(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + HalfSize.x, m_pos.y - HalfSize.y + CEarthquake::GetChangeY(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - HalfSize.x, m_pos.y + HalfSize.y + CEarthquake::GetChangeY(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + HalfSize.x, m_pos.y + HalfSize.y + CEarthquake::GetChangeY(), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].color = D3DCOLOR_RGBA(m_RGBA.r, m_RGBA.g, m_RGBA.b, m_RGBA.a);
	pVtx[1].color = D3DCOLOR_RGBA(m_RGBA.r, m_RGBA.g, m_RGBA.b, m_RGBA.a);
	pVtx[2].color = D3DCOLOR_RGBA(m_RGBA.r, m_RGBA.g, m_RGBA.b, m_RGBA.a);
	pVtx[3].color = D3DCOLOR_RGBA(m_RGBA.r, m_RGBA.g, m_RGBA.b, m_RGBA.a);

	//ポリゴン描画する前にテクスチャをセット
	pVtx[0].tex = D3DXVECTOR2(m_UV.x, m_UV.y);
	pVtx[1].tex = D3DXVECTOR2(m_UV.x + m_UVWH.x, m_UV.y);
	pVtx[2].tex = D3DXVECTOR2(m_UV.x, m_UV.y + m_UVWH.y);
	pVtx[3].tex = D3DXVECTOR2(m_UV.x + m_UVWH.x, m_UV.y + m_UVWH.y);

	m_pVtxBuffer->Unlock();
}

//セッター
void CFade::SetLayerR(int Value)
{
	if (Value < 0) { m_RGBA.r = 0; return; }
	if (Value > 255){ m_RGBA.r = 255; return; }
	m_RGBA.r = Value;
}
void CFade::SetLayerG(int Value)
{
	if (Value < 0) { m_RGBA.g = 0; return; }
	if (Value > 255) { m_RGBA.g = 255; return; }
	m_RGBA.g = Value;
}
void CFade::SetLayerB(int Value) 
{
	if (Value < 0) { m_RGBA.b = 0; return; }
	if (Value > 255) { m_RGBA.b = 255; return; }
	m_RGBA.b = Value;
}
void CFade::SetLayerA(int Value) 
{
	if (Value < 0) { m_RGBA.a = 0; return; }
	if (Value > 255) { m_RGBA.a = 255; return; }
	m_RGBA.a = Value;
}

void CFade::SetRGBA(RGBA rgba)
{
	SetLayerR(rgba.r);
	SetLayerG(rgba.g);
	SetLayerB(rgba.b);
	SetLayerA(rgba.a);
}
void CFade::ChangeAlpha(int ChangeValue) 
{
	m_RGBA.a += ChangeValue;
	if (m_RGBA.a < 0) { m_RGBA.a = 0; return; }
	if (m_RGBA.a > 255) { m_RGBA.a = 255; return; }
}