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

//��Ԋ֐�
HRESULT CScoreScale::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& NumberSize, int nDigit, const char* TexPass)
{
	//�p�����[�^������������
	m_nScore = 0;
	m_pos = pos;
	m_NumberSize = NumberSize;
	m_OriginSize = m_NumberSize;                  //���̃T�C�Y�ۑ�
	m_NumberDistance = NumberSize.x;
	m_nDigit = max(1,nDigit);
	m_Scale = 1.0f;

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
		NumberPos = D3DXVECTOR3(m_pos.x + (m_nDigit - nCnt)*m_NumberDistance, m_pos.y, 0.0f);
		m_apNumber[nCnt].Init(NumberPos, m_NumberSize, TexPass);
	}

	float CenterX = (m_pos.x + m_pos.x + (m_nDigit-1)*m_NumberDistance) * 0.5;
	float CenterY = (m_pos.y + m_pos.y + NumberSize.y) *0.5;

	m_OriginPos = D3DXVECTOR3(CenterX, CenterY,0.0f);      //���̒��S���W�ۑ�
	m_CenterPos = m_OriginPos;                             //�Z���^�[���S���W�̏����l�ݒ�

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

	//�i���o�[�̃T�C�Y�R���g���[��
	D3DXVECTOR3 DistanceFromSP = m_OriginPos - m_ScalePoint;   //�����_�ƃX�P�[�����S�̍���
	DistanceFromSP = DistanceFromSP * m_Scale;      //�X�P�[���̌�̍����T�C�Y
	m_CenterPos = m_ScalePoint + DistanceFromSP;    //�X�P�[��Center���W�����߂�

	m_NumberSize = m_OriginSize * m_Scale;          //�X�P�[����T�C�Y
	m_NumberDistance = m_NumberSize.x;              //�X�P�[�������̊Ԃ̕�

	float TotalSizeX = m_NumberSize.x * m_nDigit;
	float TotalSizeY = m_NumberSize.y;

	//�ω���̍�����W������
	m_pos.x = m_CenterPos.x - TotalSizeX;
	m_pos.y = m_CenterPos.y - TotalSizeY;

	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		int nNumber;
		nNumber = nScore % 10;
		nScore = nScore / 10;

		D3DXVECTOR3 NumberPos;
		NumberPos = D3DXVECTOR3(m_pos.x + (m_nDigit - nCnt)*m_NumberDistance, m_pos.y, 0.0f);
		m_apNumber[nCnt].SetPos(&NumberPos);                //�X�P�[����ʒu�ݒ�
		m_apNumber[nCnt].SetSize(&m_NumberSize);            //�X�P�[����T�C�Y�ݒ�

		//�i���o�[�̃A�b�v�f�[�g
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

//�t�@�N�V�����֐�
CScoreScale *CScoreScale::Create
(
	const D3DXVECTOR3& pos  /*�ʒu*/, 
	const D3DXVECTOR3& NumberSize  /*������̃T�C�Y*/, 
	const D3DXVECTOR3& ScalePoint,
	int nDigit            /*����*/, 
	const char* TexPass   /*�e�N�X�`���p�X*/
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

//�_�~�[
void CScoreScale::PowerReset(void)
{
	
}
void CScoreScale::AddPowerX(float fPowerX)
{
	
}
void CScoreScale::AddPowerY(float fPowerY)
{
	
}
