#include "CSpring.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CSpring::s_nPriority = 3;

CSpring::CSpring() : CScene2D (3)
{

}

CSpring::CSpring(int nPriority) : CScene2D(nPriority)
{

}

CSpring::~CSpring()
{

}

//プレーヤーのインスタンスを生成する関数
CSpring *CSpring::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fElasticModulus , bool bFixDirection, const char* filePass)
{
	CSpring *pSpring;
	pSpring = new CSpring(s_nPriority);
	pSpring->Init(pos, size);
	pSpring->LoadTexture(filePass);
	pSpring->SetElasticModulus(fElasticModulus);
	pSpring->SetFixDirection(bFixDirection);
	return pSpring;
}

//プレーヤーの初期化
HRESULT CSpring::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_SPRING);
	m_sizeOrigin = m_size;                   //元のサイズを保存
	m_posOrigin = m_pos;                   //元の位置保存
	m_PowerX = 0;
	m_ReturnSizeFlag = false;
	return S_OK;
}

//更新処理
void CSpring::Update(void)
{
	ReturnAction();           //元のサイズに戻るアクション
	CScene2D::VertexLock();
}

//描画処理
void CSpring::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CSpring::Uninit(void)
{
	CScene2D::Uninit();
}

void CSpring::ReturnAction(void)
{
	if (m_ReturnSizeFlag == false) return;
	if (m_sizeOrigin.x == m_size.x) return;

	//左固定
	m_size.x += 10;
	if (m_size.x > m_sizeOrigin.x)
	{
		m_size.x = m_sizeOrigin.x;
		m_ReturnSizeFlag = false;
	}
	if(m_bFixDirection == false)
	{
		m_size.x += 4;
		float Left = m_posOrigin.x - m_sizeOrigin.x*0.5;
		m_pos.x = Left + m_size.x*0.5;
	}
	//右固定
	else
	{
		m_size.x += 4;
		float Right = m_posOrigin.x + m_sizeOrigin.x*0.5;
		m_pos.x = Right - m_size.x*0.5;
	}
}