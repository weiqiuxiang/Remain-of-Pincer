#include "CFontUIScale.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CFontUIScale::s_nPriority = 5;

CFontUIScale::CFontUIScale() : CScene2D(3)
{

}

CFontUIScale::CFontUIScale(int nPriority) : CScene2D(nPriority)
{

}

CFontUIScale::~CFontUIScale()
{

}

//プレーヤーのインスタンスを生成する関数
CFontUIScale *CFontUIScale::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, const D3DXVECTOR3 &ScalePoint,int nAlpha, const char* filePass)
{
	CFontUIScale *pPlayerArrow;
	pPlayerArrow = new CFontUIScale(s_nPriority);
	pPlayerArrow->Init(pos, size);
	pPlayerArrow->LoadTexture(filePass);
	pPlayerArrow->SetAlpha(nAlpha);
	pPlayerArrow->SetScalePoint(ScalePoint);
	return pPlayerArrow;
}

//プレーヤーの初期化
HRESULT CFontUIScale::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_NONE);
	m_bMouseLock = true;

	//スケール関係
	m_OriginPos = pos;
	m_OriginSize = size;
	m_Scale = 1.0f;

	return S_OK;
}

//更新処理
void CFontUIScale::Update(void)
{
	D3DXVECTOR3 DistanceFromSP = m_OriginPos - m_ScalePoint;   //元原点とスケール中心の差分
	DistanceFromSP = DistanceFromSP * m_Scale;      //スケールの後の差分サイズ
	m_pos = m_ScalePoint + DistanceFromSP;    //スケールCenter座標を求める
	m_size = m_OriginSize * m_Scale;      //スケール後のサイズ

	CScene2D::VertexLock();
}

//描画処理
void CFontUIScale::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CFontUIScale::Uninit(void)
{
	CScene2D::Uninit();
}