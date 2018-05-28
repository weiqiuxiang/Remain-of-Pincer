#include "CTitleTraBotton.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CTitleTraBotton::s_nPriority = 5;

CTitleTraBotton::CTitleTraBotton() : CScene2D(3)
{

}

CTitleTraBotton::CTitleTraBotton(int nPriority) : CScene2D(nPriority)
{
	
}

CTitleTraBotton::~CTitleTraBotton()
{

}

//プレーヤーのインスタンスを生成する関数
CTitleTraBotton *CTitleTraBotton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TRA_TYPE TraType,const char* filePass)
{
	CTitleTraBotton *pPlayerSelecter;
	pPlayerSelecter = new CTitleTraBotton(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	pPlayerSelecter->m_TraType = TraType;
	return pPlayerSelecter;
}

CTitleTraBotton *CTitleTraBotton:: Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStageNum, const char* filePass)
{
	CTitleTraBotton *pPlayerSelecter;
	pPlayerSelecter = new CTitleTraBotton(s_nPriority);
	pPlayerSelecter->Init(pos, size);
	pPlayerSelecter->LoadTexture(filePass);
	nStageNum = max(1, nStageNum);
	pPlayerSelecter->SetStageNum(nStageNum);
	pPlayerSelecter->m_TraType = TYPE_STAGE_NUM;
	return pPlayerSelecter;
}

//プレーヤーの初期化
HRESULT CTitleTraBotton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TITLE_TRA_OBJ);
	m_sizeOrigin = m_size;                      //元のサイズ保存
	return S_OK;
}

//更新処理
void CTitleTraBotton::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CTitleTraBotton::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CTitleTraBotton::Uninit(void)
{
	CScene2D::Uninit();
}