#include "CScore.h"
#include "CNumber.h"
#include "CResult.h"

int CScore::s_nPriority = 3;

CScore::CScore() : CScene2D(3)
{
	m_nScore = 0;
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
}

CScore::CScore(int Priority) : CScene2D(Priority)
{
	m_nScore = 0;
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
}

CScore::~CScore()
{
	
}

//定番関数
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	//パラメータを初期化する
	m_nScore = 0;
	m_pos = pos;

	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		D3DXVECTOR3 NumberPos;
		NumberPos = D3DXVECTOR3(m_pos.x + (MAX_DIGIT-nCnt)*SCORE_DISTANCE, m_pos.y, 0.0f);
		m_apNumber[nCnt] = new CNumber(s_nPriority);
		m_apNumber[nCnt]->Init(D3DXVECTOR3(NumberPos.x + (nCnt * (RESULT_NUMBER_WIDTH + RESULT_NUMBER_INTV)), NumberPos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RESULT_NUMBER_WIDTH, RESULT_NUMBER_HEIGHT, 0.0f), 0);
	}

	CNumber::LoadTex();

	return S_OK;
}
void CScore::Uninit(void)
{
	//スコア解放
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = NULL;
		}
	}

	CNumber::UnloadTex();

	this->Release();
}
void CScore::Update(void)
{
	int nScore = m_nScore;

	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			int nNumber;
			nNumber = nScore % 10;
			nScore = nScore / 10;
			m_apNumber[nCnt]->SetNumber(nNumber);
			m_apNumber[nCnt]->Update();
			m_apNumber[nCnt]->SetNumType(CNumber::NUMTYPE_SCORE);

			D3DXVECTOR3 NumberPos;
			NumberPos = D3DXVECTOR3(m_pos.x + (MAX_DIGIT - nCnt)*SCORE_DISTANCE, m_pos.y, 0.0f);
			m_apNumber[nCnt]->SetPos(D3DXVECTOR3(NumberPos.x + (nCnt * (RESULT_NUMBER_WIDTH + RESULT_NUMBER_INTV)), m_pos.y, 0.0f));
		}
	}
}
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//ファクション関数
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore;
	pScore = new CScore(s_nPriority);
	pScore->Init(pos);
	pScore->SetObjType(OBJTYPE_SCORE);
	return pScore;
}
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}
int CScore::GetScore(void)
{
	return m_nScore;
}
void CScore::SetScorePos(void)
{
	
}
D3DXVECTOR3 CScore::GetPos(void)
{
	return m_pos;
}
D3DXVECTOR3 CScore::GetSize(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return size;
}

//ダミー
void CScore::PowerReset(void)
{
	
}
void CScore::AddPowerX(float fPowerX)
{
	
}
void CScore::AddPowerY(float fPowerY)
{
	
}
