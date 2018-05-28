#include "CTextBox.h"
#include "CNumber.h"
#include "CResult.h"
#include "CResultScore.h"
#include "SceneTransition.h"

#define SCROLL_SPEED (0.005f)

int CTextBox::s_nPriority = 5;

CTextBox::CTextBox() : CScene2D(5)
{
}

CTextBox::CTextBox(int Priority) : CScene2D(Priority)
{
	
}

CTextBox::~CTextBox()
{

}

//テキストボックスのインスタンスを生成する関数
CTextBox *CTextBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha, const char* filePass)
{
	CTextBox *pTextBox;
	pTextBox = new CTextBox(s_nPriority);
	pTextBox->Init(pos, size, endPos, alpha);
	pTextBox->LoadTexture(filePass);
	return pTextBox;
}

//テキストボックスの初期化
HRESULT CTextBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, int alpha)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(OBJTYPE_TEXTBOX);
	m_nAlpha = alpha;
	m_posU = 0.0f;
	m_posV = 0.0f;
	m_endPos = endPos;

	CScene2D::VertexLock();
	return S_OK;
}

//更新処理
void CTextBox::Update(void)
{
	CScene2D::VertexLock();
}

//描画処理
void CTextBox::Draw(void)
{
	CScene2D::Draw();
}

//終了処理
void CTextBox::Uninit(void)
{
	CScene2D::Uninit();
}