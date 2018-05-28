#pragma once
#ifndef _CSPRING_H_
#define _CSPRING_H_

#include "main.h"
#include "scene2D.h"

//�O���錾
class CScene2D;

class CSpring : public CScene2D
{
public:
	CSpring();
	CSpring(int nPriority = 3);
	~CSpring();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSpring *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fElasticModulus,bool bFixDirection, const char* filePass);          //CScene2D�̃C���X�^���X�𐶐�����֐�

	//�Z�b�^�[
	void SetElasticModulus(float fElasticModulus){
		if(fElasticModulus < 0.0f) m_fElasticModulus = 1.0f;
		m_fElasticModulus = fElasticModulus;
	}
	void SetFixDirection(bool bFixDirection) { m_bFixDirection = bFixDirection; }
	void SetReturnFlag(bool ReturnFlag) { m_ReturnSizeFlag = ReturnFlag; }

	//�Q�b�^�[
	static int GetPriority(void) { return s_nPriority; }
	D3DXVECTOR3 GetPosOrigin(void) {return m_posOrigin;}
	D3DXVECTOR3 GetSizeOrigin(void) { return m_sizeOrigin; }
	bool GetFixDirection(void) { return m_bFixDirection; }
	float GetElasticModulus(void) { return m_fElasticModulus; }

	//���̊֐�
	void ReturnAction(void);
private:
	float m_fElasticModulus;   //�΂˂̒e���W��
	D3DXVECTOR3 m_sizeOrigin; //���̃T�C�Y
	D3DXVECTOR3 m_posOrigin;  //���̈ʒu
	float m_PowerX;           //X�����̒e��
	bool m_bFixDirection;     //�΂˂̌Œ����(false �͍��Œ�,true�͉E�Œ�)
	bool m_ReturnSizeFlag;    //�v���[���[�Ƃ̓��蔻�肪�Ȃ��ꍇ���X�Ɍ��̃T�C�Y�ɖ߂�ݒ�
	static int s_nPriority;
};

#endif