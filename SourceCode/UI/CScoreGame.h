#pragma once
#ifndef _SCORE_GAME_H_
#define _SCORE_GAME_H_

#include "main.h"
#include "scene2D.h"
#include "CNumberGame.h"

class CScoreGame : public CScene
{
public:
	CScoreGame();
	CScoreGame(int nPriority = 3);
	~CScoreGame();

	//��Ԋ֐�
	HRESULT Init(const D3DXVECTOR3& pos/*�ʒu*/,const D3DXVECTOR3& NumberSize/*������̃T�C�Y*/,float NumberDistance/*�����̊Ԃ̋���*/,int nDigit/*����*/,const char* TexPass);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�t�@�N�V�����֐�
	static CScoreGame *Create(const D3DXVECTOR3& pos/*�ʒu*/, const D3DXVECTOR3& NumberSize/*������̃T�C�Y*/, float NumberDistance/*�����̊Ԃ̋���*/, int nDigit/*����*/, const char* TexPass);          //CScene2D�̃C���X�^���X�𐶐�����֐�
	void AddScore(int nValue);                       //���Z
	int GetScore(void);                              //�X�R�A���擾
	void SetScorePos(void);                          //�X�R�A�̈ʒu��ݒ�
	static int GetPriority(void) { return s_nPriority; }

	//�Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) {}
	void SetScore(int nScore) { m_nScore = max(0, nScore); }

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
	static int s_nPriority;
};

#endif