#include "CScoreGame.h"
#include "CNumber.h"

int CScoreGame::s_nPriority = 5;

CScoreGame::CScoreGame() : CScene(3)
{
	m_apNumber = NULL;
	m_nScore = 0;
}

CScoreGame::CScoreGame(int nPriority) : CScene(nPriority)
{
	m_apNumber = NULL;
	m_nScore = 0;
}

CScoreGame::~CScoreGame()
{
	if (NULL != m_apNumber)
	{
		delete[] m_apNumber;
		m_apNumber = NULL;
	}
}

//��Ԋ֐�
HRESULT CScoreGame::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& NumberSize, float NumberDistance/*�����̊Ԃ̋���*/, int nDigit, const char* TexPass)
{
	//�p�����[�^������������
	m_nScore = 0;
	m_pos = pos;
	m_NumberSize = NumberSize;
	m_NumberDistance = NumberDistance;
	m_nDigit = max(1,nDigit);

	if(NULL != m_apNumber)
	{
		delete[] m_apNumber;
		m_apNumber = NULL;
	}
	m_apNumber = NULL;
	m_apNumber = new CNumberGame[m_nDigit];      //�����m��

	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		D3DXVECTOR3 NumberPos;
		NumberPos = D3DXVECTOR3(m_pos.x + (m_nDigit - nCnt)*NumberDistance, m_pos.y, 0.0f);
		m_apNumber[nCnt].Init(NumberPos, m_NumberSize, TexPass);
	}

	CNumber::LoadTex();

	return S_OK;
}
void CScoreGame::Uninit(void)
{
	if (NULL != m_apNumber)
	{
		delete[] m_apNumber;
		m_apNumber = NULL;
	}

	this->Release();
}
void CScoreGame::Update(void)
{
	if (NULL == m_apNumber) return;
	int nScore = m_nScore;

	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
			int nNumber;
			nNumber = nScore % 10;
			nScore = nScore / 10;
			m_apNumber[nCnt].SetNumber(nNumber);
			m_apNumber[nCnt].Update();
	}
}
void CScoreGame::Draw(void)
{
	if (NULL == m_apNumber) return;
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		m_apNumber[nCnt].Draw();
	}
}

//�t�@�N�V�����֐�
CScoreGame *CScoreGame::Create
(
	const D3DXVECTOR3& pos  /*�ʒu*/, 
	const D3DXVECTOR3& NumberSize  /*������̃T�C�Y*/, 
	float NumberDistance  /*�����̊Ԃ̋���*/, 
	int nDigit            /*����*/, 
	const char* TexPass   /*�e�N�X�`���p�X*/
)
{
	CScoreGame *pScore;
	pScore = new CScoreGame(s_nPriority);
	pScore->Init(pos, NumberSize, NumberDistance, nDigit, TexPass);
	pScore->SetObjType(OBJTYPE_SCORE_GAME);
	return pScore;
}
void CScoreGame::AddScore(int nValue)
{
	m_nScore += nValue;
}

int CScoreGame::GetScore(void)
{
	return m_nScore;
}
void CScoreGame::SetScorePos(void)
{
	
}
D3DXVECTOR3 CScoreGame::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 CScoreGame::GetSize(void)
{
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return size;
}

//�_�~�[
void CScoreGame::PowerReset(void)
{
	
}
void CScoreGame::AddPowerX(float fPowerX)
{
	
}
void CScoreGame::AddPowerY(float fPowerY)
{
	
}
