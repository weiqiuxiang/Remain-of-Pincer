#pragma once
#ifndef _SCORE_SCALE_H_
#define _SCORE_SCALE_H_

#include "main.h"
#include "scene2D.h"
#include "CNumberGame.h"

class CScoreScale : public CScene
{
public:
	CScoreScale();
	CScoreScale(int nPriority = 3);
	~CScoreScale();

	//��Ԋ֐�
	HRESULT Init(const D3DXVECTOR3& pos/*�ʒu*/,const D3DXVECTOR3& NumberSize/*������̃T�C�Y*/,int nDigit/*����*/,const char* TexPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�t�@�N�V�����֐�
	static CScoreScale *Create(const D3DXVECTOR3& pos/*����̈ʒu*/, const D3DXVECTOR3& NumberSize/*������̃T�C�Y*/, const D3DXVECTOR3& ScalePoint,
		 int nDigit/*����*/, const char* TexPass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	void AddScore(int nValue);                       //���Z
	int GetScore(void);                              //�X�R�A���擾
	void SetScorePos(void);                          //�X�R�A�̈ʒu��ݒ�
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetOriginPos(const D3DXVECTOR3& pos) { m_OriginPos = pos; }
	void SetPosToSetOrigin(const D3DXVECTOR3& pos) {
		m_pos = pos; 
		float CenterX = (m_pos.x + m_pos.x + (m_nDigit - 1)*m_OriginSize.x) * 0.5;
		float CenterY = (m_pos.y + m_pos.y + m_OriginSize.y) *0.5;
		m_OriginPos = D3DXVECTOR3(CenterX, CenterY, 0.0f);
	}
	void SetSize(const D3DXVECTOR3& size) {}
	void SetScore(int nScore) { m_nScore = max(0, nScore); }
	void SetScale(float fScale) { m_Scale = max(0, fScale); }
	void SetScalePoint(const D3DXVECTOR3& ScalePoint) { m_ScalePoint = ScalePoint; }

	//�Q�b�^�[
	D3DXVECTOR3 GetPos(void);                        //�X�R�A�̈ʒu�擾
	D3DXVECTOR3 GetSize(void);

private:
	void PowerReset(void);
	void AddPowerX(float fPowerX);
	void AddPowerY(float fPowerY);

	CNumberGame *m_apNumber;   //Number�|�C���^
	D3DXVECTOR3 m_pos;         //�ʒu
	D3DXVECTOR3 m_NumberSize;  //������̃T�C�Y
	float m_NumberDistance;    //�����̊Ԃ̋���
	int m_nDigit;              //����
	int m_nScore;              //�X�R�A

	//�X�P�[���ϐ�
	D3DXVECTOR3 m_CenterPos;     //���S���W
	D3DXVECTOR3 m_OriginPos;     //���̌��_(���S)
	D3DXVECTOR3 m_ScalePoint;    //�X�P�[�����_(�X�P�[�����_)
	D3DXVECTOR3 m_OriginSize;    //���̃T�C�Y
	float m_Scale;

	static int s_nPriority;
};

#endif