#include "CScoreScale.h"
#include "CNumber.h"

int CScoreScale::s_nPriority = 5;

CScoreScale::CScoreScale() : CScene(3)
{
	m_apNumber = NULL;
	m_nScore = 0;
}

CScoreScale::CScoreScale(int nPriority) : CScene(nPriority)
{
	m_apNumber = NULL;
	m_nScore = 0;
}

CScoreScale::~CScoreScale()
{
	if (NULL != m_apNumber)
	{
		delete[] m_apNumber;
		m_apNumber = NULL;
	}
}

//定番関数
HRESULT CScoreScale::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& NumberSize, int nDigit, const char* TexPass)
{
	//パラメータを初期化する
	m_nScore = 0;
	m_pos = pos;
	m_NumberSize = NumberSize;
	m_OriginSize = m_NumberSize;                  //元のサイズ保存
	m_NumberDistance = NumberSize.x;
	m_nDigit = max(1,nDigit);
	m_Scale = 1.0f;

	if(NULL != m_apNumber)
	{
		delete[] m_apNumber;
		m_apNumber = NULL;
	}
	m_apNumber = NULL;
	m_apNumber = new CNumberGame[m_nDigit];      //桁分確保

	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		D3DXVECTOR3 NumberPos;
		NumberPos = D3DXVECTOR3(m_pos.x + (m_nDigit - nCnt)*m_NumberDistance, m_pos.y, 0.0f);
		m_apNumber[nCnt].Init(NumberPos, m_NumberSize, TexPass);
	}

	float CenterX = (m_pos.x + m_pos.x + (m_nDigit-1)*m_NumberDistance) * 0.5;
	float CenterY = (m_pos.y + m_pos.y + NumberSize.y) *0.5;

	m_OriginPos = D3DXVECTOR3(CenterX, CenterY,0.0f);      //元の中心座標保存
	m_CenterPos = m_OriginPos;                             //センター中心座標の初期値設定

	CNumber::LoadTex();

	return S_OK;
}
void CScoreScale::Uninit(void)
{
	if (NULL != m_apNumber)
	{
		delete[] m_apNumber;
		m_apNumber = NULL;
	}

	this->Release();
}
void CScoreScale::Update(void)
{
	if (NULL == m_apNumber) return;
	int nScore = m_nScore;

	//ナンバーのサイズコントロール
	D3DXVECTOR3 DistanceFromSP = m_OriginPos - m_ScalePoint;   //元原点とスケール中心の差分
	DistanceFromSP = DistanceFromSP * m_Scale;      //スケールの後の差分サイズ
	m_CenterPos = m_ScalePoint + DistanceFromSP;    //スケールCenter座標を求める

	m_NumberSize = m_OriginSize * m_Scale;          //スケール後サイズ
	m_NumberDistance = m_NumberSize.x;              //スケール数字の間の幅

	float TotalSizeX = m_NumberSize.x * m_nDigit;
	float TotalSizeY = m_NumberSize.y;

	//変化後の左上座標を求め
	m_pos.x = m_CenterPos.x - TotalSizeX;
	m_pos.y = m_CenterPos.y - TotalSizeY;

	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		int nNumber;
		nNumber = nScore % 10;
		nScore = nScore / 10;

		D3DXVECTOR3 NumberPos;
		NumberPos = D3DXVECTOR3(m_pos.x + (m_nDigit - nCnt)*m_NumberDistance, m_pos.y, 0.0f);
		m_apNumber[nCnt].SetPos(&NumberPos);                //スケール後位置設定
		m_apNumber[nCnt].SetSize(&m_NumberSize);            //スケール後サイズ設定

		//ナンバーのアップデート
		m_apNumber[nCnt].SetNumber(nNumber);
		m_apNumber[nCnt].Update();
	}
}
void CScoreScale::Draw(void)
{
	if (NULL == m_apNumber) return;
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		m_apNumber[nCnt].Draw();
	}
}

//ファクション関数
CScoreScale *CScoreScale::Create
(
	const D3DXVECTOR3& pos  /*位置*/, 
	const D3DXVECTOR3& NumberSize  /*一個数字のサイズ*/, 
	const D3DXVECTOR3& ScalePoint,
	int nDigit            /*桁数*/, 
	const char* TexPass   /*テクスチャパス*/
)
{
	CScoreScale *pScore;
	pScore = new CScoreScale(s_nPriority);
	pScore->Init(pos, NumberSize, nDigit, TexPass);
	pScore->SetObjType(OBJTYPE_NONE);
	pScore->SetScalePoint(ScalePoint);
	return pScore;
}
void CScoreScale::AddScore(int nValue)
{
	m_nScore += nValue;
}

int CScoreScale::GetScore(void)
{
	return m_nScore;
}
void CScoreScale::SetScorePos(void)
{
	
}
D3DXVECTOR3 CScoreScale::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 CScoreScale::GetSize(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return size;
}

//ダミー
void CScoreScale::PowerReset(void)
{
	
}
void CScoreScale::AddPowerX(float fPowerX)
{
	
}
void CScoreScale::AddPowerY(float fPowerY)
{
	
}
